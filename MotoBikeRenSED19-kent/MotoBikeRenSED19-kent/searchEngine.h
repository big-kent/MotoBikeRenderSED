// searchEngine.h

#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include <iostream>

class SearchEngine {
public:
    static void searchMotorbikesByCity() {
        // Search for motorbikes in the specified city
        std::cout << "\nEnter the city to search for motorbikes: ";
        std::string searchCity;
        std::cin.ignore();
        std::getline(std::cin, searchCity);

        std::ifstream productDetailFile("ProductDetail.txt");
        bool foundMotorbikeInCity = false;
        std::vector<std::string> motorbikeDetails;

        std::string line;
        bool cityStatementDisplayed = false; // To track if the city statement is displayed

        while (std::getline(productDetailFile, line)) {
            if (line.find("city: " + searchCity) != std::string::npos) {
                foundMotorbikeInCity = true;
                // Display the city statement only once
                if (!cityStatementDisplayed) {
                    std::cout << "\nThe motorbikes available in " << searchCity << " city:\n" << std::endl;
                    cityStatementDisplayed = true;
                }
                // Display motorbike details and add a blank line between motorbikes
                for (const std::string& detail : motorbikeDetails) {
                    std::cout << detail << std::endl;
                }
                std::cout << std::endl; // Add a blank line
                motorbikeDetails.clear(); // Clear the details for the next motorbike
            }
            motorbikeDetails.push_back(line);
            if (motorbikeDetails.size() > 13) {
                motorbikeDetails.erase(motorbikeDetails.begin()); // Limit to 11 lines before the city line
            }
        }

        productDetailFile.close();

        if (!foundMotorbikeInCity) {
            std::cout << "No available motorbikes found in " << searchCity << " City." << std::endl;
        }
    }


    static void searchUserInformation(const std::string& username) {
        std::ifstream userProfileFile("userProfile.txt");
        std::string line;
        bool foundUser = false;

        while (std::getline(userProfileFile, line)) {
            if (line.find("Username: " + username) != std::string::npos) {
                foundUser = true;
                std::cout << "User information for username: " << username << std::endl;

                // Display user information
                for (size_t i = 0; i < 10; i++) {
                    if (!std::getline(userProfileFile, line)) {
                        break;
                    }
                    std::cout << line << std::endl;
                }

                break;
            }
        }

        userProfileFile.close();

        if (!foundUser) {
            std::cout << "User with username: " << username << " not found." << std::endl;
        }
    }
    
};

#endif // SEARCH_ENGINE_H
