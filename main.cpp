#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <vector>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
    int fds[1024];
    int fdcount = 1;
    sockaddr_in6 ip6laddr = {0};
    sockaddr_in  ip4laddr = {0};
    pollfd pfd[1024] = {0};
    int ret = 0;
    int tmp;
    int port = atoi(av[1]);

    ip4laddr.sin_family = AF_INET;
    ip4laddr.sin_port = htons(port);
    ip4laddr.sin_addr.s_addr = INADDR_ANY;
    fds[0] = socket(AF_INET, SOCK_STREAM, 0);

    ret |= fds[0];// | fds[1];
    ret |= bind(fds[0], (sockaddr*)&ip4laddr, sizeof(ip4laddr));// | bind(fds[1], (sockaddr*)&ip4laddr, sizeof(ip4laddr));
    ret |= listen(fds[0], 5);// | listen(fds[1], 5);
    if(ret < 0) {
        perror("Ur julen lmao");
        return 1;  
    }
    pfd[0].fd = fds[0];
    pfd[0].events = POLLIN;
    // pfd[1].events = POLLIN;
    // pfd[1].fd = fds[1];
    while ("FUCK MEXICO") { 
        tmp = fdcount;

        pfd[0].revents = 0;
        for (int i = 1; i < tmp; i++) {
            pfd[i].fd = fds[i];
            pfd[i].events = POLLIN;
            pfd[0].revents = 0;
        }

        poll(pfd, tmp, 10000);

        for (int i = 0; i < tmp; i++) {
            if(pfd[i].revents & POLLIN) {
                if (pfd[i].fd == fds[0]) {
                    socklen_t a = 0;
                    printf("Nouvelle connexion recu\n");
                    fds[fdcount] = accept(fds[0], (sockaddr*)0x01, &a);
                    fdcount++;
                }
                else {
                    int ret;
                    char buff[256] = {0};
                    ret = read(pfd[i].fd, buff, 256);
                    if(ret <= 0) {
                        close(pfd[i].fd);
                        for (int y = 0; y < fdcount; y++)
                        {
                            if (fds[y] == pfd[i].fd) {
                                memmove(fds + y, fds + y + 1, fdcount - y - 1);
                                fdcount--;
                                break;
                            }

                        }

                    }
                    else {
                        write(1, buff, ret);
                    }
                }
            }
        }
    }
    

}