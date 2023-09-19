// searchEngine.h
#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // Add this line for std::transform
#include <fstream>



class SearchEngine {
public:
    // Define the Motorbike class or struct here
    struct Motorbike {
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

    static void searchMotorbikesByCity() {
        // Search for motorbikes in the specified city
        std::cout << "\nEnter the city to search for motorbikes: ";
        std::string searchCity;
        std::cin.ignore();
        std::getline(std::cin, searchCity);

        std::ifstream inputFile("ProductDetail.txt");

        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open the input file." << std::endl;
            return;
        }

        std::vector<Motorbike> motorbikes;
        Motorbike currentMotorbike;

        // Read motorbike data and populate the vector
        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.find("MotorbikeID: ") != std::string::npos) {
                // If a new motorbike entry is found, push the current one to the vector
                if (currentMotorbike.MotorbikeID != 0) {
                    motorbikes.push_back(currentMotorbike);
                }
                // Reset the currentMotorbike
                currentMotorbike = Motorbike();
                sscanf(line.c_str(), "MotorbikeID: %d", &currentMotorbike.MotorbikeID);
            } else if (line.find("Model: ") != std::string::npos) {
                currentMotorbike.Model = line.substr(7);
            } else if (line.find("Color: ") != std::string::npos) {
                currentMotorbike.Color = line.substr(7);
            } else if (line.find("Engine Size: ") != std::string::npos) {
                sscanf(line.c_str(), "Engine Size: %d", &currentMotorbike.EngineSize);
            } else if (line.find("Transmission Mode: ") != std::string::npos) {
                currentMotorbike.TransmissionMode = line.substr(19);
            } else if (line.find("Year Made: ") != std::string::npos) {
                sscanf(line.c_str(), "Year Made: %d", &currentMotorbike.YearMade);
            } else if (line.find("Description: ") != std::string::npos) {
                currentMotorbike.Description = line.substr(13);
            } else if (line.find("Owner username: ") != std::string::npos) {
                currentMotorbike.OwnerUsername = line.substr(16);
            } else if (line.find("Expected Rented Rate: ") != std::string::npos) {
                sscanf(line.c_str(), "Expected Rented Rate: %lf%%", &currentMotorbike.ExpectedRentedRate);
            } else if (line.find("Rate ID: ") != std::string::npos) {
                sscanf(line.c_str(), "Rate ID: %d", &currentMotorbike.RateID);
            } else if (line.find("Product status: ") != std::string::npos) {
                currentMotorbike.ProductStatus = line.substr(16);
            } else if (line.find("Score: ") != std::string::npos) {
                sscanf(line.c_str(), "Score: %d", &currentMotorbike.Score);
            } else if (line.find("Latest comment: ") != std::string::npos) {
                currentMotorbike.Comment = line.substr(16);
            } else if (line.find("Credit: ") != std::string::npos) {
                sscanf(line.c_str(), "Credit: %d", &currentMotorbike.Credit);
            } else if (line.find("City: ") != std::string::npos) {
                currentMotorbike.City = line.substr(6);
            }
        }

        // Push the last motorbike entry to the vector
        if (currentMotorbike.MotorbikeID != 0) {
            motorbikes.push_back(currentMotorbike);
        }

        // Close the file
        inputFile.close();

        // Display available motorbikes in the desired city
        std::cout << "The motorbikes available in " << searchCity << " city:\n" << std::endl;

        bool found = false;

        for (const Motorbike& bike : motorbikes) {
            if (bike.City == searchCity && bike.ProductStatus == "available") {
                // Display the motorbike information
                std::cout << "MotorbikeID: " << bike.MotorbikeID << std::endl;
                std::cout << "Model: " << bike.Model << std::endl;
                std::cout << "Color: " << bike.Color << std::endl;
                std::cout << "Engine Size: " << bike.EngineSize << std::endl;
                std::cout << "Transmission Mode: " << bike.TransmissionMode << std::endl;
                std::cout << "Year Made: " << bike.YearMade << std::endl;
                std::cout << "Description: " << bike.Description << std::endl;
                std::cout << "Owner username: " << bike.OwnerUsername << std::endl;
                std::cout << "Expected Rented Rate: " << bike.ExpectedRentedRate << "%" << std::endl;
                std::cout << "Rate ID: " << bike.RateID << std::endl;
                std::cout << "Product status: " << bike.ProductStatus << std::endl;
                std::cout << "Score: " << bike.Score << std::endl;
                std::cout << "Latest comment: " << bike.Comment << std::endl;
                std::cout << "Credit: " << bike.Credit << std::endl;
                std::cout << "City: " << bike.City << std::endl;
                std::cout << std::endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "No available motorbikes found in " << searchCity << " city." << std::endl;
        }
    }

    static void toLowerCase(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    static void searchUserInformation(const std::string& username) {
        std::ifstream userProfileFile("userProfile.txt");
        std::string line;
        bool foundUser = false;

        // Convert the input username to lowercase for case-insensitive comparison
        std::string lowercaseUsername = username;
        toLowerCase(lowercaseUsername);

        while (std::getline(userProfileFile, line)) {
            // Convert the username from the file to lowercase for comparison
            std::string lowercaseLine = line;
            toLowerCase(lowercaseLine);

            if (lowercaseLine.find("username: " + lowercaseUsername) != std::string::npos) {
                foundUser = true;
                std::cout << "User information for username: " << username <<"\n"<< std::endl;

                // Display user information
                for (size_t i = 0; i < 8; i++) {
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
