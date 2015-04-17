#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

#define BSIZE          256
#define NSTRS          3
#define SOCKET_ADDRESS "mysock"

char *strs[NSTRS] = 
{
        "this is the first string from the client\n",
        "this is the second string from the client\n",
        "this is the third string from the client\n"
};

int main(int argc, char *argv[])
{

    int      sockfd, ret, i;
    struct   sockaddr_un saun;
    char     buf[BSIZE];
        
    saun.sun_family = AF_UNIX;
    strcpy(saun.sun_path, SOCKET_ADDRESS);
    
    sockfd = socket(PF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0) 
    {
        fprintf(stderr, "\nError Opening Socket, ERROR#%d\n", errno);
        return EXIT_FAILURE;
    }

    ret = connect(sockfd, (struct sockaddr *) &saun, sizeof(saun));
    if (ret < 0) 
    {
        fprintf(stderr, "\nError Connecting Sockets, ERROR#%d\n", errno);
        return EXIT_FAILURE;
    }

    for (i = 0; i < NSTRS; i++) 
    {
        printf("SENDING:\n%s", strs[i]);
        write(sockfd, strs[i], BSIZE);
        read(sockfd, buf, BSIZE);
        printf("RECEIVED:\n%s\n", buf);
    }

    close(sockfd);
}
