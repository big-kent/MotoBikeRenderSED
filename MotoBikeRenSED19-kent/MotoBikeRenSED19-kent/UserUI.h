#ifndef USERUI_H
#define USERUI_H
#include "rental_system.h"

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
            std::cout << "1. Edit My Profile" << std::endl;
            std::cout << "2. Search Motorbikes by City" << std::endl;
            std::cout << "3. Apply a new motorbike for rental service" << std::endl;
            std::cout << "4. Rent a Motorbike" << std::endl;
            std::cout << "5. View Rental Requests" << std::endl;
            std::cout << "6. View Rental responses" << std::endl;
            std::cout << "7. Return the motorbike to the rental service" << std::endl;
            std::cout << "8. Check return motorbike message from renter" << std::endl;
            std::cout << "9. Add more credit point to your account" << std::endl;
            std::cout << "10. Exit" << std::endl;
            std::cout << "Enter your choice (1-10): ";

            if (!(std::cin >> choice) || choice < 1 || choice > 10) {
                // Input is not a valid integer in the range (1-10)
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Invalid input. Please enter a valid integer choice (1-10).\n" << std::endl;
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
                    applyMotorbikeForRent(username);
                    break;
                case 4:
                    rentMotorbike(username);
                    break;
                case 5:
                    viewRentalRequests(username);
                    break;
                case 6:
                    viewRenterResponses(username);
                    break;
                case 7:
                    returnMotorbike(username);
                    break;
                case 8:
                    checkReturnMessages(username);
                    break;                 
                case 9:
                    addMoreCreditPointsToYourAccount(username);
                    break;        
                case 10:
                    std::cout << "\nExiting " << username << "'s Menu. Goodbye!!!\n" << std::endl;
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
                break; // Exit the loop after editing
            }
        }

        if (!found) {
            std::cout << "User profile not found." << std::endl;
        } else {
            std::cout << "\nPlease fill your profile first" << std::endl;
        }
    }

};

#endif // USERUI_H
