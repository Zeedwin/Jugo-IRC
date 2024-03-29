#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <poll.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include "User.h"
#include "UserManager.h"
#include "ServerCore.h"
#include "UserManager.h"

int main(int ac, char **av)
{
    ServerCore sv(av[2]);

    // todo verifier argc et aguments
    (void)ac;
    sv.loop(atoi(av[1]));
}