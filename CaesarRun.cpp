// Winter Thomas and Ricardo Romanach

#include <iostream>
#include <string>
#include "CaesarSolver.h"

int main(){
    std::string encryptedText = "";
    while (encryptedText.empty())
    {
        std::cout << "Please enter a ciphertext:\n";
        getline(std::cin, encryptedText);
    }

    CaesarSolver caesarSolver(encryptedText);

    caesarSolver.printResults();
}