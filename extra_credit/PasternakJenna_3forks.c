#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
 {
  pid_t retVal;
  retVal = fork();
  //Fork 1
  if(retVal < 0){
    printf("fork() failed\n");
    return 1;
  }
  else if(retVal == 0){
    printf("fork1 retVal == 0 ");
    printf("in child process pid = %d \n", getpid() );
    printf("child sleeping ... \n" );
    sleep(5);
    printf(" finished sleeping\n" );
  }
  else {
    printf("parent pid = %d \n", getpid() );
    printf("fork1 in parent process waiting for child ...\n");
    wait(NULL);
    printf("wait() finished in parent process \n\n");
  }
 
  //Fork 2
  retVal = fork();
  if(retVal < 0){
    printf("fork() failed\n");
    return 1;
  }
  else if(retVal == 0){
    printf("fork2 retVal == 0 ");
    printf("in child process pid = %d \n", getpid() );
    printf("child sleeping ... \n" );
    sleep(5);
    printf(" finished sleeping\n" );
  }
  else {
    printf("parent pid = %d \n", getpid() );
    printf("fork2 in parent process waiting for child ...\n");
    wait(NULL);
    printf("wait() finished in parent process \n\n");
  }

  //Fork 3
  retVal = fork();
  if(retVal < 0){
    printf("fork() failed\n");
    return 1;
  }
  else if(retVal == 0){
    printf("fork3 retVal == 0 ");
    printf("in child process pid = %d \n", getpid() );
    printf("child sleeping ... \n" );
    sleep(5);
    printf(" finished sleeping\n" );
  }
  else {
    printf("parent pid = %d \n", getpid() );
    printf("fork3 in parent process waiting for child ...\n");
    wait(NULL);
    printf("wait() finished in parent process \n");
  }
  return 0;
}
