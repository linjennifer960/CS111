#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/stat.h>

void segfaultHandler(int signum){
    fprintf(stderr, "Received signal number %d, quitting now. \n", signum);
    exit(3);
}

int main(int argc, char *argv[]){
  if(argc==1)
    exit(0);
  struct option long_options[] = {
    {"input", required_argument, NULL, 'i'},
    {"output", required_argument, NULL, 'o'},
    {"segfault", no_argument, NULL, 's'},
    {"catch", no_argument, NULL, 'c'},
    {0,0,0,0}
  };

  int val=0;
  int my_fd=0;
  int caseS=0;
  while(1){
    val = getopt_long(argc, argv, "", long_options, NULL);
    if(val == -1)
      break;
    switch(val){
    case 'i':{
      my_fd = open(optarg,O_RDONLY);
      if(my_fd<0){
	fprintf(stderr, "Error when opening file \n");
	perror("Error when opening file \n");
	exit(1);
      }
      dup2(my_fd, 0);
      break;
    }	
    case 'o':{
      my_fd = creat(optarg, 0644);
      if(my_fd<0){
	fprintf(stderr, "Error creating file \n");
	perror("Error creating file \n");
	exit(2);
      }
      dup2(my_fd, 1);
      break;
    } 
    case 's':{
      caseS=1;
      break;
    }
    case 'c':{
      if(argc==2){
	exit(0);
	break;
      }
      else{
	signal(SIGSEGV, segfaultHandler);
	break;
      }
    }
    default:
      exit(0);
    }
  }
  if(caseS){
    char* seg = NULL;
    *seg = 'j';
  }
  char buf[1];
  while(read(0, buf,1)>0)
    write(1,buf,1);
  exit(0);
}
