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
    int ownerUsername;
    float ExpectedRentedRate;
    int RateID;
    std::string ProductStatus;
    int Score;
    std::string Comment;
    std::string City;
};

// Function to update the product status in ProductDetail.txt
void updateProductStatus(int motorbikeID) {
    // Open the file by name (without specifying a directory)
    std::ifstream inputFile("ProductDetail.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Read the entire content of the file into memory
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close(); // Close the input file

    bool foundMotorbikeID = false;
    bool foundProductStatus = false;

    // Loop through the lines and find the specified Motorbike ID
    for (int i = 0; i < lines.size(); ++i) {
        if (!foundMotorbikeID && lines[i].find("MotorbikeID: " + std::to_string(motorbikeID)) != std::string::npos) {
            foundMotorbikeID = true;
        } else if (foundMotorbikeID) {
            // Check if the line contains "Product status"
            if (lines[i].find("Product status: ") != std::string::npos) {
                // Update the "Product status" line to "Product status: unavailable"
                lines[i] = "Product status: unavailable";
                foundProductStatus = true;
                break; // Stop searching after updating
            }
        }
    }

    if (foundMotorbikeID && foundProductStatus) {
        // Open the file for writing
        std::ofstream outputFile("ProductDetail.txt");

        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open the output file." << std::endl;
            return;
        }

        // Write the modified lines back to the file
        for (const std::string& updatedLine : lines) {
            outputFile << updatedLine << std::endl;
        }

        outputFile.close(); // Close the output file
        std::cout << "Product status updated successfully." << std::endl;
    } else {
        std::cerr << "Motorbike ID not found or Product status not found after the specified Motorbike ID." << std::endl;
    }
}

// Function to display motorbike data
void displayMotorbikeData(const std::vector<Motorbike>& motorbikes, const std::string& desiredCity, int userScore) {
    // Display available motorbikes in the desired city
    std::cout << "The motorbikes available for " << desiredCity << " city:" << std::endl;

    bool found = false;

    for (const Motorbike& bike : motorbikes) {
        if (bike.City == desiredCity && bike.ProductStatus == "available" && userScore >= bike.Score) {
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
    }
}

// Define the structure for user profiles
struct UserProfile {
    std::string Username;
    std::string FullName;
    std::string Phone;
    std::string IDType;
    std::string IDNumber;
    std::string LicenseNumber;
    std::string ExpiredDate;
    int MotorbikeRentingID;
    std::string City;
    std::vector<std::string> IncomingRequests;
    std::string Message;

    // Function to update a user profile in the file
    void updateToFile() const {
        // Open the file for reading and writing
        std::ifstream inputFile("userProfile.txt");
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open the user profile file for reading." << std::endl;
            return;
        }

        // Create a temporary file for writing updated data
        std::ofstream tempFile("tempUserProfile.txt");
        if (!tempFile.is_open()) {
            std::cerr << "Error: Unable to open the temporary user profile file for writing." << std::endl;
            return;
        }

        std::string line;
        bool found = false;

        // Read and update user profiles
        while (std::getline(inputFile, line)) {
            if (line.find("Username: " + Username) != std::string::npos) {
                // Update the user profile here
                tempFile << "Username: " << Username << std::endl;
                tempFile << "Full Name: " << FullName << std::endl;
                tempFile << "Phone: " << Phone << std::endl;
                tempFile << "ID Type: " << IDType << std::endl;
                tempFile << "ID Number: " << IDNumber << std::endl;
                tempFile << "Driver's License Number: " << LicenseNumber << std::endl;
                tempFile << "Expired Date: " << ExpiredDate << std::endl;
                tempFile << "MotorbikeRentingID: " << MotorbikeRentingID << std::endl;
                tempFile << "City: " << City << std::endl;

                // Update the Incoming Requests field
                tempFile << "Incoming Requests: [";
                for (const std::string& request : IncomingRequests) {
                    tempFile << request << ", ";
                }
                tempFile << "]" << std::endl;

                // Update the Message field
                tempFile << "Message: " << Message << std::endl;

                found = true;
            } else {
                tempFile << line << std::endl;
            }
        }

        // Close both files
        inputFile.close();
        tempFile.close();

        // Rename the temporary file to overwrite the original file
        if (found) {
            if (std::remove("userProfile.txt") == 0 && std::rename("tempUserProfile.txt", "userProfile.txt") == 0) {
                std::cout << "User profile updated successfully." << std::endl;
            } else {
                std::cerr << "Error: Unable to update the user profile." << std::endl;
            }
        } else {
            std::cerr << "Error: User profile not found." << std::endl;
        }
    }
};

// Define the structure for motorbike data
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
    std::string Comment;
    std::string City;
    std::string RentalRequestUsername; // New field to store requesting user

    // Function to update motorbike data in the file
    void updateToFile() const {
        // Open the file for reading and writing
        std::ifstream inputFile("ProductDetail.txt");
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open the motorbike data file for reading." << std::endl;
            return;
        }

        // Create a temporary file for writing updated data
        std::ofstream tempFile("tempProductDetail.txt");
        if (!tempFile.is_open()) {
            std::cerr << "Error: Unable to open the temporary motorbike data file for writing." << std::endl;
            return;
        }

        std::string line;
        bool found = false;

        // Read and update motorbike data
        while (std::getline(inputFile, line)) {
            if (line.find("MotorbikeID: " + std::to_string(MotorbikeID)) != std::string::npos) {
                // Update the motorbike data here
                tempFile << "MotorbikeID: " << MotorbikeID << std::endl;
                tempFile << "Model: " << Model << std::endl;
                tempFile << "Color: " << Color << std::endl;
                tempFile << "Engine Size: " << EngineSize << std::endl;
                tempFile << "Transmission Mode: " << TransmissionMode << std::endl;
                tempFile << "Year Made: " << YearMade << std::endl;
                tempFile << "Description: " << Description << std::endl;
                tempFile << "Owner username: " << ownerUsername << std::endl;
                tempFile << "Expected Rented Rate: " << ExpectedRentedRate << "%" << std::endl;
                tempFile << "Rate ID: " << RateID << std::endl;

                // Update the Product status field
                tempFile << "Product status: " << ProductStatus << std::endl;
                
                tempFile << "Score: " << Score << std::endl;
                tempFile << "Comment: " << Comment << std::endl;
                tempFile << "City: " << City << std::endl;

                // Update the Rental Request Username field
                tempFile << "Rental Request Username: " << RentalRequestUsername << std::endl;

                found = true;
            } else {
                tempFile << line << std::endl;
            }
        }

        // Close both files
        inputFile.close();
        tempFile.close();

        // Rename the temporary file to overwrite the original file
        if (found) {
            if (std::remove("ProductDetail.txt") == 0 && std::rename("tempProductDetail.txt", "ProductDetail.txt") == 0) {
                std::cout << "Motorbike data updated successfully." << std::endl;
            } else {
                std::cerr << "Error: Unable to update motorbike data." << std::endl;
            }
        } else {
            std::cerr << "Error: Motorbike data not found." << std::endl;
        }
    }
};

// Function to handle incoming rental requests for a user
void handleIncomingRequests(const std::string& username) {
    // Find the user profile for the logged-in user
    UserProfile currentUserProfile;

    // Load user profile data from "userProfile.txt"
    std::ifstream userProfileFile("userProfile.txt");
    if (userProfileFile.is_open()) {
        std::string line;
        while (std::getline(userProfileFile, line)) {
            if (line.find("Username: " + username) != std::string::npos) {
                currentUserProfile.Username = username;
                while (std::getline(userProfileFile, line) && line != "") {
                    if (line.find("Full Name: ") != std::string::npos) {
                        currentUserProfile.FullName = line.substr(11);
                    } else if (line.find("Phone: ") != std::string::npos) {
                        currentUserProfile.Phone = line.substr(7);
                    } else if (line.find("ID Type: ") != std::string::npos) {
                        currentUserProfile.IDType = line.substr(9);
                    } else if (line.find("ID Number: ") != std::string::npos) {
                        currentUserProfile.IDNumber = line.substr(11);
                    } else if (line.find("Driver's License Number: ") != std::string::npos) {
                        currentUserProfile.LicenseNumber = line.substr(24);
                    } else if (line.find("Expired Date: ") != std::string::npos) {
                        currentUserProfile.ExpiredDate = line.substr(14);
                    } else if (line.find("MotorbikeRentingID: ") != std::string::npos) {
                        currentUserProfile.MotorbikeRentingID = std::stoi(line.substr(21));
                    } else if (line.find("City: ") != std::string::npos) {
                        currentUserProfile.City = line.substr(6);
                    } else if (line.find("Incoming Requests: [") != std::string::npos) {
                        // Parse and load the incoming requests list
                        size_t startPos = line.find("[");
                        size_t endPos = line.find("]");
                        if (startPos != std::string::npos && endPos != std::string::npos) {
                            std::string requestsStr = line.substr(startPos + 1, endPos - startPos - 1);
                            size_t pos = 0;
                            while ((pos = requestsStr.find(", ")) != std::string::npos) {
                                currentUserProfile.IncomingRequests.push_back(requestsStr.substr(0, pos));
                                requestsStr.erase(0, pos + 2);
                            }
                        }
                    } else if (line.find("Message: ") != std::string::npos) {
                        currentUserProfile.Message = line.substr(9);
                    }
                }
                break;
            }
        }
        userProfileFile.close();
    } else {
        std::cerr << "Error: Unable to open the user profile file." << std::endl;
        return;
    }

    // Display incoming requests
    std::cout << "Incoming Requests for User '" << username << "':" << std::endl;
    for (const std::string& request : currentUserProfile.IncomingRequests) {
        std::cout << "Request from: " << request << std::endl;
        
        // Prompt the user to confirm or reject the request
        std::string confirmation;
        std::cout << "Confirm this request? (yes/no): ";
        std::cin >> confirmation;

        // If the user confirms, update motorbike status and remove request
        if (confirmation == "yes") {
            // Load motorbike data for the request
            Motorbike motorbike;

            // Load motorbike data from "ProductDetail.txt"
            std::ifstream motorbikeFile("ProductDetail.txt");
            if (motorbikeFile.is_open()) {
                std::string line;
                while (std::getline(motorbikeFile, line)) {
                    if (line.find("MotorbikeID: " + request) != std::string::npos) {
                        motorbike.MotorbikeID = std::stoi(request);
                        while (std::getline(motorbikeFile, line) && line != "") {
                            if (line.find("Model: ") != std::string::npos) {
                                motorbike.Model = line.substr(7);
                            } else if (line.find("Color: ") != std::string::npos) {
                                motorbike.Color = line.substr(7);
                            } else if (line.find("Engine Size: ") != std::string::npos) {
                                motorbike.EngineSize = std::stoi(line.substr(13));
                            } else if (line.find("Transmission Mode: ") != std::string::npos) {
                                motorbike.TransmissionMode = line.substr(19);
                            } else if (line.find("Year Made: ") != std::string::npos) {
                                motorbike.YearMade = std::stoi(line.substr(12));
                            } else if (line.find("Description: ") != std::string::npos) {
                                motorbike.Description = line.substr(13);
                            } else if (line.find("Owner username: ") != std::string::npos) {
                                motorbike.ownerUsername = line.substr(16);
                            } else if (line.find("Expected Rented Rate: ") != std::string::npos) {
                                motorbike.ExpectedRentedRate = std::stof(line.substr(21));
                            } else if (line.find("Rate ID: ") != std::string::npos) {
                                motorbike.RateID = std::stoi(line.substr(9));
                            } else if (line.find("Product status: ") != std::string::npos) {
                                motorbike.ProductStatus = line.substr(16);
                            } else if (line.find("Score: ") != std::string::npos) {
                                motorbike.Score = std::stoi(line.substr(7));
                            } else if (line.find("Comment: ") != std::string::npos) {
                                motorbike.Comment = line.substr(9);
                            } else if (line.find("City: ") != std::string::npos) {
                                motorbike.City = line.substr(6);
                            } else if (line.find("Rental Request Username: ") != std::string::npos) {
                                motorbike.RentalRequestUsername = line.substr(26);
                            }
                        }
                        break;
                    }
                }
                motorbikeFile.close();
            } else {
                std::cerr << "Error: Unable to open the motorbike data file." << std::endl;
                return;
            }

            // Check if the motorbike status is "available" and the request is from the owner
            if (motorbike.ProductStatus == "available" && motorbike.ownerUsername == username) {
                // Update motorbike status to "unavailable"
                motorbike.ProductStatus = "unavailable";
                motorbike.RentalRequestUsername = ""; // Clear the request username

                // Update motorbike data in the file
                motorbike.updateToFile();

                std::cout << "Motorbike rented successfully. Status updated." << std::endl;
            } else {
                std::cerr << "Error: Motorbike not available or not owned by user." << std::endl;
            }

            // Remove the request from the user's incoming requests
            auto it = std::find(currentUserProfile.IncomingRequests.begin(), currentUserProfile.IncomingRequests.end(), request);
            if (it != currentUserProfile.IncomingRequests.end()) {
                currentUserProfile.IncomingRequests.erase(it);
            }
        } else {
            std::cout << "Request rejected." << std::endl;
        }
    }

    // Update user profile with the modified incoming requests list
    currentUserProfile.updateToFile();
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
        } else if (line.find("Rental Request Username: ") != std::string::npos) {
            currentMotorbike.RentalRequestUsername = line.substr(26);
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

    std::vector<std::pair<std::string, int>> userAccounts;

    // Read user account data and populate the vector
    std::string userLine;
    while (std::getline(userAccountFile, userLine)) {
        std::istringstream userStream(userLine);
        std::string username, password;
        int credit, score;

        userStream >> username >> password >> credit >> score;

        userAccounts.push_back(std::make_pair(username, score));
    }

    // Check if the provided username exists in the userAccounts vector
    bool userFound = false;
    int userScore = 0;

    for (const auto& userAccount : userAccounts) {
        if (userAccount.first == username) {
            userFound = true;
            userScore = userAccount.second;
            break;
        }
    }

    if (!userFound) {
        std::cout << "User '" << username << "' not found." << std::endl;
        return;
    }

    // Display the user's score
    std::cout << "User '" << username << "' Score: " << userScore << std::endl;

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
        if (bike.MotorbikeID == motorbikeID && bike.City == desiredCity && bike.ProductStatus == "available" && userScore >= bike.Score) {
            motorbikeFound = true;

            // Prompt the user to confirm the rental
            std::string confirmation;
            std::cout << "Do you want to rent this motorbike? (yes/no): ";
            std::cin >> confirmation;

            if (confirmation == "yes") {
                // Update the product status in memory to "unavailable"
                bike.ProductStatus = "unavailable";
                bike.RentalRequestUsername = username; // Store requesting user

                // Update the product status and request username in the file
                bike.updateToFile();

                std::cout << "Motorbike rented successfully! Product status updated." << std::endl;
            } else {
                std::cout << "Rental canceled." << std::endl;
            }

            break;
        }
    }

    if (!motorbikeFound) {
        std::cout << "Motorbike not available or your score is not sufficient for this motorbike." << std::endl;
    }

    // Handle incoming rental requests for the user
    handleIncomingRequests(username);
}

#endif // RENTAL_SYSTEM_H
