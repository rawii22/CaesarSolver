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
        std::string encryptedText = Vigenere::encrypt();
        std::cout << "\n" << encryptedText;
        
        std::cout << "\n\nWould you like to write the text to a file? Y/[N]\n";
        userInput = DataManipulation::getLetterInput();
        if (userInput == 'Y' || userInput == 'y'){
            std::string fileName;
            std::cout << "\nWhat file would you like to output to?\n> ";
            getline(std::cin, fileName);
            DataManipulation::writeStringToFile(fileName, encryptedText);
        }
    }
    else {
        Vigenere::solveVigenere(DataManipulation::getUserInput("Please enter the file name:", "Please enter a ciphertext:"));
    }
}