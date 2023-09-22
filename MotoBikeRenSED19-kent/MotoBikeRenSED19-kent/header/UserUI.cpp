
#include "rental_system.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "searchEngine.h"
#include <limits>
#include "UserUI.h"

void UserUI::showMenu(const std::string &username)
{
    int choice;

    while (true)
    {
        std::cout << "\nMember Menu for " << username << ":" << std::endl;
        std::cout << "1. Edit My Profile" << std::endl;
        std::cout << "2. View the motorbike's reviews" << std::endl;
        std::cout << "3. Search Motorbikes by City" << std::endl;
        std::cout << "4. Apply a new motorbike for rental service" << std::endl;
        std::cout << "5. Rent a Motorbike" << std::endl;
        std::cout << "6. View Rental Requests" << std::endl;
        std::cout << "7. View Rental responses" << std::endl;
        std::cout << "8. Return the motorbike to the rental service" << std::endl;
        std::cout << "9. Check return motorbike message from renter" << std::endl;
        std::cout << "10. Add more credit point to your account" << std::endl;
        std::cout << "11. Exit" << std::endl;
        std::cout << "Enter your choice (1-10): ";

        if (!(std::cin >> choice) || choice < 1 || choice > 11)
        {
            // Input is not a valid integer in the range (1-10)
            std::cin.clear();                                                   // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
            std::cout << "Invalid input. Please enter a valid integer choice (1-10).\n"
                      << std::endl;
            continue; // Skip the rest of the loop iteration and ask for input again
        }

        switch (choice)
        {
        case 1:
            editUserProfile(username);
            break;
        case 2:
            displayMotorbikeScoreAndComment();
            break;
        case 3:
            SearchEngine::searchMotorbikesByCity();
            break;
        case 4:
            applyMotorbikeForRent(username);
            break;
        case 5:
            rentMotorbike(username);
            break;
        case 6:
            viewRentalRequests(username);
            break;
        case 7:
            viewRenterResponses(username);
            break;
        case 8:
            returnMotorbike(username);
            break;
        case 9:
            checkReturnMessages(username);
            break;
        case 10:
            addMoreCreditPointsToYourAccount(username);
            break;
        case 11:
            std::cout << "\nExiting " << username << "'s Menu. Goodbye!!!\n"
                      << std::endl;
            return;
        default:
            break;
        }
    }
}

void UserUI::editUserProfile(const std::string &username)
{
    std::string fileName = "userProfile.txt"; // Use just the file name

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
        if (lines[i].find("Username: " + username) != std::string::npos)
        {
            // User profile found, display and edit details
            std::cout << "Found user profile for: " << username << std::endl;
            std::cout << "Current details:" << std::endl;

            // Print current details
            for (size_t j = i; j < i + 8; j++)
            {
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

            std::cout << "ID Type (Citizen ID/Passport): ";
            std::string newIdType;
            std::cin.ignore();
            std::getline(std::cin, newIdType);
            lines[i + 3] = "ID Type (Citizen ID/Passport): " + newIdType;

            std::cout << "id/passport number: ";
            std::string newIdNumber;
            std::getline(std::cin, newIdNumber);
            lines[i + 4] = "id/passport number: " + newIdNumber;

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
            if (outputFile)
            {
                for (const std::string &modifiedLine : lines)
                {
                    outputFile << modifiedLine << std::endl;
                }

                outputFile.close();
                std::cout << "User profile updated successfully." << std::endl;
            }
            else
            {
                std::cout << "Error writing to the file." << std::endl;
            }

            found = true;
            break; // Exit the loop after editing
        }
    }

    if (!found)
    {
        std::cout << "User profile not found." << std::endl;
    }
    else
    {
        std::cout << "\nPlease fill your profile first" << std::endl;
    }
}

void UserUI::displayMotorbikeScoreAndComment()
{
    int motorbikeID;

    // Ask the user to enter the motorbike ID
    std::cout << "Enter the MotorbikeID: ";
    std::cin >> motorbikeID;

    std::ifstream inputFile("ProductDetail.txt");

    if (!inputFile)
    {
        std::cerr << "Failed to open ProductDetail.txt" << std::endl;
        return;
    }

    std::string line;
    bool foundMotorbike = false;
    int linesAfterID = 0;

    while (std::getline(inputFile, line))
    {
        if (line.find("MotorbikeID: " + std::to_string(motorbikeID)) != std::string::npos)
        {
            foundMotorbike = true;
            std::cout << "\nReview for motorbike with ID: " << motorbikeID << std::endl;
            continue; // Skip the line with MotorbikeID
        }

        if (foundMotorbike)
        {
            linesAfterID++;
            if (linesAfterID == 11)
            {
                // Display the score
                std::cout << line << std::endl;
            }
            else if (linesAfterID == 12)
            {
                // Display the comment
                std::cout << line << std::endl;
                break; // Stop reading after finding the comment
            }
        }
    }

    if (!foundMotorbike)
    {
        std::cout << "Motorbike with ID " << motorbikeID << " not found." << std::endl;
    }

    inputFile.close();
};
