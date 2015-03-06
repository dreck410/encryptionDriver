#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    printf("%s\n",argv[1]);
	int fd = open("/dev/encrypt", O_RDWR);

	if (fd == -1) {
        perror("Unable to open device");
        exit(1);
    }

    int result = write(fd, argv[1], strlen(argv[1]));

    if (result != strlen(argv[1])) {
		perror("problem writing to device");
		printf("result = %d\n", result);
	}
	char* buf = malloc(strlen(argv[1] + 1));
	read(fd, buf, result);
	puts(buf);
	close(fd);
}