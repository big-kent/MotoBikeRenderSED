// AdminUI.h
#ifndef ADMINUI_H
#define ADMINUI_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "searchEngine.h"
#include <limits>

class AdminUI
{
public:
    static void showMenu();

private:
    static void viewAllUserAccounts();

    static void viewProductDetails();

    static void EditProductDetails();

    static void AddNewMotorbike();

    // Add this function inside the AdminUI class in AdminUI.h

    static bool motorbikeIdExists(const std::string &motorbikeId);

    static void DeleteMotorbikeById();
};

#endif // ADMINUI_H
