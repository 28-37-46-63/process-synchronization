#include<iostream>
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define MAX_ITEMS 5
using namespace std;


int fd;
char *itemProduced;
bool locking;
char buffer[100];
void producer();
void consumer();
void mylock();
void my_unlock();


int main(int argc,char *argv[])
{
  int pid,shmid;

  shmid=shmget(IPC_PRIVATE,10,IPC_CREAT|0666);
  itemProduced=(char*)shmat(shmid,NULL,0);
  strcpy(itemProduced,"false");

  fd= open("abc", O_CREAT|O_RDWR,0666);

  if(argc==1)
    locking=false;
  else
    locking=true;

  pid=fork(); 
  int first = 1;

  if(pid==0){
	
    consumer();
  }
  else
  {
	//sleep(1);	
	producer();
    wait(0);
  }
}



void producer()
{
 int i=1, nextItem=1;

 while(nextItem<=MAX_ITEMS)
 {
   if(locking && strcmp(itemProduced,"true")==0)
     continue;

   mylock();
   sleep(1);
   lseek(fd,0L,0);
   memset(buffer,'\0',sizeof(buffer));
   sprintf(buffer,"%d\n",nextItem++);
   write(fd,buffer,(strlen(buffer)+1));
   cout<<"Producer produced: ("<<i++<< "):"<<buffer<<endl;
   strcpy(itemProduced,"true");
   my_unlock();
 }
   shmdt(itemProduced);
}


void consumer()
{
 int i=1, nextItem=1;

 while(i<=MAX_ITEMS)
 {
   if(locking && strcmp(itemProduced,"false")==0)
     continue;

   mylock();
   sleep(1);
   lseek(fd,0L,0);
   read(fd,buffer,sizeof(buffer));
   cout<<"Consumer consumed: ("<<i++<< "):"<<buffer<<endl;
   strcpy(itemProduced,"false");
   my_unlock();
 }
   shmdt(itemProduced);
}


void mylock()
{
  if(locking)
  {
    lseek(fd,0L,0);
    if(lockf(fd,F_LOCK,0L)==-1)
       cout<<"Cannot lock";
  }
}


void my_unlock()
{
  if(locking)
  {
    lseek(fd,0L,0);
    if(lockf(fd,F_ULOCK,0L)==-1)
       cout<<"Cannot lock";
  }
}
