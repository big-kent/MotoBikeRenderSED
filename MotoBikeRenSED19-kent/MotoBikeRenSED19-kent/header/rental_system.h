#ifndef RENTAL_SYSTEM_H
#define RENTAL_SYSTEM_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include <map>
#include <cmath>

// Define a struct to represent a motorbike
struct Motorbike
{
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
    int ratingTime;
};

struct RentalRequest
{
    std::string renterUsername;
    int motorbikeID;
    std::string ownerUsername;
    std::string status; // e.g., "pending", "accepted", "rejected"
};

// Define a struct for a return message
struct ReturnMessage
{
    std::string ownerUsername;
    int motorbikeID;
    std::string renterUsername;
};

struct UserAccount
{
    std::string username;
    std::string password;
    int credit;
    int score;
    int ratingTime;
};

// Create a vector to store rental requests
extern std::vector<RentalRequest> rentalRequests;

extern std::vector<std::pair<std::string, std::pair<int, int>>> userAccounts;

// Define a global vector to keep track of rented motorbikes and their respective usernames
extern std::vector<std::pair<std::string, int>> rentedMotorbikes;

// Use a map to associate owners with their return messages
extern std::map<std::string, std::vector<ReturnMessage>> ownerReturnMessages;

// Function to display motorbike data
void displayMotorbikeData(const std::vector<Motorbike> &motorbikes, const std::string &desiredCity, int userScore, int userCredit);

void sendRentalRequest(const std::string &renterUsername, int motorbikeID, const std::string &ownerUsername);

void updateProductStatus(const std::string &motorbikeID, const std::string &newStatus);

// Function to view rental request responses for renters
void viewRenterResponses(const std::string &renterUsername);

// Function to view rental requests and approve or reject them
void viewRentalRequests(const std::string &ownerUsername);

// Function to check if a user has already rented a motorbike
bool hasUserRented(const std::string &username);

// Function to rent a motorbike
void rentMotorbike(const std::string &username);

// Function to check if a motorbike ID already exists
bool motorbikeIdExists(const std::string &motorbikeId);

// Function to rent a motorbike
void applyMotorbikeForRent(const std::string &username);

// Function to add more credit points to a user's account with credit milestones
void addMoreCreditPointsToYourAccount(const std::string &username);

// Function to calculate the updated score for a user and return it as a rounded integer
int calculateUpdatedScore(int currentScore, int ratingTime, double newRating);

void checkReturnMessages(const std::string &ownerUsername);

// Function to update the userAccount.txt file with the new owner's rounded score
void updateOwnerScoreInFile(const std::string &ownerUsername, double newScore);

// Function to update the motorbike's score, rating time, and comment in the ProductDetail.txt file
void updateMotorbikeInfoInFile(int motorbikeID, double renterRating, const std::string &comment);

// Function to send a return message
void sendReturnMessage(const std::string &ownerUsername, int motorbikeID, const std::string &renterUsername);

// Function to return the motorbike to the owner
void returnMotorbike(const std::string &renterUsername);

#endif // RENTAL_SYSTEM_H
