// Winter Thomas and Ricardo Romanach

#include <iostream>
#include <string>
#include "VigenereSolver.h"
#include "DataManipulation.h"

int main(){
    std::string encryptedText;

    encryptedText = DataManipulation::getUserInput("Please enter the file name:", "Please enter a ciphertext:");

    VigenereSolver::printSolveVigenere(encryptedText);
}