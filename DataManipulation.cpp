// Winter Thomas and Ricardo Romanach

#include <iostream>
#include <string>
#include <fstream>
#include "DataManipulation.h"

// Reads all information from a file and puts it into a string
std::string DataManipulation::readStringFromFile(std::string fileName){
    std::ifstream inputFile;
    std::string fileText = "";
    inputFile.open(fileName);
    std::string currentLine;

    if (inputFile.is_open()){
        // Check if file is empty
        if (inputFile.eof()){
            std::cout << "File is empty";
            return "";
        }

        while (std::getline (inputFile, currentLine)){
            fileText += currentLine + " ";
        }
        inputFile.close();
        // Take off ending space that is added
        fileText = fileText.substr(0, fileText.length() - 1);
    }
    else {
        std::cout << "\nFile " << fileName << " failed to open";
        return "";
    }

    return fileText;
}

// Takes a string and puts it into a file
void DataManipulation::writeStringToFile(std::string fileName, std::string stringToWrite){
    std::ofstream outputFile;
    outputFile.open(fileName);
    if (outputFile.is_open()){
        outputFile << stringToWrite;
        outputFile.close();
    }
    else {
        std::cout << "\nFile" << fileName << "failed to open";
    }
}

// Asks if a user wants input from a file or from manual input
// then prompts for file name and reads returns its contents
// or prompts user for input and returns that
std::string DataManipulation::getUserInput(std::string fileCustomMessage, std::string manualCustomMessage){
    std::string userInput;

    while (userInput != "1" && userInput != "2"){
        std::cout << "\nPlease make a selection\n";
        std::cout << "1. Get input from file\n";
        std::cout << "2. Get input from user\n";
        getline(std::cin, userInput);
    }

    // Reading from a file
    if (userInput == "1"){
        userInput = "";
        while (userInput.empty()){
            std::cout << "\n\n" << fileCustomMessage << "\n";
            getline(std::cin, userInput);
            userInput = readStringFromFile(userInput);
        }
    }
    
    // Manual user input
    else {
        userInput = "";
        while (userInput.empty()){
            std::cout << "\n\n" << manualCustomMessage << "\n";
            getline(std::cin, userInput);
        }
    }
        
    return userInput;
}