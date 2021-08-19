#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

//#define write_value _IOW('a','a',char *)
//#define read_value _IOR('a','b',char *)

int main()
{
	int fd;
	char Ubuff[100];
	//char Ubuff[] "Write application";

	fd = open("/dev/mychar",O_RDONLY);
	
	if(fd<0)
	{
		printf("Error opening the file\n");
		exit(1);
	}

	read(fd, Ubuff, sizeof(Ubuff));
	printf("Data read : %s\n",Ubuff);

	close(fd);
	return 0;
}
