#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h> 
#include <pwd.h>
#define clean() printf("\033[H\033[J")

int main (int argc, char **argv, char **envp) 
{

	char cmd[1024];
	char cmd2[1024]; // just to keep the original value of cmd intact.
	char* home_dir;
	char* pch;
	char* first_command;
	char* second_command;
	char cwd[1024];
	char charTotext[1024];
	
	//printf("%s", argv[1]);
	//if(strcmp(argv[1], "<") == 0) printf("%s", argv[2]);
	
	
	clean();
	
	while (true)
	{
		printf("> ");
		
		fgets(cmd, sizeof cmd, stdin);
		cmd[strlen(cmd)-1] = '\0'; 	// make the last character '\0'
		
		strcpy(cmd2, cmd); // Keep the original value of cmd in cmd2 before the mutations
		
		pch = strtok(cmd, " ");
		int i=0;
		while (pch != NULL)
  		{
    		if(i==0)
    		{
    			first_command= pch;
    		}
    		if(i==1)
    		{
    			second_command = pch;
    		}
    		if(i > 1 && strcmp(first_command, "cd") ==0)
    		{
				strcpy(charTotext, pch);
    			second_command = strcat(second_command, " ");
    			second_command = strcat(second_command, charTotext);
    		}
    		pch = strtok (NULL, " ");
    		
  		i++;	
  		}
		else if(strcmp(first_command, "fork") == 0)
		{
			system("./a.out");
		}
		/* Command : where - Print the current location. */
		else if ((strcmp(first_command, "where") == 0))
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s\n\n", cwd);
		}
		else if ((strcmp(first_command, "exit") == 0) || (strcmp(first_command, "quit") == 0))
		{
			clean();
			break;
		}
		else if (strcmp(first_command, "set")==0)
		{
			if(i == 2)
			{
				int ret;
				char* setHelper;
				char variable_name[1024];
				char variable_value[1024];
				char setter[1024];
				int j=0;				
				setHelper = strtok (second_command, "=");

				while (setHelper != NULL)
		  		{
    				if(j==0)
    				{
	    				strcpy(variable_name, setHelper);
    				}
    				if( j==1)
    				{
		    			strcpy(variable_value, setHelper);
    				}
    				if(j > 1 )
    				{
    					printf("Error in the input. \n\n");
		    		}
    		
			    	setHelper = strtok (NULL, "=");
  					j++;	
  				}
  				
				ret = setenv(variable_name, variable_value, 1);
				if(ret == 0)
				{
					 printf("New %s has been set to %s \n\n", variable_name, variable_value);		
				}else
				{
					 printf("Encountered error while setting %s value.\n\n", variable_name);		
				}
				
			}
			else
			{
				printf("ERROR:\tInvalid number of arguments provided.\n");
				printf("\tLegal use: set VARIABLE=VALUE  \n\n");
			}
		}
		else if (strcmp(first_command, "cd") == 0)
		{	
			// Only one word is present i.e. 'cd'
			if(i==1) 
			{
				int checker = chdir(getenv("HOME"));
				if(checker == 0 ) 
				{	
					printf("Arrived at : HOME.\n\n");
					char *cwd;
					cwd = getcwd (0, 0);

  					/*int len;
			   		len = strlen(cwd);*/
			   		
				}
				else 
				{
					printf("Problem loading the home directory path!\n\n");
				}
				
			}
			if(i>1)
			{
				
				if(strncmp(second_command, "/", 1)==0)
				{
					chdir(second_command); 
					printf("Arrived at : ");
					if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s\n\n", cwd);
				}
				else if (strcmp(second_command, "..")==0)
				{
					chdir("..");
					printf("Arrived at : ");
					if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s\n\n", cwd);
				}
				else
				{
					char* changeTo;
					if (getcwd(cwd, sizeof(cwd)) != NULL);
					changeTo = strcat(cwd, "/");
					changeTo = strcat(changeTo, second_command);
					chdir(changeTo); 
					
					printf("Arrived at : ");
					if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s\n\n", cwd);
				
				}
				
			}
			
		}
		else if ((strcmp(cmd2, "get paths") == 0))
		{
			printf("PATH : %s\n", getenv("PATH"));
			printf("HOME : %s\n", getenv("HOME"));
			printf("ROOT : %s\n\n", getenv("ROOT"));
			
		}
		else if ((strcmp(cmd2, "crap crap") == 0))
		{
			chdir("/Users/chinmay/Documents/KU/Spring 2015");
			if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s\n\n", cwd);
		}
		else if(strcmp(first_command, "ls" )== 0 || strcmp(first_command, "dir" )== 0)
		{
			DIR	*d;
			struct dirent *dir;
			d = opendir(".");
			if(d)
			{
				int count;
				while ((dir = readdir(d)) != NULL)
				{
						printf("%s\n", dir->d_name);

				}
				printf("\n");
				closedir(d);
			}
		
		}
		else
		{
			printf("ERROR:\tcommand not recognized. \n\n");
		}
		
	}

return 0;
}