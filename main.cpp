#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

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
    if (ac == 3)
    {
        ServerCore sv(av[2]);
        if(atoi(av[1]) >= 0 && atoi(av[1]) <= 65535)
            sv.loop(atoi(av[1]));
        else
        {
            std::cout << "Error: Not an available port" << std::endl;
            return 1;   
        }
    }
    else
        std::cout << "Error: <Port> <Password> " << std::endl;
    return(1);
}