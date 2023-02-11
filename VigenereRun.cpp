// Ricardo Romanach

#include <iostream>
#include <string>
#include "VigenereSolver.h"

int main(){
    std::string encryptedText = "";
    while (encryptedText.empty())
    {
        std::cout << "Please enter a ciphertext:\n";
        getline(std::cin, encryptedText);
    }

    VigenereSolver vigenereSolver(encryptedText, 2);
    //If the results seem a little off, try writing the above line as:
    // VigenereSolver vigenereSolver(encryptedText, 2);
    // Increasing the parameter at the end will force the solver to print
    // out more possible solutions. It's likely the correct translation
    // is nearby in the long list. However, remember, the number of results
    // printed will be equal to <parameter> ^ <the period of the key>.

    vigenereSolver.printResults();
}