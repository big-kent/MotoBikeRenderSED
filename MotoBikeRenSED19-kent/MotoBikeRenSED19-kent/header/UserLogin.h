// UserLogin.h

#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class UserLogin
{
public:
    struct UserInfo
    {
        std::string username;
        std::string password;
        int credit;
        int score;
        int rating_time;
    };

    static bool isUserLoginValid(const std::string &username, const std::string &password);

    static bool isAdminLoginValid(const std::string &username, const std::string &password);
};

#endif // USERLOGIN_H
