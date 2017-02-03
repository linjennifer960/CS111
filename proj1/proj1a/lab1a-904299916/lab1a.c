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

/*the following section incorporates code from gnu manual chp17.7*/
/////////////////////////////////////////////////////////////////////
struct termios saved_attributes;
int shell=0;
pid_t pid;
void reset_input_mode (void){
  if(shell){
    int status;
    waitpid(pid, &status, 0);
    if(WIFEXITED(status))  //exit normally
      fprintf(stderr,"Normal exit, shell exit status: %d\n",WEXITSTATUS(status));
    else
      fprintf(stderr,"Terminated by signal: %s (%d)\n", strsignal(WTERMSIG(status)), WTERMSIG(status));
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode(void){
  struct termios tattr;
  
  /* save the terminal attributes so we can restore them later*/
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, & tattr);
  tattr.c_lflag &= ~(ICANON|ECHO);
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}
char EOT=0x4;
int check;
///////////////////////////////////////////////////////////////////
void* newThreadFunc(void *arg){
  int *input=(int *)arg;
  char c;
  int test;
  char a='\0';
  while(1){
    test=read(*input, &c, 1);
    /*if(test<0)
      break;
    else if(test==0){
      atexit(reset_input_mode);
      exit(1);
     }
    else if(c==EOF){
      //restore terminal mode, exit with code 1
      atexit(reset_input_mode);
      exit(1);
      }
    else
      write(STDOUT_FILENO, &c, 1);*/
    if(test>0 && c!=EOT)
      write(STDOUT_FILENO, &c, 1);
    if(test==0){
      check=1;
      break;
    }
  }
  return (void*)0;
}

void pipe_handler(int signum){
  //fprintf(stderr, "SIGPIPE\n");
  exit(1);
}

int main(int argc, char *argv[]){
  struct option long_options[]={
    {"shell", no_argument, NULL, 'i'},   //shell option
    {0,0,0,0}
  };
  int val=0;
  while (1){
    val = getopt_long(argc, argv, "", long_options, NULL);
    if(val == -1)
      break;
    switch(val){
    case 'i':
      shell=1;
      break;
    default:
      break;
    }
  }
  set_input_mode();
  //char EOT=0x4;   //^D
  char CR=0xD;   
  char LF=0xA;
  char ETX=0x3;   //^C
  //////////////////////////if shell option//////////////////////////
  /*the following code about pipes incorporates sample code from TA*/
  if(shell){
    int to_child_pipe[2];         //add pipes
    int from_child_pipe[2];
    pid_t child_pid;
    if(pipe(to_child_pipe) <0){
      fprintf(stderr, "Error creating pipe!\n");
      exit(1);
    }
    if(pipe(from_child_pipe) <0){
      fprintf(stderr, "Error creating pipe!\n");
      exit(1);
    }
    child_pid=fork();     //fork to create new process
    if(child_pid > 0) {   //parent
      signal(SIGPIPE, pipe_handler);
      close(to_child_pipe[0]);  
      close(from_child_pipe[1]);
      
      //thread for reading from shell pipe
      pthread_t newThreadID;
      pthread_create(&newThreadID, NULL, newThreadFunc, &from_child_pipe[0]);

      //for reading from keyboard
      char c;
      char j='j';
      while(1){
	/*if(check){
	  write(to_child_pipe[1],&j,1);
	  }*/
	if(read(STDIN_FILENO, &c, 1)<0){
	  fprintf(stderr, "Read from child failed\n");
	  exit(1);
	}
	if(c==CR || c==LF){ //echo as <cr><lf>, go to shell as <lf>
	  write(STDOUT_FILENO, &CR, 1);
	  write(STDOUT_FILENO, &LF, 1);
	  write(to_child_pipe[1], &LF, 1);
	}else if(c==ETX){ //^C
	  kill(child_pid, SIGINT);
	  break;
	}else if(c==EOT){ //^D
	  //close pipe, send SIGHUP to shell, restore terminal modes
	  //atexit(reset_input_mode);
	  close(to_child_pipe[1]);
	  close(from_child_pipe[0]);
	  kill(child_pid, SIGHUP);
	  exit(0);
	}else{  //echo to stdout & forward to shell
	  write(STDOUT_FILENO, &c, 1);
	  write(to_child_pipe[1], &c, 1);
	}
      }

    } else if(child_pid==0) {     //child
      close(to_child_pipe[1]);
      close(from_child_pipe[0]);
      dup2(to_child_pipe[0], STDIN_FILENO);
      dup2(from_child_pipe[1], STDOUT_FILENO);
      close(to_child_pipe[0]);
      close(from_child_pipe[1]);

      char *execvp_argv[2];
      char execvp_filename[] = "/bin/bash";
      execvp_argv[0]=execvp_filename;
      execvp_argv[1]=NULL;
      if(execvp(execvp_filename, execvp_argv)==-1){
	fprintf(stderr, "execvp failed \n");
	exit(1);
      }
    } else{
      fprintf(stderr, "fork failed\n");
      exit(1);
    }
    return 0;
  }

  ////////////////////////////no shell/////////////////////////////////
   if(!shell){   //no --shell
     char c;
    while(1){
      if(read (STDIN_FILENO, &c, 1) < 0){
	fprintf(stderr, "Error reading stdin \n");
	exit(1);
      }
      if(c== EOT){   //^D
	atexit(reset_input_mode);
	exit(0);
      }
      else if (c==CR || c==LF){ //for cr and lf
	write(STDOUT_FILENO, &CR, sizeof(char));
	write(STDOUT_FILENO, &LF, sizeof(char));
      }
      else
	write(STDOUT_FILENO, &c, sizeof(char));
    }
  }
  return 0;
}
    
