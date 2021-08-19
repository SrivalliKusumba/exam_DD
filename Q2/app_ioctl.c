#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define write_value _IOW('a','a',char *)
#define read_value _IOR('a','b',char *)

int main()
{
	int fd;
	char buff[100];
	char x[] = "op1";
	

	fd = open("/dev/mychar",O_RDWR);
	
	if(fd<0)
	{
		printf("Error opening the file\n");
		exit(1);
	}

	ioctl(fd, write_value, (char *)&x);

	ioctl(fd, read_value, (char *)&buff);

	printf("buff = %s\n",buff);
	

	close(fd);
	return 0;
}
