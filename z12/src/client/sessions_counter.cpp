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
#include <time.h>
#include <stdio.h>
#include <chrono>


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
    int n = 1000;
    int sockfd[n];
    struct sockaddr_in srv_addr;
  
    auto begin = std::chrono::steady_clock::now();
    for (int i = 0; i < n; i++)
    {
        sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);

        set_sockaddr(&srv_addr);

        if (connect(sockfd[i], (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0)
        {
            perror("connect()");
            return (1);
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    printf("%f connects per seconds\n", n / (double)elapsed_ms.count());

    for (int i = 0; i < n; i++)
        close(sockfd[i]);
}