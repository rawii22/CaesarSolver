// Ricardo Romanach

#include <iostream>
#include <string>
#include "VigenereSolver.h"

int main(){
    std::string encryptedText;
    while (encryptedText.empty())
    {
        std::cout << "\nPlease enter a ciphertext:\n";
        getline(std::cin, encryptedText);
    }

    VigenereSolver::printSolveVigenere(encryptedText);
}