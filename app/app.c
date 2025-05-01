#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(){
	int fd = open("/dev/mydev1", O_RDWR);
	if(fd<0)exit(1);

	int led = 0;
	while(1){
		scanf("%d", &led);
		if(led==1){
			ioctl(fd, _IO(3,0), 0);
		} else if(led==0){
			ioctl(fd, _IO(4,0), 0);
		} else {
			break;
		}
	}
	
	close(fd);

	return 0;
}