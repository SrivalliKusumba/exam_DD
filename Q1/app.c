#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int fd;
	char Ubuff[] = "User application";
	char kbuff1[100];
	char kbuff2[100];
	fd = open("/dev/mychar",O_RDWR,0777);
	if(fd<0)
	{
		printf("Error opening the file\n");
		exit(1);
	}
	if(fork() == 0)
	{
	write(fd,Ubuff,sizeof(Ubuff));
	read(fd,kbuff1,100);
	printf("Data read %s\n",kbuff1);
	exit(0);
	}
	else
	{
		write(fd,Ubuff,sizeof(Ubuff));
		read(fd,kbuff2,100);
		printf("Data read is %s\n",kbuff2);
		wait(NULL);
	}
	
	close(fd);
}
