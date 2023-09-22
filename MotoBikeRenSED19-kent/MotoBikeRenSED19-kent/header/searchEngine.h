// searchEngine.h
#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // Add this line for std::transform
#include <fstream>

class SearchEngine
{
public:
    // Define the Motorbike class or struct here
    struct Motorbike
    {
        int MotorbikeID;
        std::string Model;
        std::string Color;
        int EngineSize;
        std::string TransmissionMode;
        int YearMade;
        std::string Description;
        std::string OwnerUsername;
        double ExpectedRentedRate;
        int RateID;
        std::string ProductStatus;
        int Score;
        int Credit;
        std::string Comment;
        std::string City;
    };

    static void searchMotorbikesByCity();

    static void toLowerCase(std::string &str);

    static void searchUserInformation(const std::string &username);
};

#endif // SEARCH_ENGINE_H
