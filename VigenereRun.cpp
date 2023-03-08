// Winter Thomas and Ricardo Romanach

#include <iostream>
#include <string>
#include "Vigenere.h"
#include "DataManipulation.h"

int main(){
    int userInput;

    std::cout << "\nWould you like to encrypt or decrypt?\n";
    std::cout << "1. Encrypt\n";
    std::cout << "2. Decrypt\n";
    userInput = DataManipulation::getIntegerInput(1, 2);

    if (userInput == 1){
        std::cout << "\n" << Vigenere::encrypt();
    }
    else {
        Vigenere::solveVigenere(DataManipulation::getUserInput("Please enter the file name:", "Please enter a ciphertext:"));
    }
}