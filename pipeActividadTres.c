#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

int main() 
{
  int pid;
  int file;
  srand(time(NULL));
  int randomNumber;
  char c[5];

  if(pipe(&file) == -1)
  {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  }

  switch(pid = fork())
  {
    case 0:
      // The child process will calculate if the number generate by the parent is more than or less than 500
      file = open("/home/asus/so/file.txt", O_RDONLY | O_EXCL);
      char number[5];
      read(file, number, strlen(c));
      int n2 = strtol(number, NULL, 10);
      if(n2 < 500)
      {
        printf("menor que 500\n");
      }
      else
      {
        printf("mayor o igual a 500\n");
      }
      close(file);

    default:
      // The parent process will generate a random number between 1 and 1000.
      randomNumber = rand() % 1000 + 1;
      sprintf(c, "%d", randomNumber);
      file = open("/home/asus/so/file.txt", O_CREAT | O_RDWR | O_TRUNC);
      write(file, c, strlen(c));
      close(file); 
  }
}
