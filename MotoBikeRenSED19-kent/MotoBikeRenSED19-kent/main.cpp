#include <iostream>
#include "AdminLogin.h"
#include "UserLogin.h"
#include "RegisterAccount.h"
#include "AdminUI.h"
#include "ProductDetails.h"
#include "UserUI.h"
#include "searchEngine.h"
#include <limits> // Include this header for numeric_limits

using namespace std;

int main() {
    int userType;
    string username;
    string password;
    bool returnToMainMenu = false;
    while (true) {
        cout << "EEET2482/COSC2082 ASSIGNMENT" << endl;
        cout << "MOTORBIKE RENTAL APPLICATION" << endl;
        cout << "\nInstructor: Dr. Ling Huo Chong" << endl;
        cout << "Group: Group 19" << endl;
        cout << "s3863969, Lu Minh Khang" << endl;
        cout << "s3927152, Trinh Xuan Khanh" << endl;
        cout << "s3978302, Nguyen Quy Minh Thang" << endl;
        cout << "s3915155, Nguyen Thi Quynh Lam\n" << endl;
        cout << "Use the app as: 1. Guest   2. Member   3. Admin\n" << endl;
        cout << "Enter choice: ";
        
        if (!(cin >> userType)) {
            // Input is not an integer
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
            cout << "Invalid input. Please enter a valid integer choice (1-3).\n" << endl;
            continue; // Skip the rest of the loop iteration and ask for input again
        }

        switch (userType) {
            case 1: // Guest
                while (true) {
                    cout << "\nGuest Menu:" << endl;
                    cout << "1. Register" << endl;
                    cout << "2. View Motorbikes Available" << endl;
                    cout << "3. Search for motorbikes by city name" << endl;
                    cout << "4. Exit" << endl;
                    cout << "Enter choice: ";
                    if (!(cin >> userType)) {
                        // Input is not an integer
                        cin.clear(); // Clear error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
                        cout << "Invalid input. Please enter a valid integer choice (1-4).\n" << endl;
                        continue; // Skip the rest of the loop iteration and ask for input again
                    }

                    switch (userType) {
                        case 1:
                            {
                                cout << "\nYou selected 'Register'. Please enter a new username: ";
                                string newUsername;
                                cin >> newUsername;

                                cout << "Please enter a new password: ";
                                string newPassword;
                                cin >> newPassword;

                                cout << "Please confirm your password: ";
                                string confirmPassword;
                                cin >> confirmPassword;

                                RegisterAccount::PaymentMethod paymentMethod = RegisterAccount::selectPaymentMethod();

                                cout << "Please enter your full name: ";
                                string fullName;
                                cin.ignore(); // Clear the newline left in the buffer
                                getline(cin, fullName);

                                cout << "Please enter your phone number: ";
                                string phone;
                                cin >> phone;

                                cout << "Please enter your ID type (e.g., passport): ";
                                string idType;
                                cin.ignore();
                                getline(cin, idType);

                                cout << "Please enter your ID number: ";
                                string idNumber;
                                cin >> idNumber;

                                cout << "Please enter your driver's license number: ";
                                string licenseNumber;
                                cin >> licenseNumber;

                                cout << "Please enter the expiry date of your driver's license (e.g., 07/12): ";
                                string expiryDate;
                                cin >> expiryDate;

                                cout << "Please enter the city you are live in (e.g, Ho Chi Minh/ Ha Noi):";
                                string City;
                                cin >> City;

                                if (newPassword == confirmPassword) {
                                    if (RegisterAccount::registerUser(newUsername, newPassword, confirmPassword, paymentMethod, fullName, phone, idType, idNumber, licenseNumber, expiryDate, City)) {
                                        cout << "Registration successful. You can now log in as a user." << endl;
                                        cout << "\nLogin successfully. Welcome, our member " << newUsername << "!" << endl;

                                        UserUI::showMenu(newUsername);
                                    } else {
                                        cout << "Registration failed. Please try again." << endl;
                                    }
                                } else {
                                    cout << "Password confirmation does not match. Please try again." << endl;
                                }

                            }
                            break;
                        case 2:
                            // Display product details when choosing option 3
                            cout << "\nViewing available motorbikes:" << endl;
                            ProductDetails::displayProductDetails(); // Call the function using the class
                            break;
                        case 3:
                            SearchEngine::searchMotorbikesByCity();
                            break;
                        case 4:
                            cout << "Returning to the main menu!\n" << endl;
                            returnToMainMenu = true;
                        default:
                            break;
                    }
                    if (returnToMainMenu|| userType == 4 ) {
                        break;
                    }
                }
                break;
            case 2: // Member
                cout << "\nEnter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (UserLogin::isUserLoginValid(username, password)) {
                    cout << "\nLogin successfully. Welcome, our member " << username << "!" << endl;
                    UserUI::showMenu(username);
                    // Add user-specific functionality here
                } else {
                    cout << "Login failed. Please check your username or password." << endl;
                }
                break;
            case 3: // Admin
                cout << "\nEnter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                if (AdminLogin::isAdminLoginValid(username, password)) {
                    cout << "\nLogin to admin successfully. Welcome !!!" << endl;
                    AdminUI::showMenu(); // Show the admin menu
                } else {
                    cout << "Login failed. Please check your username or password." << endl;
                }
                break;
            default:
                cout << "Invalid choice. Please enter a valid option (1/2/3)." << endl;
                break;
        }
    }

    return 0;
}
