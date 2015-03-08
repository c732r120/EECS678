#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h> 
#include <pwd.h>

int main()
{
	int i = 0;
	while(i<8)
	{
		printf("%d ", i);
		sleep(1);
		i++;
	}

return 0;
}