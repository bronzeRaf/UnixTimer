//Mprouzos Rafail 7945
#include <sys/types.h> 
#include <sys/time.h> 
#include <sys/times.h> 
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#define BUF 50

//global variable declaration
int fd[2],status=0;
struct timeval takeTime,takeTime2;
struct tms cpuTake;
clock_t cpuS;

//function declaration
void child(int argc, char **argv);
double getStart();
void parent();

//main function
int main(int argc, char **argv){
  pid_t pid;
  
  if (pipe(fd) < 0){ perror("creating pipe"); exit(1); }//error on creating pipe
  
  if ((pid = fork()) < 0){ perror("cannot fork"); exit(1); }//error on fork
  else if(pid>0){//parent process
	parent();
  }
  else{//child process
  	child(argc,&argv[0]);
  }
  //exiting parent process now (after returning from parent() )...
}

//receives from child (with the pipe) process the starting time value and makes it a double value. It returns this value
double getStart(){
  int n;
  double sTime;
  char line[BUF];

  close(fd[1]);//close writing end
  n = read(fd[0], line, BUF);//take the message from child
  close(fd[0]);//close read end
  sTime= atof(line);//make the received string a double value
  return sTime;
}

//child process function. Takes begin time, send this time at parent process and executes the program with its parameters
void child(int argc, char **argv){
  double p;
  char line[BUF];
  
  close(fd[0]);//close reading end
  //take the starting time
  gettimeofday (&takeTime, NULL);
  //make the starting time a float value 
  p = (double)((takeTime.tv_usec)/1.0e6 + takeTime.tv_sec);
  //make the string for sending
  sprintf(line,"%lf",p);
  write(fd[1], line, strlen(line)+1);//send the time as string message
  close(fd[1]);//close writing  end
  //executing program with execv
  execv(argv[1],&argv[1]);
  //exiting for child process
  exit(0);
}

//parent process function. Takes cpu time (user and system), wait child to die and calculates the real (wall clock) time value. Print the result (time values)
void parent(){
  double sTime,eTime,realTime,cpuUser,cpuSystem;
  
  sTime= getStart();//start time
  //waiting child to die
  wait(&status);
  //take the ending time
  gettimeofday(&takeTime2, NULL);
  //make the ending time a double value 
  eTime = (double)((takeTime2.tv_usec)/1.0e6 + takeTime2.tv_sec);
  realTime=eTime-sTime;
  //print result wall clock time
  printf("Real wall clock time for execution is %lf \n",realTime);
  
  //cpu time
  cpuS=times(&cpuTake);
  if (cpuS < 0)//if times fail
	perror("times error");
  else {//if times is ok
	cpuUser=((double) cpuTake.tms_cutime)/CLOCKS_PER_SEC;
	cpuSystem=((double) cpuTake.tms_cstime)/CLOCKS_PER_SEC;
  }
  printf("CPU system time for executing is %lf \n",cpuSystem);
  printf("CPU user time for executing is %lf \n",cpuUser);
}

