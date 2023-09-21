// ProductDetails.h

#ifndef PRODUCTDETAILS_H
#define PRODUCTDETAILS_H

#include <iostream>
#include <fstream>
#include <string>

class ProductDetails {
public:
    static void displayProductDetails() {
        std::ifstream productFile("ProductDetail.txt");
        std::string line;

        if (productFile.is_open()) {
            while (std::getline(productFile, line)) {
                // Check if the line contains any of the excluded keywords
                if (line.find("Score:") == std::string::npos &&
                    line.find("Latest comment:") == std::string::npos &&
                    line.find("Rating time:") == std::string::npos) {
                    std::cout << line << std::endl;
                }
            }

            productFile.close();
        } else {
            std::cout << "Failed to open product details file." << std::endl;
        }
    }
};


#endif // PRODUCTDETAILS_H
