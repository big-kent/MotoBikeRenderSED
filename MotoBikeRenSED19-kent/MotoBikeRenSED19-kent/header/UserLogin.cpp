// UserLogin.cpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "UserLogin.h"

bool UserLogin::isUserLoginValid(const std::string &username, const std::string &password)
{
    std::ifstream userFile("userAccount.txt");
    std::string line;

    if (userFile.is_open())
    {
        while (std::getline(userFile, line))
        {
            std::istringstream iss(line);
            UserInfo userInfo;

            if (iss >> userInfo.username >> userInfo.password >> userInfo.credit >> userInfo.score >> userInfo.rating_time)
            {
                if (username == userInfo.username && password == userInfo.password)
                {
                    userFile.close();
                    return true; // User login is valid
                }
            }
        }
        userFile.close();
    }

    return false; // User login is not valid
}

bool UserLogin::isAdminLoginValid(const std::string &username, const std::string &password)
{
    std::ifstream adminFile("adminAccount.txt");
    std::string adminUsername;
    std::string adminPassword;

    if (adminFile.is_open())
    {
        while (adminFile >> adminUsername >> adminPassword)
        {
            if (username == adminUsername && password == adminPassword)
            {
                adminFile.close();
                return true; // Admin login is valid
            }
        }
        adminFile.close();
    }

    return false; // Admin login is not valid
};