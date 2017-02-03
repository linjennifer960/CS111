import csv

#open file we want to write to		
result = open("lab3b_check.txt", 'w')

class Inode:
	def __init__(self):
		self._inodeNum = 0
		self._refList = []
		self._numLinks = 0
		self._ptrs=[]

class Block:
	def __init__(self):
		self._blockNum = 0
		self._refList = []
		self._indirectBlockNum = 0

class Parser:
	def __init__(self):
		#initialize
		self.totalInodeNum = 0
		self.totalBlockNum = 0
		self.blockSize = 0
		self.blockPerGroup = 0
		self.inodePerGroup = 0
		self.inodeBitmapBlocks = []
		self.blockBitmapBlocks = []
		self.inodeFreeList = []
		self.blockFreeList = []
		self.allocatedInodes = {}
		self.allocatedBlocks = {}
		self.directoryMap = {}
		self.indirectMap = {}

	def readFiles(self):
		self.readSuper()	#for super.csv
		self.readGroup()	#for group.csv
		self.readIndirect()	#for indirect.csv
		self.readBitmap()	#for bitmap.csv
		self.readInode()	#for inode.csv
		self.readDirectory()	#for directory.csv

	def readSuper(self, file="super.csv"):
		with open(file, 'r') as supercsv:
			reader = csv.reader(supercsv)
			for row in reader:
				self.totalInodeNum = int(row[1])
				self.totalBlockNum = int(row[2])
				self.blockSize = int(row[3])
				self.blockPerGroup = int(row[5])
				self.inodePerGroup = int(row[6])

	def readGroup(self, file="group.csv"):
		with open(file, 'r') as groupcsv:
			reader = csv.reader(groupcsv)
			for row in reader:
				self.inodeBitmapBlocks.append(int(row[4], 16))
				self.blockBitmapBlocks.append(int(row[5], 16))

	def readIndirect(self, file="indirect.csv"):
		with open(file, 'r') as indirectcsv:
			reader = csv.reader(indirectcsv)
			for row in reader:
				self.indirectMap[(int(row[0], 16) , int(row[1]))] = int(row[2], 16)

	def readBitmap(self, file="bitmap.csv"):
		with open(file, 'r') as bitmapcsv:
			reader = csv.reader(bitmapcsv)
			for row in reader:
				if int(row[0], 16) in self.inodeBitmapBlocks:
					self.inodeFreeList.append(int(row[1]))
				elif int(row[0], 16) in self.blockBitmapBlocks:
					self.blockFreeList.append(int(row[1]))

	def readInode(self, file="inode.csv"):
		with open(file, 'r') as inodecsv:
			reader = csv.reader(inodecsv)
			for row in reader:
				inodeNum = int(row[0])
				inode = Inode()
				inode._inodeNum = inodeNum
				inode._numLinks = int(row[5])
				for i in range(15):
					if int(row[i+11], 16) == 0:
						break
					else:
						inode._ptrs.append(int(row[i+11], 16))
				self.allocatedInodes[inodeNum] = inode

				numBlocks = int(row[10])
				if numBlocks > 12:
					for i in range(12):
						blockNum = int(row[i+11], 16)
						if (blockNum ==0) or (blockNum > self.totalBlockNum):
							result.write("INVALID BLOCK < " + blockNum + " > IN INODE < " + str(int(row[0])) + " > ENTRY < " + str(i) + " >\n")
						else:
							block = Block()
							block._blockNum = blockNum
							block._refList.append((int(row[0]), None, i))
							self.allocatedBlocks[blockNum] = block

				else:
					for i in range(numBlocks):
						blockNum = int(row[i+11], 16)
						if(blockNum==0) or (blockNum > self.totalBlockNum):
							result.write("INVALID BLOCK < " + str(blockNum) + " > IN INODE < " + str(int(row[0])) + " > ENTRY < " + str(i) + " >\n")
						else:
							if blockNum in self.allocatedBlocks:
								self.allocatedBlocks[blockNum]._refList.append((int(row[0]), None, i))
							else:
								block = Block()
								block._blockNum = blockNum
								block._refList.append((int(row[0]), None, i))
								self.allocatedBlocks[blockNum] = block


	def readDirectory(self, file="directory.csv"):
		with open(file, 'r') as directorycsv:
			reader = csv.reader(directorycsv)
			for row in reader:
				parent = int(row[0])
				child = int(row[4])
				entryNum = int(row[1])
				if(parent != child) or (parent == 2):
					self.directoryMap[child] = parent
				if child in self.allocatedInodes:
					self.allocatedInodes[child]._refList.append((parent, entryNum))
				else:
					result.write("UNALLOCATED INODE < " + str(child) + " > REFERENCED BY DIRECTORY < " + str(parent) + " > ENTRY < " + str(entryNum) + " >\n")
				if (entryNum == 0) and (child!=parent):
					entryName = row[5]
					result.write("INCORRECT ENTRY IN < " + str(parent) + " > NAME < " + str(entryName) + " > LINK TO < " + str(child) + " > SHOULD BE < " + str(parent) + " >\n")
				elif (entryNum == 1) and (child != self.directoryMap[parent]):
					entryName = row[5]
					result.write("INCORRECT ENTRY IN < " + str(parent) + " > NAME < " + str(entryName) + " > LINK TO < " + str(child) + " > SHOULD BE < " + str(self.directoryMap[parent]) + " >\n")    

		for inodeNum in self.allocatedInodes:
			inode = self.allocatedInodes[inodeNum]
			count = len(inode._refList)
			if (inode._inodeNum > 10) and (count == 0):
				groupNum = inodeNum / self.inodePerGroup
				result.write("MISSING INODE < " + str(inode._inodeNum) + " > SHOULD BE IN FREE LIST < " + str(self.inodeBitmapBlocks[groupNum]) + " >\n")
			elif (inode._numLinks != count):
				result.write("LINKCOUNT < " + str(inode._inodeNum) + " > IS < " + str(inode._numLinks) + " > SHOULD BE < " + str(count) + " >\n")

		for inodeNum in self.inodeFreeList:
			if inodeNum in self.allocatedInodes:
				inode = self.allocatedInodes[inodeNum]
				result.write("UNALLOCATED INODE < " + str(inodeNum) + " > REFERENCED BY")
				for i in range(len(inode._refList)):
					result.write(" DIRECTORY < " + str(inode._refList[i][0]) + " > ENTRY < " + str(inode._refList[i][1]) + " >")
				result.write("\n")

		for inodeNum in range(11, int(self.totalInodeNum) + 1):
			if (inodeNum not in self.inodeFreeList) and (inodeNum not in self.allocatedInodes):
				groupNum = inodeNum / self.inodePerGroup
				result.write("MISSING INODE < " + str(inodeNum) + " > SHOULD BE IN FREE LIST < " + str(self.inodeBitmapBlocks[groupNum]) + " >\n")

		for blockNum in self.allocatedBlocks:
			block = self.allocatedBlocks[blockNum]
			if len(block._refList) > 1:
				result.write("MULTIPLY REFERENCED BLOCK < " + str(block._blockNum) + " > BY")
				for i in range(len(block._refList)):
					result.write(" INODE < " + str(block._refList[i][0]) + " > ENTRY < " + str(block._refList[i][2]) + " >")
				result.write("\n")

		for block in self.blockFreeList:
			if block in self.allocatedBlocks:
				if self.allocatedBlocks[block]._refList[0][1] == None:
					result.write("UNALLOCATED BLOCK < " + str(block) + " > REFERENCED BY INODE < " + str(self.allocatedBlocks[block]._refList[0][0]) + " > ENTRY < " + str(self.allocatedBlocks[block]._refList[0][2]) + " >\n")

def main():
	parser = Parser()
	parser.readFiles()

if __name__ == "__main__":
	main()


