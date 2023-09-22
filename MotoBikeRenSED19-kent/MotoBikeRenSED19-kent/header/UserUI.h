#ifndef USERUI_H
#define USERUI_H
#include "rental_system.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "searchEngine.h"
#include <limits>

class UserUI
{
public:
    static void showMenu(const std::string &username);

    static void editUserProfile(const std::string &username);

    static void displayMotorbikeScoreAndComment();
};

#endif // USERUI_H
