#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct flock fl = {F_WRLCK, SEEK_SET, 0, 100, 0};  // Initialize with write lock
    int fd;
    int fsize, offset;
    char buff[51];  // 50 characters + 1 for null terminator

    if ((fd = open(argv[1], O_RDWR)) == -1) {
        printf("Error Opening File\n");
        exit(1);
    }

    // Check if file is already locked
    fl.l_type = F_WRLCK;  // Check for write lock
    if (fcntl(fd, F_GETLK, &fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    if (fl.l_type == F_UNLCK) {
        printf("File not locked by any process\n");
        printf("Press Enter to lock the file\n");
        getchar();

        // Set exclusive write lock
        fl.l_type = F_WRLCK;
        fl.l_pid = getpid();

        if (fcntl(fd, F_SETLK, &fl) == -1) {
            printf("Cannot set exclusive lock\n");
            exit(1);
        }

        printf("File has been exclusively locked by process: %d\n", fl.l_pid);
    } else {
        printf("File is already locked by process: %d\n", fl.l_pid);
        close(fd);
        return 0;
    }

    printf("Press Enter to release lock\n");
    getchar();

    fl.l_type = F_UNLCK;  // Unlock
    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("Unlocking failed");
    } else {
        printf("File has been unlocked\n");
    }

    // Move to last 50 bytes and read them
    fsize = lseek(fd, 0, SEEK_END);
    offset = fsize > 50 ? fsize - 50 : 0;  // Ensure offset is within file size

    lseek(fd, offset, SEEK_SET);

    // Clear buffer and read up to 50 bytes
    memset(buff, 0, sizeof(buff));
    read(fd, buff, 50);
    
    printf("Last 50 bytes of the file is:\n");
    printf("%s\n", buff);

    close(fd);
    return 0;
}
