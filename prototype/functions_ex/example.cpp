#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main(){
	
	char *args[] = {"./exec", NULL};
	int status;

	pid_t pid, wpid;
	
	pid = fork();

	if(pid == -1){
		perror("forking");
		exit(EXIT_FAILURE);
	}
	
	if(pid == 0){
		execvp(args[0],args);
	}
	wpid = waitpid(pid, &status, 0);

	if(wpid == -1){

		perror("waitpid");
		exit(EXIT_FAILURE);
	}

	if(WIFEXITED(status)){

		int exit_status = WEXITSTATUS(status);
		printf("Exit Status: %d", exit_status);

	}
	else{

		perror("Error: ASA");
	}

	exit(EXIT_SUCCESS);
	return 0;
}

