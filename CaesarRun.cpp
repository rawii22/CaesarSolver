// Winter Thomas and Ricardo Romanach

#include <iostream>
#include <string>
#include "Caesar.h"
#include "DataManipulation.h"

int main(){
    int userInput;
    int numberOfResults = 5;

    std::cout << "\nWould you like to encrypt or decrypt?\n";
    std::cout << "1. Encrypt\n";
    std::cout << "2. Decrypt\n";
    userInput = DataManipulation::getIntegerInput(1, 2);
    
    if (userInput == 1){
        std::cout << Caesar::encrypt();
    }
    else {
        Caesar::solveCaesar(DataManipulation::getUserInput("Please enter the file name:", "Please enter a ciphertext:"), numberOfResults);
    }
}