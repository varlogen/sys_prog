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
#include <stdlib.h>

#define DEFAULT_PORT 8080
#define MAX_CONN 16
#define MAX_EVENTS 32
#define BUF_SIZE 16
#define MAX_LINE 256

void server_run();
int main(int argc, char *argv[])
{
	server_run();
	return 0;
}

static void epoll_ctl_add(int epfd, int fd, uint32_t events)
{
	struct epoll_event ev;
	ev.events = events;
	ev.data.fd = fd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1)
	{
		perror("epoll_ctl()\n");
		exit(1);
	}
}

static void set_sockaddr(struct sockaddr_in *addr)
{
	bzero((char *)addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(DEFAULT_PORT);
}

static int setnonblocking(int sockfd)
{
	if (fcntl(sockfd, F_SETFD, fcntl(sockfd, F_GETFD, 0) | O_NONBLOCK) ==
		-1)
	{
		return -1;
	}
	return 0;
}

void server_run()
{
	int i;
	int n;
	int epfd;
	int nfds;
	int listen_sock;
	int conn_sock;
	socklen_t socklen;
	char buf[BUF_SIZE];
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;
	struct epoll_event events[MAX_EVENTS];

	listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	set_sockaddr(&srv_addr);
	bind(listen_sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr));

	setnonblocking(listen_sock);
	listen(listen_sock, MAX_CONN);

	epfd = epoll_create(1);
	epoll_ctl_add(epfd, listen_sock, EPOLLIN | EPOLLOUT | EPOLLET);

	socklen = sizeof(cli_addr);

	for (;;)
	{
		nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
		for (i = 0; i < nfds; i++)
		{
			if (events[i].data.fd == listen_sock)
			{
				conn_sock =
					accept(listen_sock,
						   (struct sockaddr *)&cli_addr,
						   &socklen);

				inet_ntop(AF_INET, (char *)&(cli_addr.sin_addr),
						  buf, sizeof(cli_addr));
				printf("connected with %s:%d\n", buf,
					   ntohs(cli_addr.sin_port));

				setnonblocking(conn_sock);
				epoll_ctl_add(epfd, conn_sock,
							  EPOLLIN | EPOLLET | EPOLLRDHUP |
							  EPOLLHUP);
			}
			else if (events[i].events & EPOLLIN)
			{
				for (;;)
				{
					bzero(buf, sizeof(buf));
					n = recv(events[i].data.fd, buf,
							 sizeof(buf), 0);
					if (n <= 0)
					{
						break;
					}
					else
					{
						send(events[i].data.fd, buf,
							 strlen(buf), 0);
						break;
					}
				}
			}
			else
			{
				printf("[+] unexpected\n");
			}
			if (events[i].events & (EPOLLRDHUP | EPOLLHUP))
			{
				printf("[+] connection closed\n");
				epoll_ctl(epfd, EPOLL_CTL_DEL,
						  events[i].data.fd, NULL);
				close(events[i].data.fd);
				continue;
			}
		}
	}
}