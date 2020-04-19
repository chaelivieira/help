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

int main(int argc, char* argv[]) {
    int ret, fd;
    char message[BUFFER_LENGTH];

    if (argc != 2) {
        printf("Usage: qadd message\n");
        return -1;
    }

    //   Open the device.
#ifdef DEBUG
    printf("Opening to %s...", DEVICE_NAME);
#endif
    fd = open(DEVICE_NAME, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open device...");
        return errno;
    }

    //   Write to the device.
#ifdef DEBUG
    printf("Sending: [%s]\n", argv[0]);
#endif
    ret = write(fd, argv[1], strlen(argv[1]));
    if (ret < 0) {
        perror("Failed to write the message to the device.");
        return errno;
    }

    close(fd);
    return 0;
}
