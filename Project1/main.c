#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#include <pwd.h>



int main (int argc, char **argv, char **envp) 
{

	char cmd[256];
	char* home_dir;
	char* pch;
	
	while (true)
	{
		printf("> ");
		fgets(cmd, sizeof cmd, stdin);
		cmd[strlen(cmd)-1] = '\0';
		
		
		pch = strtok(cmd, " ");
		printf("begins");

		while (pch != NULL)
  		{
    		printf ("%s\n",pch);
    		pch = strtok (NULL, " ");
  		}
				printf("ends");
		
		
		printf("%s", cmd);
		if ((strcmp(cmd, "exit") == 0) || (strcmp(cmd, "quit") == 0))
		{
			break;
		}
		if (strcmp(cmd, "cd") == 0)
		{
			int checker = chdir(getenv("HOME"));
			if(checker == 0 ) 
			{	
				printf("works!");
				char *cwd;
				cwd = getcwd (0, 0);
				printf("%s", cwd);
				
				
				
  				int len;
			   len = strlen(cwd);
			   printf("%d", len);
			}
			else 
			{
				printf("problem!");
			}
		
		}
		
		if ((strcmp(cmd, "home asd\n") == 0))
		{
			printf("recognized\n");
		  /*chdir(getenv("HOME"));
		   printf("\n Now changed \n");
		   		   if (getcwd(cwd, sizeof(cwd)) != NULL) printf("%s", cwd); */
		   		    printf("PATH : %s\n", getenv("PATH"));
					printf("HOME : %s\n", getenv("HOME"));
					printf("ROOT : %s\n", getenv("ROOT"));
			
		}
		
		
		
	}

	return 0;
}


/*if((home_dir = getenv("HOME")) == NULL)
			{
				printf("I'm here!");
				home_dir = getpwuid(getuid())->pw_dir;
			}
			*/
			//printf(" OKAY!! %s Done!", &home_dir);
