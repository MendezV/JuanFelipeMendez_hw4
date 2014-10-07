/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
int main(void)
{
  DIR           *d;
  struct dirent *dir;
char *file;
    
    FILE *in;
    int i;
    char filename[100]="list.dat";
    
    printf("Writing to file: %s\n", filename);
  
    in = fopen(filename,"w");
    if(!in){
        printf("problems opening the file %s\n", filename);
        exit(1);
    }

  d = opendir("Brahe-3141-f");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      file=dir->d_name;
      if (strcmp(file, ".") != 0 && strcmp(file, "..") != 0 )
      if (strcmp(file, ".DS_Store") != 0 ) 
      fprintf(in, "%s\n", file);
    }

    closedir(d);
  }

  return(0);
}
