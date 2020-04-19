#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>

#define BUFFER_LENGTH 256
#define DEVICE_NAME "/dev/qmod"

#define DEBUG 1

static char buffer[BUFFER_LENGTH];

int main() {
    int ret, fd;
    char message[BUFFER_LENGTH];

    //   Open the device.
#ifdef DEBUG
    printf("Opening to %s...", DEVICE_NAME);
#endif
    fd = open(DEVICE_NAME, O_RDWR);
    if (fd < 0) {
        perror("Failed to open device...");
        return errno;
    }

#ifdef DEBUG
    printf("Reading from the device...\n");
#endif
    ret = read(fd, buffer, BUFFER_LENGTH);
    if (ret < 0){
        perror("Failed to read a message from the device.");
        return errno;
    }
    printf("%s\n", buffer);

    close(fd);
    return 0;
}
