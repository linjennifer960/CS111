#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <mraa/aio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <math.h>
#include <getopt.h>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>

const int B=4275;                 // B value of the thermistor
int run_flag = 1;
int freq = 3;                     // default frequency
int stop = 0;
int scale = 0;                    // default temp scale = fahrenheit
int sockfd;
int n_port;
FILE* fd;
char* command[5]={"OFF", "STOP", "START", "SCALE", "FREQ"};
fd_set rfds;
int retval;
mraa_aio_context rotary;
uint16_t value;


void sockets(void){
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        fprintf(stderr, "Socket opening error\n");
        exit(1);
    }
    server = gethostbyname("lever.cs.ucla.edu");
    if (server == NULL) {
        fprintf(stderr,"Cannot find host\n");
        exit(1);
    }
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(16000);
    
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    char req[22] = "Port request 904299916";
    write(sockfd, &req , sizeof(req));
    read(sockfd, &n_port, sizeof(n_port));
}

void *thread_func(void *arg)
{
    while(fd && run_flag){
        //stop command used
        while(stop)
            continue;
        value = mraa_aio_read(rotary);
        float R = 1023.0/((float)value)-1.0;
        R = 100000.0*R;
        float temperature=1.0/(log(R/100000.0)/B+1/298.15)-273.15;
        
        //convert to Fahrenheit
        if(scale == 0)
            temperature = temperature*9.0/5.0+32;
        
        char* time_str;
        time_str = malloc(9);
        time_t time_1 = time(NULL);
        struct tm *time_2 = localtime(&time_1);
        strftime(time_str, 9, "%H:%M:%S", time_2);
        
        //Celsius
        if(scale == 1){
            printf("%s %.1f C\n", time_str, temperature);
            fprintf(fd, "%s %.1f C\n", time_str, temperature);
        }
        //Fahrenheit
        else{
            printf("%s %.1f F\n", time_str, temperature);
            fprintf(fd, "%s %.1f F\n", time_str, temperature);
        }
        fflush(fd);
        
        char res[20] = {'\0'};
        sprintf(res,"904299916 TEMP=%.1f\n", temperature);
        write(sockfd, &res, sizeof(res));
        
        sleep(freq);
    }
    
    if(fd)
        fclose(fd);
    mraa_aio_close(rotary);
    return NULL;
}

void checkCommands(void){
    //from man page of select2
    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    FD_SET(sockfd, &rfds);
    while(1){
        retval = select(sockfd + 1, &rfds, NULL, NULL, NULL);
        
        /*buffer to store command, should be at most 9 charcters, but initiate more
         in case of additional leading zeroes */
        char commandbuf[15] = {'\0'};
        
        if(retval!= -1 && FD_ISSET(sockfd, &rfds)){
            read(sockfd, &commandbuf, sizeof(commandbuf));
            fprintf(fd, "%s", commandbuf);
            printf("%s\n", commandbuf);
            
            //off
            if(strcmp(commandbuf, command[0]) == 0){
                run_flag = 0;
                exit(0);
            }
            //stop
            else if(strcmp(commandbuf, command[1]) == 0)
                stop = 1;
            //start
            else if(strcmp(commandbuf, command[2]) == 0)
                stop = 0;
            //scale
            else if(strncmp(commandbuf, command[3], 5) == 0){
                //check for char after equal sign (C or F)
                if(commandbuf[6] == 'C')
                    scale = 1;
                else
                    scale = 0;
            }
            //freq, check for number after equal sign
            else if(strncmp(commandbuf, command[4], 4) == 0){
                int i = 5;
                int num = 0;
                while(commandbuf[i] != '\0'){
                    num += num*10 + (commandbuf[i] - '0');
                    i++;
                }
                freq = num;
            }
            //invalid commands
            else
                fprintf(fd, " I");
            
            fprintf(fd, "\n");
            fflush(fd);
        }
    }
}

int main()
{
    sockets();
    
    printf("%d\n", n_port);
    struct sockaddr_in serv_addr;
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        fprintf(stderr, "Socket opening error\n");
        exit(1);
    }
    server = gethostbyname("lever.cs.ucla.edu");
    if (server == NULL) {
        fprintf(stderr,"Cannot find host\n");
        exit(1);
    }
    memset((char *) &serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
    serv_addr.sin_port = htons(n_port);
    
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    rotary = mraa_aio_init(0);
    fd = fopen("log2.txt","w+");
    
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    
    checkCommands();
    return 0;
}
