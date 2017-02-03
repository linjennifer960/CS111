#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>


int fs = 0;
int isPowerOfTwo(int x){
    if(x==1)    return true;
    if(x==0)    return false;
    if(x%2!=0)  return false;
    return isPowerOfTwo(x/2);
}

int isFree(char *map, int byteNum, int bitNum){
    char *byte = map + byteNum;
    int mask = (0x1 << bitNum);
    return !((*byte) & mask);
}

struct inodeStr{
    int num;
    int numOfBlocks;
    uint32_t blockarr[15];
};

int indir(uint32_t* indirectPtr, int blockSize, int containingBlock, FILE* csv){
    if(indirectPtr == 0)
        return 0;
    int counter = 0;
    int numPointers = 256; // An indirect pointer points to 256 data blocks
    for(int i=0; i<numPointers; i++){
        uint32_t data = indirectPtr[i];
        if(data == 0)
            break;
        else
            fprintf(csv, "%x,%d,%x\n", containingBlock, i, data);
        counter++;
    }
    return counter;
}

int main(int argc, char* argv[]){
    if(argc > 2){
        fprintf(stderr, "Incorrect number of arguments");
        exit(1);
    }
    fs = open(argv[1], O_RDONLY);
    if(fs<0){
        fprintf(stderr, "Error opening image");
        exit(1);
    }
    ////////////SUPERBLOCK//////////////
    char *spblock=malloc(1024);
    int ret = pread(fs, spblock, 1024, 1024);
    if(ret<1024){
        fprintf(stderr, "Unexpected superblock read");
        exit(1);
    }
    uint16_t *magic = (uint16_t*)(spblock+56);
    uint32_t *inodeNum = (uint32_t*)(spblock);
    uint32_t *blockNum = (uint32_t*)(spblock+4);
    uint32_t *logBlockSize = (uint32_t*)(spblock+24);
    int blockSize = 1024 << *logBlockSize;
    uint32_t *logFragSize = (uint32_t*)(spblock+28);
    int fragSize;
    if(*logFragSize < 0)
        fragSize = 1024 >> -(*logFragSize);
    else
        fragSize = 1024 << *logFragSize;
    uint32_t *blockPerGroup = (uint32_t*)(spblock+32);
    uint32_t *inodePerGroup = (uint32_t*)(spblock+40);
    uint32_t *fragPerGroup = (uint32_t*)(spblock+36);
    uint32_t *firstDataBlock = (uint32_t*)(spblock+20);
    
    //sanity checking
    if(*magic!=0xEF53){
        fprintf(stderr, "Superblock - invalid magic: 0x%x", *magic);
        exit(1);
    }
    if(!isPowerOfTwo(blockSize || blockSize>64000 || blockSize<512)){
        fprintf(stderr, "Superblock - invalid block size: %d", blockSize);
        exit(1);
    }
    if(*blockNum % *blockPerGroup != 0){
        fprintf(stderr, "superblock - %d blocks, %d blocks/group", *blockNum, *blockPerGroup);
        exit(1);
    }
    if(*inodeNum % *inodePerGroup !=0){
        fprintf(stderr, "superblock - %d Inodes, %d Inodes/group", *inodeNum, *inodePerGroup);
        exit(1);
    }
    
    int wr1 = creat("super.csv", 0666);
    dprintf(wr1, "%x,%d,%d,%d,%d,%d,%d,%d,%d\n", *magic, *inodeNum, *blockNum, blockSize, fragSize, *blockPerGroup, *inodePerGroup, *fragPerGroup, *firstDataBlock);
    
    //////////GROUP DESCRIPTOR//////////
    int groupNum = *blockNum / *blockPerGroup;
    char *groupDesTable = malloc(groupNum*32);
    if(blockSize==1024)
        pread(fs, groupDesTable, groupNum*32, 2048);
    else
        pread(fs, groupDesTable, groupNum*32, blockSize);
    
    int i;
    int numContainBlock;
    int wr2 = creat("group.csv", 0666);
    
    int inodeMap[groupNum];
    int blockMap[groupNum];
    int inodeTable[groupNum];
    
    for(i=0; i<groupNum; i++) {
        numContainBlock = *blockPerGroup;
        uint16_t *freeBlockNum = (uint16_t*)(groupDesTable+12);
        uint16_t *freeInodeNum = (uint16_t*)(groupDesTable+14);
        uint16_t *directoryNum = (uint16_t*)(groupDesTable+16);
        uint32_t *freeInodeBitmapBlock = (uint32_t*)(groupDesTable+4);
        uint32_t *freeBlockBitmapBlock = (uint32_t*)(groupDesTable);
        uint32_t *inodeTableStartBlock = (uint32_t*)(groupDesTable+8);
        
        //sanity checking
        if(numContainBlock!=*blockPerGroup){
            fprintf(stderr, "Group %d: %d blocks, superblock says %d", i, numContainBlock, *blockPerGroup);
        }
        
        dprintf(wr2, "%d,%d,%d,%d,%x,%x,%x\n", numContainBlock, *freeBlockNum, *freeInodeNum, *directoryNum, *freeInodeBitmapBlock, *freeBlockBitmapBlock, *inodeTableStartBlock);
        
        inodeMap[i] = (*freeInodeBitmapBlock);
        blockMap[i] = (*freeBlockBitmapBlock);
        inodeTable[i] = (*inodeTableStartBlock);
        
        groupDesTable+=32;
    }
    //////////FREE BITMAP ENTRY/////////
    FILE *bitmapfile = fopen("bitmap.csv", "w+");
    int j;
    int allocatedInode[(*inodeNum)];
    int aisize=0;
    for(j=0; j<groupNum; j++){
        char *bitMap = malloc(blockSize);
        uint32_t blockNumOfMap = (uint32_t) blockMap[j];
        int offset = blockNumOfMap*blockSize;
        pread(fs, bitMap, blockSize, offset);
        
        int k;
        int l;
        int freeBlock;
        for(k=0; k<(*blockPerGroup)/8; k++){
            for(l=0; l<8; l++){
                if(isFree(bitMap, k, l)){
                    freeBlock = (*blockPerGroup)*j + 8*k + l + 1;
                    fprintf(bitmapfile, "%x,%d\n", blockNumOfMap, freeBlock);
                }
            }
        }
        char *inodeBitMap = malloc(blockSize);
        uint32_t blockNumOfInodeMap = (uint32_t) inodeMap[j];
        int inodeOffset = blockNumOfInodeMap*blockSize;
        pread(fs, inodeBitMap, blockSize, inodeOffset);
        int freeInode;
        for(k=0; k<(*inodePerGroup)/8; k++){
            for(l=0; l<8; l++){
                if(isFree(inodeBitMap, k, l)){
                    freeInode = (*inodePerGroup)*j + 8*k + l + 1;
                    fprintf(bitmapfile, "%x,%d\n", blockNumOfInodeMap, freeInode);
                }
                else{
                    allocatedInode[aisize] = (*inodePerGroup)*j + 8*k + l + 1;
                    aisize++;
                }
            }
        }
    }
    ///////////////INODE////////////////
    char* inode = malloc(128);
    FILE *inodefile = fopen("inode.csv", "w+");
    struct inodeStr inodeDir[aisize];
    int index=0;
    
    int inodeIndex;
    int blockGroup;
    int offset;
    struct inodeStr;
    for(i=0; i<aisize; i++){
        inodeIndex = (allocatedInode[i]-1) % (*inodePerGroup);
        blockGroup = (allocatedInode[i]-1) / (*inodePerGroup);
        offset = 128*inodeIndex + inodeTable[blockGroup]*blockSize;
        pread(fs, inode, 128, offset);
        
        uint16_t* mode = (uint16_t*) inode;
        uint16_t* owner = (uint16_t*) (inode + 2);
        uint16_t* group = (uint16_t*) (inode + 24);
        uint16_t* linkCount = (uint16_t*) (inode + 26);
        uint32_t* creationTime = (uint32_t*) (inode + 12);
        uint32_t* modificationTime = (uint32_t*) (inode + 16);
        uint32_t* accessTime = (uint32_t*) (inode + 8);
        uint32_t* fileSize = (uint32_t*) (inode + 4);
        uint32_t* numBlocks = (uint32_t*) (inode + 28);
        uint32_t* blockPtrs = (uint32_t*) (inode + 40);
        
        char typeOfFile;
        int mask = 0xF000;
        if((mask&(*mode)) == 0xA000)
            typeOfFile = 's';
        else if((mask&(*mode)) == 0x4000)
            typeOfFile = 'd';
        else if((mask&(*mode)) == 0x8000)
            typeOfFile = 'f';
        else
            typeOfFile = '?';
        
        int k;
        if(typeOfFile == 'd'){
            inodeDir[index].num = allocatedInode[i];
            inodeDir[index].numOfBlocks = (*numBlocks)* 512 / blockSize;
            for(k=0; k<15; k++){
                inodeDir[index].blockarr[k] = *(blockPtrs+k);
            }
            index++;
        }
        fprintf(inodefile, "%d,%c,%o,%d,%d,%d,%x,%x,%x,%d,%d", allocatedInode[i], typeOfFile, *mode, *owner, *group, *linkCount, *creationTime, *modificationTime, *accessTime, *fileSize, (*numBlocks)* 512 / blockSize);
        int l;
        for(l=0; l<15; l++){
            fprintf(inodefile, ",%x", *blockPtrs);
            blockPtrs++;
            if(l==14)
                fprintf(inodefile, "\n");
            
        }
    }
    
    ///////////DIRECTORY ENTRY//////////
    FILE *directoryfile = fopen("directory.csv", "w+");
    char *direct = malloc(blockSize);
    int k;
    for(i=0; i<index; i++){
        int entryNum = 0;
        for(j=0; j<inodeDir[i].numOfBlocks; j++){
            uint16_t temp = 0;
            while(1){
                pread(fs, direct, blockSize, (inodeDir[i].blockarr[j]*blockSize) + temp);
                uint32_t *inode = (uint32_t*)(direct);
                uint16_t *rec_len = (uint16_t*)(direct+4);
                
                temp += *rec_len;
                char *name_len=(direct+6);
                char name[255];
                int size_name=0;
                for(k=0; k<*name_len; k++){
                    name[size_name] = *(direct+8+k);
                    size_name++;
                }
                name[size_name]='\0';
                /*sanity checking
                if(*rec_len<8 || *rec_len>1024)
                    fprintf(stderr, "Entry length not reasonable, rec_len=%d\n", *rec_len);
                if(*name_len > *rec_len)
                    fprintf(stderr, "Name length didn't fit within entry length, rec_len=%d, name_len=%d\n", *rec_len, *name_len);*/
                
                //if entry or name length is unreasonable, stop interpret directory
                if(*rec_len<8 || *rec_len>1024 || *name_len > *rec_len){
                    entryNum++;
                    if(*inode!=0)
                        fprintf(directoryfile, "%d,%d,%d,%d,%d,\"%s\"\n", inodeDir[i].num, entryNum, *rec_len, *name_len, *inode, name);
                    break;
                }
                
                if(*inode !=0)
                    fprintf(directoryfile, "%d,%d,%d,%d,%d,\"%s\"\n", inodeDir[i].num, entryNum, *rec_len, *name_len, *inode, name);
                entryNum++;
                if(temp>=blockSize)
                    break;
            }
        }
    }

    ////////INDIRECT BLOCK ENTRY////////
    FILE *indirect = fopen("indirect.csv", "w+");
    uint32_t* indirbl = malloc(blockSize);
    uint32_t* doubindirbl = malloc(blockSize);
    uint32_t* tripindirbl = malloc(blockSize);
    
    for (int i = 0; i < aisize; i++){
        int i_inodeindex = (allocatedInode[i] - 1) % (*inodePerGroup);
        int i_blockgroup = (allocatedInode[i] - 1) / (*inodePerGroup);
        int off = 128*i_inodeindex + blockSize*inodeTable[i_blockgroup];
        pread(fs, inode, 128, off);
        
        uint32_t* block = (uint32_t*) (inode + 40);
        uint32_t* blocks = (uint32_t*) (inode + 28);
        int numBlocks = *blocks * 512 / blockSize;
        
        if (numBlocks > 12){
            if(block[12] != 0){
                pread(fs, indirbl, blockSize, block[12]*blockSize);
                if(indirbl != 0){
                    indir(indirbl, blockSize, block[12], indirect);
                }
            }
            if(block[13] != 0){
                pread(fs, doubindirbl, blockSize, block[13]*blockSize);
                if(doubindirbl != 0){
                    int check = indir(doubindirbl, blockSize, block[13], indirect);
                    for(int j = 0; j < check; j++){
                        pread(fs, indirbl, blockSize, doubindirbl[j]*blockSize);
                        if(indirbl != 0){
                            indir(indirbl, blockSize, doubindirbl[j], indirect);
                        }
                    }
                }
            }
            if(block[14] != 0){
                pread(fs, tripindirbl, blockSize, block[14]*blockSize);
                if(tripindirbl != 0){
                    int check1 = indir(tripindirbl, blockSize, block[14], indirect);
                    for(int j = 0; j < check1; j++){
                        pread(fs, doubindirbl, blockSize, tripindirbl[j]*blockSize);
                        if(doubindirbl != 0){
                            int check = indir(doubindirbl, blockSize, block[14], indirect);
                            for(int k = 0; k < check; k++){
                                pread(fs, indirbl, blockSize, doubindirbl[k]*blockSize);
                                if(indirbl != 0){
                                    indir(indirbl, blockSize, doubindirbl[k], indirect);
                                } 
                            }
                        }
                    }
                }
            }
        }
    }
}
