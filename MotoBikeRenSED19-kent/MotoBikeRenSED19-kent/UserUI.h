#ifndef USERUI_H
#define USERUI_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "searchEngine.h"
#include <limits>

class UserUI {
public:
    static void showMenu(const std::string& username) {
        int choice;

        while (true) {
            std::cout << "\nMember Menu for " << username << ":" << std::endl;
            std::cout << "1. Edit User Profile" << std::endl;
            std::cout << "2. Search Motorbikes by City" << std::endl;
            std::cout << "3. Rent a Motorbike" << std::endl;
            std::cout << "4. Exit" << std::endl;
            std::cout << "Enter your choice (1-4): ";

            if (!(std::cin >> choice) || choice < 1 || choice > 4) {
                // Input is not a valid integer in the range (1-5)
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Invalid input. Please enter a valid integer choice (1-4).\n" << std::endl;
                continue; // Skip the rest of the loop iteration and ask for input again
            }

            switch (choice) {
                case 1:
                    editUserProfile(username);
                    break;
                case 2:
                    SearchEngine::searchMotorbikesByCity();
                    break;
                case 3:
                    rentMotorbike();
                    break;
                case 4:
                    std::cout << "Exiting the User Menu. Goodbye!\n" << std::endl;
                    return;
                default:
                    break;
            }
        }
    }

    static void editUserProfile(const std::string& username) {
        std::string fileName = "userProfile.txt"; // Use just the file name

        std::ifstream inputFile(fileName);
        if (!inputFile) {
            std::cout << "File not found." << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }

        inputFile.close();

        bool found = false;

        for (size_t i = 0; i < lines.size(); i++) {
            if (lines[i].find("Username: " + username) != std::string::npos) {
                // User profile found, display and edit details
                std::cout << "Found user profile for: " << username << std::endl;
                std::cout << "Current details:" << std::endl;

                // Print current details
                for (size_t j = i; j < i + 8; j++) {
                    std::cout << lines[j] << std::endl;
                }

                // Prompt for new details
                std::cout << "\nEnter new details:" << std::endl;

                std::cout << "Full Name: ";
                std::string newFullName;
                std::cin.ignore(); // Clear the newline left in the buffer
                std::getline(std::cin, newFullName);
                lines[i + 1] = "Full Name: " + newFullName;

                std::cout << "Phone: ";
                std::string newPhone;
                std::getline(std::cin, newPhone);
                lines[i + 2] = "Phone: " + newPhone;

                std::cout << "ID Type: ";
                std::string newIdType;
                std::cin.ignore();
                std::getline(std::cin, newIdType);
                lines[i + 3] = "ID Type: " + newIdType;

                std::cout << "ID Number: ";
                std::string newIdNumber;
                std::getline(std::cin, newIdNumber);
                lines[i + 4] = "ID Number: " + newIdNumber;

                std::cout << "Driver's License Number: ";
                std::string newDriverLicenseNum;
                std::getline(std::cin, newDriverLicenseNum);
                lines[i + 5] = "Driver's License Number: " + newDriverLicenseNum;

                std::cout << "Expired Date (MM/YY): ";
                std::string newExpiredDate;
                std::getline(std::cin, newExpiredDate);
                lines[i + 6] = "Expired Date: " + newExpiredDate;

                std::cout << "City: ";
                std::string newCity;
                std::getline(std::cin, newCity);
                lines[i + 7] = "City: " + newCity;

                std::ofstream outputFile(fileName);
                if (outputFile) {
                    for (const std::string& modifiedLine : lines) {
                        outputFile << modifiedLine << std::endl;
                    }

                    outputFile.close();
                    std::cout << "User profile updated successfully." << std::endl;
                } else {
                    std::cout << "Error writing to the file." << std::endl;
                }

                found = true;
                break;
            }
            else{
                std::cout << "\nPlease fill your profile first" << std::endl;
                break;
            }
        }

        if (!found) {
            std::cout << "User profile not found." << std::endl;
        }
    }

    static void rentMotorbike() {
    // Define a struct to represent a motorbike
    struct Motorbike {
        int MotorbikeID;
        std::string Model;
        std::string Color;
        int EngineSize;
        std::string TransmissionMode;
        int YearMade;
        std::string Description;
        int OwnerID;
        float ExpectedRentedRate;
        int RateID;
        std::string ProductStatus;
        int Score;
        std::string Comment;
        std::string City;
    };

    // Open the file by name (without specifying a directory)
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
        } else if (line.find("Owner ID: ") != std::string::npos) {
            sscanf(line.c_str(), "Owner ID: %d", &currentMotorbike.OwnerID);
        } else if (line.find("Expected Rented Rate: ") != std::string::npos) {
            sscanf(line.c_str(), "Expected Rented Rate: %f%%", &currentMotorbike.ExpectedRentedRate);
        } else if (line.find("Rate ID: ") != std::string::npos) {
            sscanf(line.c_str(), "Rate ID: %d", &currentMotorbike.RateID);
        } else if (line.find("Product status: ") != std::string::npos) {
            currentMotorbike.ProductStatus = line.substr(16);
        } else if (line.find("Score: ") != std::string::npos) {
            sscanf(line.c_str(), "Score: %d", &currentMotorbike.Score);
        } else if (line.find("Comment: ") != std::string::npos) {
            currentMotorbike.Comment = line.substr(9);
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

    // Prompt the user for the desired city
    std::string desiredCity;
    std::cout << "Enter the city where you want to rent a motorbike: ";
    std::cin.ignore();
    std::getline(std::cin, desiredCity);

    // Display available motorbikes in the desired city
    std::cout << "The motorbikes available for " << desiredCity << " city:" << std::endl;

    bool found = false;

    for (const Motorbike& bike : motorbikes) {
        if (bike.City == desiredCity && bike.ProductStatus == "available") {
            // Display the motorbike information
            std::cout << "MotorbikeID: " << bike.MotorbikeID << std::endl;
            std::cout << "Model: " << bike.Model << std::endl;
            std::cout << "Color: " << bike.Color << std::endl;
            std::cout << "Engine Size: " << bike.EngineSize << std::endl;
            std::cout << "Transmission Mode: " << bike.TransmissionMode << std::endl;
            std::cout << "Year Made: " << bike.YearMade << std::endl;
            std::cout << "Description: " << bike.Description << std::endl;
            std::cout << "Owner ID: " << bike.OwnerID << std::endl;
            std::cout << "Expected Rented Rate: " << bike.ExpectedRentedRate << "%" << std::endl;
            std::cout << "Rate ID: " << bike.RateID << std::endl;
            std::cout << "Product status: " << bike.ProductStatus << std::endl;
            std::cout << "Score: " << bike.Score << std::endl;
            std::cout << "Comment: " << bike.Comment << std::endl;
            std::cout << "City: " << bike.City << std::endl;
            std::cout << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "No available motorbikes found in " << desiredCity << " city." << std::endl;
    }
}
};

#endif // USERUI_H
