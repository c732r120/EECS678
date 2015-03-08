#include <stdio.h> 
#include <stdlib.h> 
#include <curses.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <dirent.h> 
#include <pwd.h> 
#include <errno.h> 
#include <sys/wait.h> 
#include <signal.h> 
#define clean() printf("\033[H\033[J")
#define ARRSIZE 1024