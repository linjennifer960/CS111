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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mcrypt.h>

int sockfd, newsockfd;
int to_child_pipe[2];
int from_child_pipe[2];
int portcheck=0;
int portnum;
int check = 0;
pid_t child_pid;
int encryptcheck = 0;
MCRYPT en;
struct termios saved_attributes;


void *newThreadFunc(void *arg)
{
    char c;
    int test;
    while(1)
    {
        test = read(from_child_pipe[0], &c, 1);
        if(test == 0){
            check=1;
            break;
        }
        else if(test <0)
            break;
        else {  //test>0
            if(encryptcheck)
                mcrypt_generic(en, &c, 1);
            write(STDOUT_FILENO, &c, 1);
        }
    }
    return (void*)0;
}

void pipe_handler(int signum)
{
    shutdown(sockfd, 2);
    shutdown(newsockfd, 2);
    close(to_child_pipe[1]);
    close(from_child_pipe[0]);
    exit(2);
}

void parentFunc(void){
    char c;
    while(1){
        int foo=read(STDIN_FILENO, &c, 1);
        if(foo<=0){
            shutdown(sockfd, 2);
            shutdown(newsockfd,2);
            close(to_child_pipe[1]);
            close(from_child_pipe[0]);
            exit(1);
            break;
        }
        if(check){
            shutdown(sockfd, 2);
            shutdown(newsockfd, 2);
            close(to_child_pipe[1]);
            close(from_child_pipe[0]);
            exit(2);
            break;
        }
        else{
            if(encryptcheck)
                mdecrypt_generic(en, &c, 1);
            write(to_child_pipe[1], &c, 1);
        }
    }
}

void parentCloseDups(void){
    close(to_child_pipe[0]);
    close(from_child_pipe[1]);
    dup2(newsockfd, STDIN_FILENO);
    dup2(newsockfd, STDOUT_FILENO);
    dup2(newsockfd, STDERR_FILENO);
    close(newsockfd);
}

void childCloseDups(void){
    close(to_child_pipe[1]);
    close(from_child_pipe[0]);
    dup2(to_child_pipe[0], STDIN_FILENO);
    dup2(from_child_pipe[1], STDOUT_FILENO);
    dup2(from_child_pipe[1],STDERR_FILENO);
    close(to_child_pipe[0]);
    close(from_child_pipe[1]);
}

int main(int argc, char *argv[])
{
    static struct option long_options[] = {
        { "port", required_argument, NULL, 'p'},
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
            case 'e':
                encryptcheck = 1;
                break;
        }
    }
    if(portcheck==0){
        fprintf(stderr, "No port number specified. Exiting from server.\n");
        exit(1);
    }
    
    if(pipe(to_child_pipe) < 0 || pipe(from_child_pipe) < 0)
    {
        fprintf(stderr, "Error creating pipe.\n");
        exit(1);
    }
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        fprintf(stderr, "Error opening socket.\n");
        exit(1);
    }
   	memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portnum);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding. \n");
        exit(1);
    }
    listen(sockfd,5);
    socklen_t clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if(newsockfd<0){
        fprintf(stderr, "Error on accept");
        exit(1);
    }
    
    if(encryptcheck){
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
    child_pid=fork();     //fork to create new process
    if(child_pid > 0) {   //parent
        signal(SIGPIPE, pipe_handler);
        
        parentCloseDups();
        
        pthread_t newThreadID;
        pthread_create(&newThreadID, NULL, newThreadFunc, NULL);
        parentFunc();
    }
    else if(child_pid==0) {     //child
        
        childCloseDups();
        
        char *execvp_argv[2];
        char execvp_filename[] = "/bin/bash";
        execvp_argv[0]=execvp_filename;
        execvp_argv[1]=NULL;
        if(execvp(execvp_filename, execvp_argv)==-1){
            fprintf(stderr, "execvp failed \n");
            exit(1);
        }
    }
    else{
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    return 0;
}
