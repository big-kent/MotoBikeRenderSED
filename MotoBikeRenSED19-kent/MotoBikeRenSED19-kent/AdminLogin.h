// AdminLogin.h

#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <string>
#include <fstream>

class AdminLogin {
public:
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

#endif // ADMINLOGIN_H
