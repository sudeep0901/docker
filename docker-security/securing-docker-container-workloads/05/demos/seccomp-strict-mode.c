#include <stdio.h>                  // Required by printf and perror
#include <fcntl.h>                  // Required by open
#include <sys/syscall.h>            // Required by syscall
#include <sys/prctl.h>              // Required by prctl
#include <linux/seccomp.h>          // Require for SECCOMP_MODE_STRICT constant
#include <stdlib.h>                 // Required for exit status constants
#include <unistd.h>                 // Required by syscall, read and close

int main() {

    int     fd, i = 0;
    ssize_t ret;
    char    c;
    char    buff[100];

    printf(">> Right now, we can make all system calls, let's open a file for reading.\n");

    if ((fd = open("/etc/passwd", O_RDONLY)) == -1) {
        perror("Failed to open file");
        syscall(SYS_exit, EXIT_FAILURE);
    }

    printf(">> Used the open() system call to open the /etc/passwd file for reading.\n");

    if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT) == -1) {
        perror("Failed to set seccomp strict mode");
        syscall(SYS_exit, EXIT_FAILURE);
    }

    printf(">> Now in seccomp strict mode, but still able to read from /etc/passwd file.\n");

    while ((ret = read(fd, &c, 1)) > 0 && c != '\n') {
        buff[i] = c;
        i++;
    }

    if (ret == -1) {
        perror("Failed to read first line of file");
        syscall(SYS_exit, EXIT_FAILURE);
    }

    buff[i] = '\0';

    printf(">> Read /etc/passwd, the entry for UID=0: '%s'.\n", buff);
    printf(">> Attempting to close /etc/passwd, using close() system call.\n");

    if (close(fd) == -1) {
        perror("Failed to close file");
        syscall(SYS_exit, EXIT_FAILURE);
    }

    printf(">> Successfully closed the /etc/passwd file using the close() system call.\n");

    syscall(SYS_exit, EXIT_SUCCESS);
    
}
