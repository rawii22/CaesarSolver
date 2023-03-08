// Winter Thomas and Ricardo Romanach

#include <iostream>
#include <string>
#include "Caesar.h"
#include "DataManipulation.h"

int main(){
    int userInput;

    std::cout << "\nWould you like to encrypt or decrypt?\n";
    std::cout << "1. Encrypt\n";
    std::cout << "2. Decrypt\n";
    userInput = DataManipulation::getIntegerInput(1, 2);
    
    if (userInput == 1){
        std::cout << Caesar::encrypt();
    }
    else {
        std::string encryptedText = "";
        while (encryptedText.empty()) {
            std::cout << "Please enter a ciphertext:\n";
            getline(std::cin, encryptedText);
        }
        Caesar caesarSolver(encryptedText);
        caesarSolver.printResults();
    }
}