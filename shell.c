//Kevin Cervantes González
//311045075
#include <stdio.h>
#include "grep.h"

void ls() {
	int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
    	execl("/bin/ls","/bin/ls",NULL,NULL);
    	exit(EXIT_FAILURE);    	
    } else if (pid < 0) {
    	printf("Error\n");
      	status = -1;
    } else {
    	if(waitpid(pid,&status,0) != pid){
        	printf("Error 2\n");
        	status = -1;
      	}
    }

    return status;
}


void pwd() {
    int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
    	char path[1024];
    	getcwd(path, sizeof(path));
    	printf("%s\n", path);
    	exit(EXIT_FAILURE); //salida del proceso hijo
    } else if (pid < 0) {
    	printf("Error\n");
      	status = -1;
    } else {
    	if(waitpid(pid,&status,0) != pid){
        	printf("Error 2\n");
        	status = -1;
      	}
    }

    return status;
}

void cat(const char * arg) {
	int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
    	bool unArchivo = true;
    	bool noEspacio = true;
    	char archivo1[100];
    	char archivo2[100];
    	int j=0;
    	for(int i = 0; i < strlen(arg); i++){
      		if(noEspacio){
        		archivo1[i]=(arg[i]);
        		if(isspace(arg[i])) {
          			archivo1[i]='\0';
          			noEspacio=false;
          			unArchivo=false;
        		}
        	} else {
        		archivo2[j]=(arg[i]);
        		j++;
        		if(isspace(arg[i+1])){
          			archivo2[j]='\0';
          			break;
        		}
        	}
          	 
        }

    	if (unArchivo) {
    		execl("/bin/cat", "/bin/cat", archivo1, NULL, NULL);
    		exit(EXIT_FAILURE); //salida del proceso hijo
    	} else {
    		execl("/bin/cat", "/bin/cat", archivo1, archivo2, NULL);
    		exit(EXIT_FAILURE); //salida del proceso hijo
    	}

    		
    	
    } else if (pid < 0) {
    	printf("Error\n");
      	status = -1;
    } else {
    	if(waitpid(pid,&status,0) != pid){
        	printf("Error 2\n");
        	status = -1;
      	}
    }

    return status;
	
}

void cp(const char * arg) {
	int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
    	bool noEspacio = true;
    	char archivo[100];
    	char dir[100];
    	int j=0;
    	for(int i = 0; i < strlen(arg); i++){
      		if(noEspacio){
        		archivo[i]=(arg[i]);
        		if(isspace(arg[i])) {
          			archivo[i]='\0';
          			noEspacio=false;
        		}
        	} else {
        		dir[j]=(arg[i]);
        		j++;
        		if(isspace(arg[i+1])){
          			dir[j]='\0';
          			break;
        		}
        	}
          	 
        }

    	execl("/bin/cp", "/bin/cp", archivo, dir, NULL);
    	exit(EXIT_FAILURE); //salida del proceso hijo

    		
    	
    } else if (pid < 0) {
    	printf("Error\n");
      	status = -1;
    } else {
    	if(waitpid(pid,&status,0) != pid){
        	printf("Error 2\n");
        	status = -1;
      	}
    }

    return status;
	
}

void grepMain(const char * arg){
  grep(arg);
}


int shell() {
	char buffer[1024];
	while(1) {
		printf("kevinshell-1.0$ ");
		fgets(buffer, 1024, stdin);
		if(strncmp(buffer, "exit", 4) == 0) {
			exit(0);
		} else if(strncmp(buffer, "ls", 2) == 0){
			ls();
		} else if(strncmp(buffer, "pwd", 3) == 0){
			pwd();
		} else if(strncmp(buffer, "cat", 3) == 0){
			cat(buffer + 4);
		} else if(strncmp(buffer, "cp", 2) == 0){
			cp(buffer + 3);
		} else if(strncmp(buffer, "grep", 4) == 0){
			grepMain(buffer + 5);
		} else {
			printf("Error. Comando no conocido\n");
		}
	}

	return 1;
}

int main() {
	shell();
}