#ifndef DEFINES_H_
#define DEFINES_H_

typedef int                 socket_t;
typedef struct pollfd       pollfd_t;
typedef struct sockaddr_in  sockaddr_in_t;

#define NEED_PASS       0x1
#define NEED_NOT_CONN   0x2
#define NEED_CONN       0x4

#define BAD_PASS 0x1
#define PREFIX_SRV ":irc.42.fr"

#define UMODE_i 0x1 // i - marque un utilisateur comme invisible ;
#define UMODE_s 0x2 // s - marque un utilisateur comme recevant les notifications du serveur ;
#define UMODE_w 0x4 // w - l'utilisateur reçoit les WALLOPs ;
#define UMODE_o 0x8 // o - drapeau d'opérateur. 

#define TIMEOUT 20

#endif
