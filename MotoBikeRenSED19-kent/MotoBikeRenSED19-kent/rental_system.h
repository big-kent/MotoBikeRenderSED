#ifndef RENTAL_SYSTEM_H
#define RENTAL_SYSTEM_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

// Define a struct to represent a motorbike
struct Motorbike {
    int MotorbikeID;
    std::string Model;
    std::string Color;
    int EngineSize;
    std::string TransmissionMode;
    int YearMade;
    std::string Description;
    std::string ownerUsername;
    float ExpectedRentedRate;
    int RateID;
    std::string ProductStatus;
    int Score;
    int Credit;
    std::string Comment;
    std::string City;
};

struct RentalRequest {
    std::string renterUsername;
    int motorbikeID;
    std::string ownerUsername;
    std::string status; // e.g., "pending", "accepted", "rejected"
};

// Create a vector to store rental requests
std::vector<RentalRequest> rentalRequests;

// Function to display motorbike data
void displayMotorbikeData(const std::vector<Motorbike>& motorbikes, const std::string& desiredCity, int userScore) {
    // Display available motorbikes in the desired city
    std::cout << "The motorbikes available for " << desiredCity << " city:" << std::endl;

    bool found = false;

    for (const Motorbike& bike : motorbikes) {
        if (bike.City == desiredCity && bike.ProductStatus == "available" && (userScore >= bike.Score || userScore == 0)) {
            // Display the motorbike information
            std::cout << "MotorbikeID: " << bike.MotorbikeID << std::endl;
            std::cout << "Model: " << bike.Model << std::endl;
            std::cout << "Color: " << bike.Color << std::endl;
            std::cout << "Engine Size: " << bike.EngineSize << std::endl;
            std::cout << "Transmission Mode: " << bike.TransmissionMode << std::endl;
            std::cout << "Year Made: " << bike.YearMade << std::endl;
            std::cout << "Description: " << bike.Description << std::endl;
            std::cout << "Owner username: " << bike.ownerUsername << std::endl;
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
        std::cout << "No available motorbikes found in " << desiredCity << " city with a score lower than or equal to your score." << std::endl;
        return;
    }
    return;
}

// Function to send a rental request message
void sendRentalRequest(const std::string& renterUsername, int motorbikeID, const std::string& ownerUsername) {
    std::cout << "Sending rental request to the motorbike owner..." << std::endl;
    std::cout << "Request Message: " << renterUsername << " wants to rent your motorbike (ID: " << motorbikeID << ")." << std::endl;
    std::cout << "Sent to owner: " << ownerUsername << std::endl;

    // Save the rental request
    RentalRequest request;
    request.renterUsername = renterUsername;
    request.motorbikeID = motorbikeID;
    request.ownerUsername = ownerUsername;
    request.status = "pending";

    rentalRequests.push_back(request);
}

void updateProductStatus(const std::string& motorbikeID, const std::string& newStatus) {
    std::ifstream inputFile("ProductDetail.txt");
    if (!inputFile) {
        std::cerr << "Error: Cannot open ProductDetail.txt for reading." << std::endl;
        return;
    }

    std::ofstream outputFile("temp_ProductDetail.txt");
    if (!outputFile) {
        std::cerr << "Error: Cannot create temp_ProductDetail.txt for writing." << std::endl;
        inputFile.close();
        return;
    }

    std::string line;
    bool foundMotorbike = false;

    while (std::getline(inputFile, line)) {
        if (line.find("MotorbikeID: " + motorbikeID) != std::string::npos) {
            // Found the motorbike, update its Product status
            outputFile << line << '\n';

            // Skip lines until we find the "Product status" line
            while (std::getline(inputFile, line) && line.find("Product status:") == std::string::npos) {
                outputFile << line << '\n';
            }

            // Update the "Product status" line
            outputFile << "Product status: " << newStatus << '\n';
            foundMotorbike = true;
        } else {
            // Copy other lines as they are
            outputFile << line << '\n';
        }
    }

    inputFile.close();
    outputFile.close();

    // Rename the temp file to replace the original
    if (foundMotorbike) {
        if (std::remove("ProductDetail.txt") != 0) {
            std::cerr << "Error: Unable to remove ProductDetail.txt" << std::endl;
            return;
        }

        if (std::rename("temp_ProductDetail.txt", "ProductDetail.txt") != 0) {
            std::cerr << "Error: Unable to rename temp_ProductDetail.txt" << std::endl;
        }
    } else {
        std::cerr << "Error: Motorbike with ID " << motorbikeID << " not found." << std::endl;
    }
}

// Function to view rental requests and approve or reject them
void viewRentalRequests(const std::string& ownerUsername) {
    // Open the ProductDetail.txt file to read and update motorbike information
    std::ifstream productDetailFile("ProductDetail.txt");
    if (!productDetailFile.is_open()) {
        std::cerr << "Unable to open ProductDetail.txt." << std::endl;
        return;
    }

    // Temporary storage for motorbike details
    std::vector<std::string> motorbikeDetails;
    std::string line;

    // Read and store motorbike details
    while (std::getline(productDetailFile, line)) {
        motorbikeDetails.push_back(line);
    }

    // Close the ProductDetail.txt file
    productDetailFile.close();

    // Open the userAccount.txt file to read and update user information
    std::ifstream userAccountFile("userAccount.txt");
    if (!userAccountFile.is_open()) {
        std::cerr << "Unable to open userAccount.txt." << std::endl;
        return;
    }

    // Temporary storage for user account details
    std::vector<std::string> userAccountDetails;

    // Read and store user account details
    while (std::getline(userAccountFile, line)) {
        userAccountDetails.push_back(line);
    }

    // Close the userAccount.txt file
    userAccountFile.close();

    // Iterate through rentalRequests to find pending requests for the owner
    for (RentalRequest& request : rentalRequests) {
        if (request.ownerUsername == ownerUsername && request.status == "pending") {
            std::cout << "From: " << request.renterUsername << " (Motorbike ID: " << request.motorbikeID << ")" << std::endl;

            // Prompt owner for approval
            std::string approval;
            do {
                std::cout << "Do you want to approve this request? (yes/no): ";
                std::cin >> approval;
                if (approval != "yes" && approval != "no") {
                    std::cout << "Invalid input. Please enter 'yes' or 'no'." << std::endl;
                }
            } while (approval != "yes" && approval != "no");

            if (approval == "yes") {
                // Mark the request as approved
                request.status = "approved";
                std::cout << "Request approved. " << ownerUsername << " has granted permission to rent the motorbike." << std::endl;
                
                // Update the Product status to "unavailable"
                updateProductStatus(std::to_string(request.motorbikeID), "unavailable");

                // Find the motorbike with the specified motorbikeID and get its credit (price)
                int motorbikeCredit = 0;
                for (size_t i = 0; i < motorbikeDetails.size(); ++i) {
                    if (motorbikeDetails[i].find("MotorbikeID: " + std::to_string(request.motorbikeID)) != std::string::npos) {
                        std::istringstream iss(motorbikeDetails[i + 13]);
                        iss.ignore(8); // Skip "Credit: "
                        iss >> motorbikeCredit;
                        break;
                    }
                }

                // Find the renter in userAccount.txt and update their credit
                for (size_t i = 0; i < userAccountDetails.size(); ++i) {
                    if (userAccountDetails[i].find(request.renterUsername) != std::string::npos) {
                        std::istringstream iss(userAccountDetails[i]);
                        std::string dummy, username, password;
                        int userCredit;
                        iss >> username >> password >> userCredit;

                        // Check if the user has enough credit to rent the motorbike
                        if (userCredit >= motorbikeCredit) {
                            // Subtract the motorbike credit (price) from the user's credit
                            userCredit -= motorbikeCredit;

                            // Update user credit in userAccountDetails vector
                            std::ostringstream oss;
                            oss << username << " " << password << " " << userCredit << " 8";
                            userAccountDetails[i] = oss.str();

                            std::cout << "Motorbike rented successfully. Credits updated." << std::endl;
                        } else {
                            std::cout << "Insufficient credit to rent the motorbike." << std::endl;
                        }
                        break;
                    }
                }
            } else {
                // Mark the request as rejected
                request.status = "rejected";
                std::cout << "Request rejected. " << ownerUsername << " has declined the rental request." << std::endl;
            }
        }
    }

    // Write the updated user account details back to userAccount.txt
    std::ofstream updatedUserAccountFile("userAccount.txt");
    if (updatedUserAccountFile.is_open()) {
        for (const auto& detail : userAccountDetails) {
            updatedUserAccountFile << detail << "\n";
        }
        updatedUserAccountFile.close();
    } else {
        std::cerr << "Unable to open userAccount.txt for writing." << std::endl;
    }
}




// Function to rent a motorbike
void rentMotorbike(const std::string& username) {
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
        } else if (line.find("Owner username: ") != std::string::npos) {
            currentMotorbike.ownerUsername = line.substr(16);
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

    // Open the user account file
    std::ifstream userAccountFile("userAccount.txt");

    if (!userAccountFile.is_open()) {
        std::cerr << "Error: Unable to open the user account file." << std::endl;
        return;
    }

std::vector<std::pair<std::string, std::pair<int, int>>> userAccounts;

// Read user account data and populate the vector
std::string userLine;
while (std::getline(userAccountFile, userLine)) {
    std::istringstream userStream(userLine);
    std::string username, password;
    int credit, score;

    userStream >> username >> password >> credit >> score;

    userAccounts.push_back(std::make_pair(username, std::make_pair(credit, score)));
}

// Check if the provided username exists in the userAccounts vector
bool userFound = false;
std::pair<int, int> userData; // Credit and Score

for (const auto& userAccount : userAccounts) {
    if (userAccount.first == username) {
        userFound = true;
        userData = userAccount.second; // Extract credit and score
        break;
    }
}

if (!userFound) {
    std::cout << "User '" << username << "' not found." << std::endl;
    return;
}

// Display the user's credit and score on the same line
int userCredit = userData.first;
int userScore = userData.second;
std::cout << "User: " << username << ", Credit: " << userCredit << ", Score: " << userScore <<"\n"<<std::endl;


    // Prompt the user for the desired city
    std::string desiredCity;
    std::cout << "Enter the city where you want to rent a motorbike: ";
    std::cin.ignore();
    std::getline(std::cin, desiredCity);

    // Call the function to display motorbike data with the user's score
    displayMotorbikeData(motorbikes, desiredCity, userScore);

    // Ask the user to enter the ID of the motorbike they want to rent
    int motorbikeID;
    std::cout << "Enter the ID of the motorbike you want to rent: ";
    std::cin >> motorbikeID;

    // Check if the selected motorbike is available and if the user's score is sufficient
    bool motorbikeFound = false;

    for (Motorbike& bike : motorbikes) {
        if (bike.MotorbikeID == motorbikeID && bike.City == desiredCity && bike.ProductStatus == "available" && (userScore >= bike.Score || userScore == 0)) {
            motorbikeFound = true;

            // Prompt the user to confirm the rental
            std::string confirmation;
            std::cout << "Do you want to rent this motorbike? (yes/no): ";
            std::cin >> confirmation;

            if (confirmation == "yes") {
                // Get the owner's username from the motorbike data
                std::string ownerUsername;
                for (const auto& bike : motorbikes) {
                    if (bike.MotorbikeID == motorbikeID) {
                        ownerUsername = bike.ownerUsername;
                        break;
                    }
                }

                // Call the function to send the rental request
                sendRentalRequest(username, motorbikeID, ownerUsername);
            } else {
                std::cout << "Rental canceled." << std::endl;
            }
            break;
        }
    }

    if (!motorbikeFound) {
        std::cout << "Motorbike not available or your score is not sufficient for this motorbike." << std::endl;
    }
}

#endif // RENTAL_SYSTEM_H
