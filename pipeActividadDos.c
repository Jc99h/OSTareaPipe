#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main() {

  pid_t pid;
  int fd[2];
  char *const cmdChild[] = {"sort", NULL};
  char *const cmdParent[] = {"cat", "/etc/hosts", NULL};

  if(pipe(fd) == -1)
  {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  }

  switch(pid = fork())
  {
    case 0:
      // The child process will execute sort.
      // Close the pipe write descriptor.
      close(fd[WRITE]);
      // Redirect STDIN to read from the pipe.
      dup2(fd[READ], STDIN_FILENO);
      // Execute sor
      execvp(cmdChild[0], cmdChild);

    case -1:
      perror("fork() failed");
      exit(EXIT_FAILURE);

    default:
      // The parent process will execute cat /etc/hosts.
      // Close the pipe read descriptor.
      close(fd[READ]);
      // Redirect STDOUT to write to the pipe.
      dup2(fd[WRITE], STDOUT_FILENO);
      // Execute cat /etc/hosts
      execvp(cmdParent[0], cmdParent);
  }
}
