#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <assert.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <mcrypt.h>

struct termios saved_attributes;
char EOT = 0x04;
char CR = 0x0D;
char LF = 0x0A;
int sockfd;
int portcheck = 0;
int portnum;
int logcheck = 0;
int log_fd = -1;
int encryptcheck = 0;
MCRYPT en;
static char* arg;

/*the following section incorporates code from gnu manual chp17.7*/
/////////////////////////////////////////////////////////////////////
void reset_input_mode(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode(void)
{
    struct termios tattr;
    /* save the terminal attributes so we can restore them later*/
    tcgetattr(STDIN_FILENO, &saved_attributes);
    atexit(reset_input_mode);
    /* set the funny terminal modes. */
    tcgetattr(STDIN_FILENO, &tattr);
    tattr.c_lflag &= ~(ICANON|ECHO);
    tattr.c_cc[VMIN] =1 ;
    tattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}

void *newThreadFunc(void *arg)
{
    char c;
    int test;
    while(1)
    {
        test = read(sockfd, &c, 1);
        if(test <= 0)
            break;
        if(logcheck)
        {
            write(log_fd, "RECEIVED 1 bytes: ", 18);
            write(log_fd, &c, 1);
            if(c != CR && c != LF)
                write(log_fd, "\n", 1);
        }
        if(encryptcheck)
            mdecrypt_generic(en, &c,1);
        write(STDOUT_FILENO, &c, 1);
    }
    return (void*)0;
}

void readFile(void){
    char c;
    while(1){
        int test;
        test=read(STDIN_FILENO, &c, 1);
        if(test<=0){
            shutdown(sockfd, 2);
            exit(1);
        }
        if(c==EOT){
            shutdown(sockfd, 2);
            exit(0);
        }
        else if(c==CR||c==LF){
            write(STDOUT_FILENO, &CR, 1);
            write(STDOUT_FILENO, &LF, 1);
            c=LF;
            if(encryptcheck){
                mcrypt_generic(en, &c, 1);
            }
            write(sockfd, &c, 1);
            if(logcheck){
                write(log_fd, "SENT 1 bytes: ", 14);
                write(log_fd, &c, 1);
                if(c!=CR && c!=LF)
                    write(log_fd, "\n", 1);
            }
        }
        else{
            write(STDOUT_FILENO, &c, 1);
            if(encryptcheck)
                mcrypt_generic(en, &c, 1);
            write(sockfd, &c, 1);
            if(logcheck){
                write(log_fd, "SENT 1 bytes: ", 14);
                write(log_fd, &c, 1);
                write(log_fd, "\n", 1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    static struct option long_options[] = {
        { "port", required_argument, NULL, 'p'},
        { "log" , required_argument, NULL, 'l'},
        { "encrypt" , no_argument, NULL, 'e'},
        {0,0,0,0},
    };
    int val = 0;
    while(1)
    {
        val = getopt_long(argc, argv, "", long_options, NULL);
        if(val == -1)
            break;
        switch(val){
            case 'p':
                portcheck = 1;
                portnum = atoi(optarg);
                break;
            case 'l':
                logcheck = 1;
                arg=optarg;
                break;
            case 'e':
                encryptcheck = 1;
                break;
        }
        
        
    }
    if(portcheck==0){
        fprintf(stderr, "No port specified. Exiting from client.\n");
        exit(1);
    }
    
    if(logcheck){
        log_fd=creat(arg,0666);
    }
    
    set_input_mode ();
    
    /*The following incorporates code from the unix sockets client example*/
    ///////////////////////////////////////////////////////////////////////
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "Error! Problem opening socket\n");
        exit(1);
    }
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"Error! Problem finding host\n");
        exit(0);
    }
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(portnum);
    
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        fprintf(stderr, "Error! Problem connecting to server\n");
        exit(1);
    }
    if(encryptcheck==1){
        int keysize=16; //128 bits
        int kfd;
        char* key;
        key=calloc(1, keysize);
        kfd=open("my.key", O_RDONLY);
        if(kfd<0){
            fprintf(stderr, "Error opening my.key.\n");
            exit(1);
        }
        char pwd[20];
        read(kfd, &pwd, strlen(pwd));
        memmove(key, pwd, strlen(pwd));
        en=mcrypt_module_open("twofish", NULL, "cfb", NULL);
        if(en==MCRYPT_FAILED){
            fprintf(stderr, "Error opening encryption module.\n");
            exit(1);
        }
        char* IV;
        IV=(char*) malloc(mcrypt_enc_get_iv_size(en));
        int i;
        for(i=0; i<mcrypt_enc_get_iv_size(en);i++){
            IV[i]=rand();
        }
        int k;
        k=mcrypt_generic_init(en, key, keysize, IV);
        if(k<0){
            mcrypt_perror(k);
            exit(1);
        }
    }
    
    pthread_t newThreadID;
    pthread_create(&newThreadID, NULL, newThreadFunc, NULL);
    readFile();
    return 0; 
}
