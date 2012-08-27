#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE* archivo = fopen("lila.txt","r");
  char * buffer = NULL;
  int i, c;
  c = fgetc(archivo);
  while(!feof(archivo))
    {
      buffer = (char*)realloc(NULL, sizeof(char));
        i = 0;
      while( c != '\n')
        {
          buffer[i] = c;
          i++;
          buffer = (char*)realloc(buffer, (i+1)*sizeof(char));
          c = fgetc(archivo);
        }
      /*Agrego el \n al buffer*/
      buffer = (char*)realloc(buffer, (i+2)*sizeof(char));
      buffer[i] = c;
      buffer[i+1] = 0;
      /*Trabajar con el buffer*/
      printf("%s", buffer);
      free(buffer);
      c = fgetc(archivo);
    }
  //close(archivo);
}
