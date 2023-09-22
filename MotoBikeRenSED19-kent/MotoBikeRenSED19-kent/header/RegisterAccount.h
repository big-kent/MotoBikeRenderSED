#ifndef REGISTERACCOUNT_H
#define REGISTERACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

class RegisterAccount
{
public:
    enum class PaymentMethod
    {
        CASH,
        CREDIT_CARD,
        BANK_CHECK,
        INTERNET_BANKING
    };

    static bool registerUser(const std::string &username, const std::string &password, const std::string &confirmPassword, PaymentMethod paymentMethod,
                             const std::string &fullName, const std::string &phone, const std::string &idType,
                             const std::string &idNumber, const std::string &licenseNumber, const std::string &expiryDate, const std::string &City);

    static PaymentMethod selectPaymentMethod();

private:
    static bool isUsernameInFile(const std::string &username, const std::string &filename);

    // Simulated payment processing functions
    static bool processPayment(PaymentMethod paymentMethod);
};

#endif // REGISTERACCOUNT_H
