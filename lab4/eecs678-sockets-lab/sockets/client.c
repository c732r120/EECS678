#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BSIZE 256
#define NSTRS 3
#define SOCKET_ADDRESS	"mysock"
#define UNIX_PATH_MAX    108

/*
 * This is the set of strings we will send through the socket for
 * conversion
 */
char *strs[NSTRS] = 
{
  "this is the first string from the client\n",
  "this is the second string from the client\n",
  "this is the third string from the client\n"
};

	
int main(int argc, char *argv[])
{
	int sockfd, ret, i;
	char buf[BSIZE];
	struct sockaddr_un saun;
	
#if 0
	/* Socket Address Structure */
	struct sockaddr_un
	{
		sa_family_t sun_family;
		char sun_path[UNIX_PATH_MAX];
	}
		
	saun.sun_family= AF_UNIX;
	strncpy(saun.sun_path, SOCEKET_ADDRESS, sizeof(saun.sun_path)-1);



	/* Add Code: Create the client session socket */
	sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{
    	fprintf(stderr, "\nError Opening Socket, ERROR#%d\n", errno);
    	return EXIT_FAILURE;
	}


	/* Add Code: Connect the session socket to the server */
	
	ret= connect(sockfd, (struct sockaddr *)&saun, sizeof(saun));
	if (ret < 0) 
	{
		fprintf(stderr, "\nError Connecting Sockets, ERROR#%d\n", errno);
		return EXIT_FAILURE;
	}

  /* Add Code: Send the strs array, one string at a time, to the
   * server. Read the converted string and print it out before sending
   * the next string
   */
   

    FILE *fp;
	fp = fdopen(sockfd, "r");
   
   
	for (i = 0; i < NSTRS; i++)
	{
	  	send(sockfd, strs[i], strlen(strs[i]), 0);
    	printf("SENDING:\n%s", strs[i]);
    	 while ((buf = fgetc(fp)) != EOF)
        {
            putchar(buf);
            if (buf == '\n')
                break;
        }
		printf("RECEIVED:\n%s\n", buf);
	}

  close(sockfd);
#endif
}
