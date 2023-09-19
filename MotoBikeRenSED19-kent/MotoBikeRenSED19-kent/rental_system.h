#ifndef RENTAL_SYSTEM_H
#define RENTAL_SYSTEM_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

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

std::vector<std::pair<std::string, std::pair<int, int>>> userAccounts;

// Define a global vector to keep track of rented motorbikes and their respective usernames
std::vector<std::pair<std::string, int>> rentedMotorbikes;

// Function to display motorbike data
void displayMotorbikeData(const std::vector<Motorbike>& motorbikes, const std::string& desiredCity, int userScore, int userCredit) {
    // Display available motorbikes in the desired city
    std::cout << "The motorbikes available for " << desiredCity << " city:" << std::endl;

    bool found = false;

    for (const Motorbike& bike : motorbikes) {
        if (bike.City == desiredCity && bike.ProductStatus == "available" && (userScore >= bike.Score || userScore == 0) && userCredit > bike.Credit) {
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
            std::cout << "Latest comment: " << bike.Comment << std::endl;
            std::cout << "Credit: " << bike.Credit << std::endl;
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

void sendRentalRequest(const std::string& renterUsername, int motorbikeID, const std::string& ownerUsername) {
    if (renterUsername == ownerUsername) {
        std::cout << "You cannot rent your own motorbike; you should rent a motorbike from others." << std::endl;
        return; // Exit the function, as the user cannot rent their own motorbike.
    }

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

// Function to view rental request responses for renters
void viewRenterResponses(const std::string& renterUsername) {
    // Initialize a flag to check if there are responses for the renter
    bool hasResponses = false;

    // Iterate through rentalRequests to find responses for the renter
    for (const RentalRequest& request : rentalRequests) {
        if (request.renterUsername == renterUsername) {
            if (request.status == "approved") {
                std::cout << "Your rental request for Motorbike ID " << request.motorbikeID << " has been approved by "<< request.ownerUsername << std::endl;
            } else if (request.status == "rejected") {
                std::cout << "Your rental request for Motorbike ID " << request.motorbikeID << " has been rejected by "<< request.ownerUsername << std::endl;
            }
            hasResponses = true;
        }
    }

    // Check if there are responses for the renter
    if (!hasResponses) {
        std::cout << "You do not have any rental request responses right now." << std::endl;
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

    // Initialize a flag to check if the owner has any pending requests
    bool hasPendingRequests = false;

    // Iterate through rentalRequests to find pending requests for the owner
    for (RentalRequest& request : rentalRequests) {
        if (request.ownerUsername == ownerUsername && request.status == "pending") {
            hasPendingRequests = true; // Set the flag to true
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
                        int userScore;
                        int userRatingTime;
                        iss >> username >> password >> userCredit >> userScore >> userRatingTime;

                        // Check if the user has enough credit to rent the motorbike
                        if (userCredit >= motorbikeCredit) {
                            // Subtract the motorbike credit (price) from the user's credit
                            userCredit -= motorbikeCredit;

                            // Update user credit in userAccountDetails vector
                            std::ostringstream oss;
                            oss << username << " " << password << " " << userCredit << " " << userScore << " " << userRatingTime;
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

    // Check if the owner has any pending requests
    if (!hasPendingRequests) {
        std::cout << "You do not have any rental requests right now." << std::endl;
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


// Function to check if a user has already rented a motorbike
bool hasUserRented(const std::string& username) {
    for (const auto& rental : rentedMotorbikes) {
        if (rental.first == username) {
            return true; // User has already rented a motorbike
        }
    }
    return false; // User has not rented any motorbike
}

// Function to rent a motorbike
void rentMotorbike(const std::string& username) {

    // Check if the user is trying to rent their own motorbike
    bool isRentingOwnMotorbike = false;

    for (const auto& request : rentalRequests) {
        if (request.renterUsername == username && request.status == "pending") {
            isRentingOwnMotorbike = true;
            break;
        }
    }

    if (isRentingOwnMotorbike) {
        std::cout << "You have already attempted to rent your own motorbike, or a rental request is pending." << std::endl;
        return;
    }
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

    // Open the user account file
    std::ifstream userAccountFile("userAccount.txt");

    if (!userAccountFile.is_open()) {
        std::cerr << "Error: Unable to open the user account file." << std::endl;
        return;
    }

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
    displayMotorbikeData(motorbikes, desiredCity, userScore, userCredit);

    // Ask the user to enter the ID of the motorbike they want to rent
    int motorbikeID;
    std::cout << "Enter the ID of the motorbike you want to rent: ";
    std::cin >> motorbikeID;

    // Check if the selected motorbike is available and if the user's score is sufficient
    bool motorbikeFound = false;

    for (Motorbike& bike : motorbikes) {
        if (bike.MotorbikeID == motorbikeID && bike.City == desiredCity && bike.ProductStatus == "available" && (userScore >= bike.Score || userScore == 0) && userCredit > bike.Credit) {
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
                rentedMotorbikes.push_back(std::make_pair(username, motorbikeID));
            } else {
                std::cout << "Rental canceled." << std::endl;
            }
            break;
        }
    }

    if (!motorbikeFound) {
        std::cout << "Motorbike not available or your score, credit is not sufficient for this motorbike." << std::endl;
        std::cout << "Please try to type the right city name or check your score and credit again !!!" << std::endl;
    }
}

// Function to check if a motorbike ID already exists
bool motorbikeIdExists(const std::string& motorbikeId) {
    // Open the file for reading
    std::ifstream inputFile("ProductDetail.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file." << std::endl;
        return false; // Return false to indicate an error
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        // Search for lines that contain "MotorbikeID:" and compare the ID
        if (line.find("MotorbikeID: ") != std::string::npos) {
            std::string existingId = line.substr(13); // Extract the ID from the line
            if (existingId == motorbikeId) {
                inputFile.close(); // Close the file
                return true; // ID exists in the file
            }
        }
    }

    inputFile.close(); // Close the file
    return false; // ID not found in the file
}

// Function to rent a motorbike
void applyMotorbikeForRent(const std::string& username) {
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
        std::string model, color, engineSize, transmissionMode, yearMade, description, rentedRate, rateId, Comment,Credit, City;

        std::cin.ignore(); // Clear the newline left in the buffer

        std::cout << "Model: ";
        std::getline(std::cin, model);

        std::cout << "Color: ";
        std::getline(std::cin, color);

        std::cout << "Engine Size: ";
        std::getline(std::cin, engineSize);

        std::cout << "Transmission Mode (Automatic, Manual, Electronic): ";
        std::getline(std::cin, transmissionMode);

        std::cout << "Year Made: ";
        std::getline(std::cin, yearMade);

        std::cout << "Description: ";
        std::getline(std::cin, description);

        // Set the owner username to be the same as the applying user's username
        std::string ownerUsername = username;

        std::cout << "Expected Rented Rate: ";
        std::getline(std::cin, rentedRate);

        std::cout << "Rate ID: ";
        std::getline(std::cin, rateId);

        std::cout << "Latest comment: ";
        std::getline(std::cin, Comment);

        std::cout << "Credit needed for renting: ";
        std::getline(std::cin, Credit);

        std::cout << "City: ";
        std::getline(std::cin, City);

        // Write a blank line before writing the new motorbike details to the file
        productFile << "\n";

        // Write the new motorbike details to the file
        productFile << "MotorbikeID: " << motorbikeId << std::endl;
        productFile << "Model: " << model << std::endl;
        productFile << "Color: " << color << std::endl;
        productFile << "Engine Size: " << engineSize << std::endl;
        productFile << "Transmission Mode: " << transmissionMode << std::endl;
        productFile << "Year Made: " << yearMade << std::endl;
        productFile << "Description: " << description << std::endl;
        productFile << "Owner username: " << ownerUsername << std::endl;
        productFile << "Expected Rented Rate: " << rentedRate << std::endl;
        productFile << "Rate ID: " << rateId << std::endl;
        productFile << "Product status: available" << std::endl;
        productFile << "Score: " << 0 << std::endl;
        productFile << "Latest comment: " << Comment << std::endl;
        productFile << "Credit: " << Credit << std::endl;
        productFile << "City: " << City << std::endl;

        productFile.close();
        std::cout << "New motorbike added successfully." << std::endl;
    } else {
        std::cerr << "Failed to open product details file." << std::endl;
    }
}

// Function to add more credit points to a user's account with credit milestones
void addMoreCreditPointsToYourAccount(const std::string& username) {
    // Define the exchange rate: 1 credit = $1
    const int creditToDollarExchangeRate = 1;

    // Open the userAccount.txt file to read user account data
    std::ifstream userAccountFile("userAccount.txt");
    if (!userAccountFile.is_open()) {
        std::cerr << "Unable to open userAccount.txt." << std::endl;
        return;
    }

    // Temporary storage for user account details
    std::vector<std::string> userAccountDetails;

    // Read and store user account details
    std::string line;
    while (std::getline(userAccountFile, line)) {
        userAccountDetails.push_back(line);
    }

    // Close the userAccount.txt file
    userAccountFile.close();

    // Find the user's account by searching for their username
    int userIndex = -1;
    for (size_t i = 0; i < userAccountDetails.size(); ++i) {
        if (userAccountDetails[i].find(username) != std::string::npos) {
            userIndex = static_cast<int>(i);
            break;
        }
    }

    // Check if the user was found
    if (userIndex == -1) {
        std::cout << "User not found." << std::endl;
        return;
    }

    // Extract and display the user's current credit
    std::istringstream iss(userAccountDetails[userIndex]);
    std::string usernameFromFile, password;
    int currentCredit, score;
    iss >> usernameFromFile >> password >> currentCredit >> score;

    std::cout << "User:" << username << ", your current credits: " << currentCredit << " credits\n" << std::endl;

    // Define credit milestones with their equivalent dollar values
    std::vector<std::pair<int, int>> creditMilestones = {{5, 5}, {10, 10}, {20, 20}, {50, 50}, {100, 100}}; // Add more milestones as needed

    // Display available credit options to the user
    std::cout << "Available credit options:" << std::endl;
    for (size_t i = 0; i < creditMilestones.size(); ++i) {
        std::cout << i + 1 << ". " << creditMilestones[i].first << " credits = $" << creditMilestones[i].second << std::endl;
    }

    // Prompt the user to select a credit milestone
    int choice;
    do {
        std::cout << "\nEnter the number corresponding to your chosen credit milestone: ";
        if (!(std::cin >> choice) || choice < 1 || choice > static_cast<int>(creditMilestones.size())) {
            std::cout << "Invalid input. Please select a valid option." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > static_cast<int>(creditMilestones.size()));

    // Get the selected credit and dollar values
    int creditsToAdd = creditMilestones[choice - 1].first;
    int dollarsToAdd = creditMilestones[choice - 1].second;

    // Display payment method options
    std::cout << "\nSelect a payment method:" << std::endl;
    std::cout << "1. Cash" << std::endl;
    std::cout << "2. Credit card" << std::endl;
    std::cout << "3. Bank check" << std::endl;
    std::cout << "4. Internet banking" << std::endl;

    int paymentMethodChoice;
    do {
        std::cout << "\nEnter the number corresponding to your chosen payment method: ";
        if (!(std::cin >> paymentMethodChoice) || paymentMethodChoice < 1 || paymentMethodChoice > 4) {
            std::cout << "Invalid input. Please select a valid payment method." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (paymentMethodChoice < 1 || paymentMethodChoice > 4);

    // Process the selected payment method (you can add logic here to handle each method)

    // Update the user's credit
    currentCredit += creditsToAdd;

    // Update user credit in userAccountDetails vector
    std::ostringstream oss;
    oss << usernameFromFile << " " << password << " " << currentCredit << " " << score;
    userAccountDetails[userIndex] = oss.str();

    // Write the updated user account details back to userAccount.txt
    std::ofstream updatedUserAccountFile("userAccount.txt");
    if (updatedUserAccountFile.is_open()) {
        for (const auto& detail : userAccountDetails) {
            updatedUserAccountFile << detail << "\n";
        }
        updatedUserAccountFile.close();
        std::cout << "Credits added successfully. Your new credit balance is: " << currentCredit << " credits ($" << dollarsToAdd << ")." << std::endl;
    } else {
        std::cerr << "Unable to open userAccount.txt for writing." << std::endl;
    }
}

#endif // RENTAL_SYSTEM_H
