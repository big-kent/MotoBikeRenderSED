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

class AdminUI {
public:
    static void showMenu() {
        int choice;

        while (true) {
            std::cout << "\nAdmin Menu:" << std::endl;
            std::cout << "1. View all user accounts" << std::endl;
            std::cout << "2. Search for user information" << std::endl;
            std::cout << "3. View motorbike Details" << std::endl;
            std::cout << "4. Search for motorbikes by city name" << std::endl;
            std::cout << "5. Edit motorbike Details" << std::endl;
            std::cout << "6. Add New Motorbike" << std::endl;
            std::cout << "7. Delete Motorbike by ID" << std::endl; // New option
            std::cout << "8. Log out" << std::endl;
            std::cout << "Enter your choice (1-8): ";

            if (!(std::cin >> choice) || choice < 1 || choice > 8) {
                // Input is not a valid integer in the range (1-8)
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Invalid input. Please enter a valid integer choice (1-8).\n" << std::endl;
                continue; // Skip the rest of the loop iteration and ask for input again
            }

            switch (choice) {
                case 1:
                    viewAllUserAccounts();
                    break;
                case 2:
                    {
                    std::string usernameToSearch;
                    std::cout << "Enter the username to search for: ";
                    std::cin >> usernameToSearch;
                    std::cout << std::endl;
                    SearchEngine::searchUserInformation(usernameToSearch);
                        }
                    break;
                case 3:
                    viewProductDetails();
                    break;
                case 4:
                    SearchEngine::searchMotorbikesByCity();
                    break;
                case 5:
                    EditProductDetails();
                    break;
                case 6:
                    AddNewMotorbike();
                    break;
                case 7:
                    DeleteMotorbikeById(); // New function to delete motorbike by ID
                    break;
                case 8:
                    std::cout << "Exiting admin account. Goodbye!" << std::endl;
                    return;
                default:
                    break;
            }
        }
    }


private:
    static void viewAllUserAccounts() {
        std::ifstream userFile("userAccount.txt");

        if (userFile.is_open()) {
            std::string username;
            std::string password;
            std::string creditPoint;

            std::cout << "\nList of User Accounts:" << std::endl;
            while (userFile >> username >> password >> creditPoint) {
                std::cout << "Username: " << username << "\tPassword: " << password << "\tCredit Point: " << creditPoint << std::endl ;
            }

            userFile.close();
        } else {
            std::cerr << "Failed to open user account file." << std::endl;
        }
    }

    static void viewProductDetails() {
        std::ifstream productFile("ProductDetail.txt");
        std::string line;

        if (productFile.is_open()) {
            std::cout << "\nProduct Detail:" << std::endl;
            while (std::getline(productFile, line)) {
                std::cout << line << std::endl;
            }

            productFile.close();
        } else {
            std::cerr << "Failed to open product details file." << std::endl;
        }
    }

    static void EditProductDetails()
    {
        std::cout << "Enter the MotorbikeID to edit details: ";
        std::string motorbikeIdToEdit;
        std::cin >> motorbikeIdToEdit;

        std::string fileName = "ProductDetail.txt"; // Use just the file name

        std::ifstream inputFile(fileName);
        if (!inputFile)
        {
            std::cout << "File not found." << std::endl;
            return;
        }

        std::vector<std::string> lines;
        std::string line;

        while (std::getline(inputFile, line))
        {
            lines.push_back(line);
        }

        inputFile.close();

        bool found = false;

        for (size_t i = 0; i < lines.size(); i++)
        {
            if (lines[i].find("MotorbikeID: " + motorbikeIdToEdit) != std::string::npos)
            {
                // You can edit the details here
                std::cout << "Found MotorbikeID: " << motorbikeIdToEdit << std::endl;
                std::cout << "Current details:" << std::endl;

                // Print current details
                for (size_t j = i; j < i + 13; j++)
                {
                    std::cout << lines[j] << std::endl;
                }

                // Prompt for new details
                std::cout << "\nEnter new details:" << std::endl;

                std::cout << "Model: ";
                std::string newModel;
                std::cin.ignore(); // Clear the newline left in the buffer
                std::getline(std::cin, newModel);
                lines[i + 1] = "Model: " + newModel;

                std::cout << "Color: ";
                std::string newColor;
                std::getline(std::cin, newColor);
                lines[i + 2] = "Color: " + newColor;

                std::cout << "Engine Size: ";
                std::string newEngineSize;
                std::getline(std::cin, newEngineSize);
                lines[i + 3] = "Engine Size: " + newEngineSize;

                std::cout << "Transmission Mode: ";
                std::string newTransmissionMode;
                std::getline(std::cin, newTransmissionMode);
                lines[i + 4] = "Transmission Mode: " + newTransmissionMode;

                std::cout << "Year Made: ";
                std::string newYearMade;
                std::getline(std::cin, newYearMade);
                lines[i + 5] = "Year Made: " + newYearMade;

                std::cout << "Description: ";
                std::string newDescription;
                std::getline(std::cin, newDescription);
                lines[i + 6] = "Description: " + newDescription;

                std::cout << "Owner username: ";
                std::string newOwnerId;
                std::getline(std::cin, newOwnerId);
                lines[i + 7] = "Owner username: " + newOwnerId;

                std::cout << "Expected Rented Rate: ";
                std::string newRentedRate;
                std::getline(std::cin, newRentedRate);
                lines[i + 8] = "Expected Rented Rate: " + newRentedRate;

                std::cout << "Rate ID: ";
                std::string newRateId;
                std::getline(std::cin, newRateId);
                lines[i + 9] = "Rate ID: " + newRateId;

                std::cout << "Product status: ";
                std::string newProductStatus;
                std::getline(std::cin, newProductStatus);
                lines[i + 10] = "Product status: " + newProductStatus;

                std::cout << "Score: ";
                std::string newScore;
                std::getline(std::cin, newScore);
                lines[i + 11] = "Score " + newScore;

                std::cout << "Comment: ";
                std::string newComment;
                std::getline(std::cin, newComment);
                lines[i + 12] = "Comment: " + newComment;
                
                std::cout << "city: ";
                std::string newCity;
                std::getline(std::cin, newCity);
                lines[i + 13] = "City " + newCity;

                std::ofstream outputFile(fileName);
                if (outputFile)
                {
                    for (const std::string &modifiedLine : lines)
                    {
                        outputFile << modifiedLine << std::endl;
                    }

                    outputFile.close();
                    std::cout << "Details updated successfully." << std::endl;
                }
                else
                {
                    std::cout << "Error writing to the file." << std::endl;
                }

                found = true;
                break;
            }
        }

        if (!found)
        {
            std::cout << "MotorbikeID not found." << std::endl;
        }
    }

        static void AddNewMotorbike() {
        std::ofstream productFile("ProductDetail.txt", std::ios::app); // Append mode

        if (productFile.is_open()) {
            std::cout << "\nAdd New Motorbike:" << std::endl;

            std::string motorbikeId;
            std::cout << "MotorbikeID: ";
            std::cin >> motorbikeId;

            // Check if the motorbike ID already exists (you may need to modify this check)
            if (motorbikeIdExists(motorbikeId)) {
                std::cout << "MotorbikeID already exists. Please choose a unique ID." << std::endl;
                return;
            }

            // Input the rest of the motorbike details
            std::string model, color, engineSize, transmissionMode, yearMade, description, ownerUsername, rentedRate, rateId, productStatus, Score, Comment, City;

            std::cin.ignore(); // Clear the newline left in the buffer

            std::cout << "Model: ";
            std::getline(std::cin, model);

            std::cout << "Color: ";
            std::getline(std::cin, color);

            std::cout << "Engine Size: ";
            std::getline(std::cin, engineSize);

            std::cout << "Transmission Mode: ";
            std::getline(std::cin, transmissionMode);

            std::cout << "Year Made: ";
            std::getline(std::cin, yearMade);

            std::cout << "Description: ";
            std::getline(std::cin, description);

            std::cout << "Owner Username: ";
            std::getline(std::cin, ownerUsername);

            std::cout << "Expected Rented Rate: ";
            std::getline(std::cin, rentedRate);

            std::cout << "Rate ID: ";
            std::getline(std::cin, rateId);

            std::cout << "Product status: ";
            std::getline(std::cin, productStatus);
            
            std::cout << "Score: ";
            std::getline(std::cin, Score);

            std::cout << "Comment: ";
            std::getline(std::cin, Comment);

            std::cout << "City: ";
            std::getline(std::cin, City);

            // Write the new motorbike details to the file
            productFile << "\nMotorbikeID: " << motorbikeId << std::endl;
            productFile << "Model: " << model << std::endl;
            productFile << "Color: " << color << std::endl;
            productFile << "Engine Size: " << engineSize << std::endl;
            productFile << "Transmission Mode: " << transmissionMode << std::endl;
            productFile << "Year Made: " << yearMade << std::endl;
            productFile << "Description: " << description << std::endl;
            productFile << "Owner Username: " << ownerUsername << std::endl;
            productFile << "Expected Rented Rate: " << rentedRate << std::endl;
            productFile << "Rate ID: " << rateId << std::endl;
            productFile << "Product status: " << productStatus << std::endl;
            productFile << "Score: " << Score << std::endl;
            productFile << "Comment: " << Comment << std::endl;
            productFile << "City: " << City << std::endl;

            productFile.close();
            std::cout << "New motorbike added successfully." << std::endl;
        } else {
            std::cerr << "Failed to open product details file." << std::endl;
        }
    }

    // Add this function inside the AdminUI class in AdminUI.h

    static bool motorbikeIdExists(const std::string& motorbikeId) {
        std::ifstream productFile("ProductDetail.txt");
        std::string line;

        while (std::getline(productFile, line)) {
            if (line.find("MotorbikeID: " + motorbikeId) != std::string::npos) {
                productFile.close();
                return true; // MotorbikeID already exists
            }
        }

        productFile.close();
        return false; // MotorbikeID does not exist
    }

        static void DeleteMotorbikeById() {
        std::cout << "Enter the MotorbikeID to delete: ";
        std::string motorbikeIdToDelete;
        std::cin >> motorbikeIdToDelete;

        std::string fileName = "ProductDetail.txt";
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
            if (lines[i].find("MotorbikeID: " + motorbikeIdToDelete) != std::string::npos) {
                // Remove the lines corresponding to the motorbike
                for (int j = 0; j < 14; j++) {
                    lines.erase(lines.begin() + i);
                }

                std::ofstream outputFile(fileName);
                if (outputFile) {
                    for (const std::string &modifiedLine : lines) {
                        outputFile << modifiedLine << std::endl;
                    }

                    outputFile.close();
                    std::cout << "Motorbike deleted successfully." << std::endl;
                } else {
                    std::cout << "Error writing to the file." << std::endl;
                }

                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "MotorbikeID not found." << std::endl;
        }
    }

};

#endif // ADMINUI_H
