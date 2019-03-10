#include <stdio.h>                  // Required by printf and perror
#include <fcntl.h>                  // Required by open
#include <sys/syscall.h>            // Required by syscall
#include <seccomp.h>                // Require by libseccomp functions
#include <stdlib.h>                 // Required for exit status constants
#include <unistd.h>                 // Required by syscall, read and close

int main() {

    int             fd, i = 0;
    ssize_t         ret;
    char            c;
    char            buff[100];
    scmp_filter_ctx ctx;

    printf(">> Right now, we can make all system calls, let's open a file for reading.\n");

    if ((fd = open("/etc/passwd", O_RDONLY)) == -1) {
        perror("Failed to open file");
        syscall(SYS_exit, EXIT_FAILURE);
    }

    printf(">> Used the open() system call to open the /etc/passwd file for reading.\n");

    if ((ctx = seccomp_init(SCMP_ACT_KILL)) == NULL) {
        perror("Failed to initialise seccomp filter state");
        exit(EXIT_FAILURE);
    }

    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0) < 0) {
        perror("Failed to add seccomp rule to filter");
        exit(EXIT_FAILURE);
    }

    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0) < 0) {
        perror("Failed to add seccomp rule to filter");
        exit(EXIT_FAILURE);
    }

    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0) < 0) {
        perror("Failed to add seccomp rule to filter");
        exit(EXIT_FAILURE);
    }

    if (seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(rt_sigreturn), 0) < 0) {
        perror("Failed to add seccomp rule to filter");
        exit(EXIT_FAILURE);
    }

    if (seccomp_load(ctx) < 0) {
        perror("Failed to load seccomp filter");
        exit(EXIT_FAILURE);
    }

    printf(">> Now in seccomp filter mode, but still able to read from /etc/passwd file.\n");

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
