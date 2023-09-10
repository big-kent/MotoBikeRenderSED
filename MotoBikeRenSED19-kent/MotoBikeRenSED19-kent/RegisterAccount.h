#ifndef REGISTERACCOUNT_H
#define REGISTERACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

class RegisterAccount {
public:
    enum class PaymentMethod { CASH, CREDIT_CARD, BANK_CHECK, INTERNET_BANKING };

    static bool registerUser(const std::string& username, const std::string& password, const std::string& confirmPassword, PaymentMethod paymentMethod,
                             const std::string& fullName, const std::string& phone, const std::string& idType,
                             const std::string& idNumber, const std::string& licenseNumber, const std::string& expiryDate, const std::string& City) {
        if (password == confirmPassword) {
            // Check if the username already exists in userAccount.txt
            if (isUsernameInFile(username, "userAccount.txt")) {
                std::cout << "\nThis username already exists. Please choose a different username." << std::endl;
                return false; // Registration failed
            }

            // Check if the username already exists in adminAccount.txt
            if (isUsernameInFile(username, "adminAccount.txt")) {
                std::cout << "\nThis username is only for admin. Please choose another username." << std::endl;
                return false; // Registration failed
            }

            std::ofstream userFile("userAccount.txt", std::ios::app); // Open the file in append mode
            std::ofstream userProfileFile("userProfile.txt", std::ios::app); // Open the user profile file in append mode

            if (userFile.is_open() && userProfileFile.is_open()) {
                int initialCredit = 20;

                // Simulate the payment process based on the selected payment method
                bool paymentSuccessful = processPayment(paymentMethod);

                if (paymentSuccessful) {
                    // Write the new username, password, and initial credit points to the userAccount file
                    userFile << username << " " << password << " " << initialCredit << "\n";
                    userFile.close();

                    // Write user profile information to the userProfile file
                    userProfileFile << "\nUsername: " << username << "\n";
                    userProfileFile << "Full Name: " << fullName << "\n";
                    userProfileFile << "Phone: " << phone << "\n";
                    userProfileFile << "ID Type: " << idType << "\n";
                    userProfileFile << "ID Number: " << idNumber << "\n";
                    userProfileFile << "Driver's License Number: " << licenseNumber << "\n";
                    userProfileFile << "Expired Date: " << expiryDate << "\n";
                    userProfileFile << "MotorbikeRentingID: 0\n"; // Assuming an initial value
                    userProfileFile << "City: " << City << "\n";

                    userProfileFile.close();

                    std::cout << "Registration successful. You have " << initialCredit << " credit points." << std::endl;
                    return true; // Registration successful
                } else {
                    std::cout << "Payment failed. Registration canceled." << std::endl;
                }
            }
        }

        return false; // Registration failed
    }

    static PaymentMethod selectPaymentMethod() {
        int choice;
        while (true) {
            std::cout << "You need to deposit for 20 credits for an account" << std::endl;
            std::cout << "Please select a payment method:" << std::endl;
            std::cout << "1. Cash" << std::endl;
            std::cout << "2. Credit Card" << std::endl;
            std::cout << "3. Bank Check" << std::endl;
            std::cout << "4. Internet Banking" << std::endl;
            std::cout << "Enter your choice (1-4): ";
            if (!(std::cin >> choice)) {
                // Input is not an integer
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
                std::cout << "Invalid input. Please enter a valid integer choice (1-4).\n";
                continue; // Ask for input again
            }

            if (choice >= 1 && choice <= 4) {
                break; // Valid input, exit the loop
            } else {
                std::cout << "Invalid choice. Please enter a valid option (1-4).\n";
            }
        }

        switch (choice) {
            case 1:
                return PaymentMethod::CASH;
            case 2:
                return PaymentMethod::CREDIT_CARD;
            case 3:
                return PaymentMethod::BANK_CHECK;
            case 4:
                return PaymentMethod::INTERNET_BANKING;
            default:
                // This should not be reached, but return a default value to handle it
                std::cout << "Invalid choice. Defaulting to Cash payment." << std::endl;
                return PaymentMethod::CASH;
        }
    }

private:
    static bool isUsernameInFile(const std::string& username, const std::string& filename) {
        std::ifstream file(filename);
        std::string existingUsername;

        if (file.is_open()) {
            while (file >> existingUsername) {
                if (username == existingUsername) {
                    file.close();
                    return true; // Username exists in the file
                }
            }
            file.close();
        }

        return false; // Username does not exist in the file
    }

    // Simulated payment processing functions
    static bool processPayment(PaymentMethod paymentMethod) {
        switch (paymentMethod) {
            case PaymentMethod::CASH:
                // Implement cash payment logic (e.g., collect cash)
                std::cout << "Payment by cash accepted." << std::endl;
                return true; // Payment successful
            case PaymentMethod::CREDIT_CARD:
                // Implement credit card payment logic (e.g., validate card details)
                std::cout << "Payment by credit card accepted." << std::endl;
                return true; // Payment successful
            case PaymentMethod::BANK_CHECK:
                // Implement bank check payment logic (e.g., verify check details)
                std::cout << "Payment by bank check accepted." << std::endl;
                return true; // Payment successful
            case PaymentMethod::INTERNET_BANKING:
                // Implement internet banking payment logic (e.g., connect to a bank's API)
                std::cout << "Payment by internet banking accepted." << std::endl;
                return true; // Payment successful
            default:
                std::cout << "Invalid payment method selected." << std::endl;
                return false; // Payment failed
        }
    }
};

#endif // REGISTERACCOUNT_H
