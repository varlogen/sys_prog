#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
    signal(SIGPIPE, SIG_IGN);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0)
    {
        perror("socket() error");
        return -1;
    }
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = htons(INADDR_ANY);

    int one = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if (bind(sock_fd, (struct sockaddr *)&sa, sizeof(sa)) < 0)
    {
        perror("bind() error");
        return -1;
    }

    if (listen(sock_fd, SOMAXCONN) < 0)
    {
        perror("listen() error");
        return -1;
    }

    cout << "Socked num: " << sock_fd << endl;
    char buf[100];

    while (true)
    {
        cout << "Will accept" << endl;
        int conn = accept(sock_fd, 0, 0);
        if (conn < 0)
        {
            perror("accept() error");
        }

        int new_p = fork();

        if (new_p == -1)
        {
            printf("fork error");
            continue;
        }
        else if (new_p == 0)
        {
            int fail = false;
            while (!fail)
            {
                int n = recv(conn, &buf, sizeof(buf) - 1, 0);
                if (n < 0)
                {
                    perror("recv() error");
                    break;
                }
                if (n == 0)
                {
                    break;
                }
                buf[n] = '\0';
                printf("[+] data: %s\n", buf);
                int total = n;
                int written = 0;
                while (written < total + 1)
                {
                    int n = send(conn, buf + written, total + 1 - written, 0);
                    if (n < 0)
                    {
                        perror("send() error");
                        fail = true;
                        break;
                    }
                    if (n == 0)
                    {
                        printf("Eof received");
                    }
                    written += n;
                }
            }
            printf("[+] connection closed\n");
        }
    }

    return 0;
}