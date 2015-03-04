#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#define BSIZE          256
#define SOCKET_ADDRESS "mysock"

void convert_string (char *cp)
{
    char *currp;	
    int   c;
    for (currp = cp; *currp != '\0'; currp++)
    {
        c = toupper (*currp);
        *currp = (char) c;
    }
}

int main(int argc, char *argv[])
{

    int    handshake_sockfd, session_sockfd, ret;
    struct sockaddr_un saun;
    char   buf[BSIZE];

    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, SOCKET_ADDRESS);

    handshake_sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (handshake_sockfd < 0) 
    {
        fprintf(stderr, "\nError Opening Socket, ERROR#%d\n", errno);
        return EXIT_FAILURE;
    }

    unlink(SOCKET_ADDRESS);

    ret = bind(handshake_sockfd, (struct sockaddr *) &saun, sizeof(saun));
    if (ret < 0) 
    {
        fprintf(stderr, "\nError Binding Socket, ERROR#%d\n", errno);
        return EXIT_FAILURE;
    }
    
    ret = listen(handshake_sockfd, 5);
    if (ret < 0) 
    {
        fprintf(stderr, "\nError Listening on Socket, ERROR#%d\n", errno);
        return EXIT_FAILURE;
    }
    
    session_sockfd = accept(handshake_sockfd, NULL, NULL);
    if (session_sockfd < 0) 
    {
        fprintf(stderr, "\nError Accepting Socket, ERROR#%d\n", errno);
        return EXIT_FAILURE;
    }
    
    while (read(session_sockfd, buf, BSIZE) > 0) 
    {
        printf("RECEIVED:\n%s", buf);
        convert_string(buf);
        write(session_sockfd, buf, BSIZE);
        printf("SENDING:\n%s\n", buf);
    }

    close(session_sockfd);
    close(handshake_sockfd);
}
