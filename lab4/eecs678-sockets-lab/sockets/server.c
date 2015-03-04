#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#define QSIZE 5
#define BSIZE 256
#define SOCKET_ADDRESS	"mysock"
#define UNIX_PATH_MAX    108


void convert_string (char *cp)
{
  char *currp;	/* pointer to current position in the input string */
  int c;        /* return value of toupper is the converted letter */

  for (currp = cp; *currp != '\0'; currp++) 
  {
    c = toupper (*currp);
    *currp = (char) c;
  }
}

int main(int argc, char *argv[])
{

	int handshake_sockfd, session_sockfd, ret;
	struct sockaddr_un saun;
	char buf[BSIZE];

#if 0
	/* Socket Address Structure */
	struct sockaddr_un
	{
	  sa_family_t sun_family;
	  char sun_path[UNIX_PATH_MAX];
	}
   
   	saun.sun_family= AF_UNIX;
	strncpy(saun.sun_path, SOCEKET_ADDRESS, sizeof(saun.sun_path)-1);
   
   
	/* The handshake socket */
	handshake_socfd = socket(PF_UNIX, SOCK_STREAM, 0);
	if (handshake_sockfd < 0) 
	{
		fprintf(stderr, "\nError Opening Socket, ERROR#%d\n", errno);
	    return EXIT_FAILURE;
	}

	unlink(SOCKET_ADDRESS);

	/* Binding the handshake socket to the sockaddr. */ 
  	ret= bind(handshake_sockfd, (struct sockaddr *) &saun, sizeof(saun));  
	if (ret < 0) 
	{
    	fprintf(stderr, "\nError Binding Socket, ERROR#%d\n", errno);
	    return EXIT_FAILURE;
	}

	/* handshake socket = listening socket  */
	ret = listen(handshake_socfd, 5);
	if (ret < 0)
	{
		fprintf(stderr, "\nError Listening on Socket, ERROR#%d\n", errno);
		return EXIT_FAILURE;
	}

	/* Accept a connection, session socket as the return value.*/
	session_sockfd= accept(handshake_sockfd, NULL, NULL); 
	if (session_sockfd < 0) 
	{
		fprintf(stderr, "\nError Accepting Socket, ERROR#%d\n", errno);
		return EXIT_FAILURE;
	}

  /* Add Code: Read lines one at a time from the connected session
   * socket. Convert each line to uppercase using convert_string, and
   * write the line back to the client. Continue until there are no
   * more lines to read.
   */
   printf("alright!");
	FILE *fp;
	fp = fdopen(session_sockfd, "r");

	while ((buf = fgetc(fp)) != EOF) 
	{
		printf("RECEIVED:\n%s", buf);
		
		convert_string(buf);	
		
		send(sessions_sockfd, buf, strlen(buf), 0);
		printf("SENDING:\n%s\n", buf);
	}

  close(session_sockfd);
  close(handshake_sockfd);

#endif
}
