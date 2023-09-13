// UserLogin.h

#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <string>
#include <fstream>

class UserLogin {
public:
    static bool isUserLoginValid(const std::string& username, const std::string& password) {
        std::ifstream userFile("userAccount.txt");
        std::string userUsername;
        std::string userPassword;

        if (userFile.is_open()) {
            while (userFile >> userUsername >> userPassword) {
                if (username == userUsername && password == userPassword) {
                    userFile.close();
                    return true; // User login is valid
                }
            }
            userFile.close();
        }

        return false; // User login is not valid
    }
    
        static bool isAdminLoginValid(const std::string& username, const std::string& password) {
        std::ifstream adminFile("adminAccount.txt");
        std::string adminUsername;
        std::string adminPassword;

        if (adminFile.is_open()) {
            while (adminFile >> adminUsername >> adminPassword) {
                if (username == adminUsername && password == adminPassword) {
                    adminFile.close();
                    return true; // Admin login is valid
                }
            }
            adminFile.close();
        }

        return false; // Admin login is not valid
    }
};

#endif // USERLOGIN_H
