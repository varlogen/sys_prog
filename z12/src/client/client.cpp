#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>

#define MAX_LINE 256
#define DEFAULT_PORT 8080

static void set_sockaddr(struct sockaddr_in *addr)
{
    bzero((char *)addr, sizeof(struct sockaddr_in));
    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(DEFAULT_PORT);
}

int main()
{
    int n;
    int c;
    int sockfd;
    char buf[MAX_LINE];
    struct sockaddr_in srv_addr;
    const char *message = "hello";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    set_sockaddr(&srv_addr);

    if (connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0)
    {
        perror("connect()");
        return(1);
    }

    for (;;)
    {
        /*
        printf("input: ");
        fgets(buf, sizeof(buf), stdin);
        c = strlen(buf) - 1;
        buf[c] = '\0';
        write(sockfd, buf, c + 1);
        */
        write(sockfd, message, strlen(message));

        bzero(buf, sizeof(buf));
        while (errno != EAGAIN && (n = read(sockfd, buf, sizeof(buf))) > 0)
        {
            printf("echo: %s\n", buf);
            bzero(buf, sizeof(buf));

            c -= n;
            if (c <= 0)
            {
                break;
            }
        }
    }
    close(sockfd);
}