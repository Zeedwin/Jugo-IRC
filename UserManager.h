#ifndef USER_MANAGER_H_
#define USER_MANAGER_H_

#include <string>
#include <vector>

#include "User.h"

#include "defines.h"

class UserManager
{
    private:
        std::vector<User*>   users;
    
    public:
        UserManager(void);

        /* find_if ? */
        User    *get_user(std::string const &name);
        User    *get_user(int fd);
        /* d'autres surcharges de `get_user` */

        std::vector<User*>::iterator begin(void); /* this->users.begin() */
        std::vector<User*>::iterator end(void);   /* this->users.end() */

        /*  !!ATTENTION!! ne pas utiliser ces methodes
            !!ATTENTION!! si ont est entrain d'itérer sur les utilisateurs */
        void    create_user(int fd); /* créer une utilisateur dans `users` */
		std::vector<User*>::iterator erase(std::vector<User*>::iterator it); /* enlève un utilisateur de `users` */

        void    check_pings(void);

        ~UserManager(void);
};

#endif
