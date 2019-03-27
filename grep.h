//Kevin Cervantes González
//311045075
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

void grep(const char * arg) {

	bool noEspacio=true;
	char palabra[100];
	char archivo[100];
	int j =0;
	for(int i = 0; i < strlen(arg); i++){
  		if(noEspacio){
    		palabra[i]=(arg[i]);
    		if(isspace(arg[i])){
      			palabra[i]='\0';
      			noEspacio=false;
      		}
    	} else {
        	archivo[j]=(arg[i]);
        	j++;
        	if(isspace(arg[i+1])){
          		archivo[j]='\0';
          		break;
        	}	
  		}
  	}
	
   FILE *fp;
   char * linea = NULL;
   size_t longitud = 0;
   ssize_t lectura;

   fp = fopen(archivo, "r");
   if (fp == NULL) {
      perror("Error. Directorio no encontrado\n");
      exit(EXIT_FAILURE);
   }

   int i=0;
   while ((lectura = getline(&linea, &longitud, fp)) != -1) {
     char *resultado = strstr(linea,palabra);
     if(resultado != NULL) {
       printf("linea numero %d %s\n", i, linea);
     }
     i++;
   }

   fclose(fp);
}

