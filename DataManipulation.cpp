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
            std::cout << "\nFile is empty";
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
        std::cout << "\nFile" << fileName << "failed to open\n";
    }
}

// Asks if a user wants input from a file or from manual input
// then prompts for file name and reads returns its contents
// or prompts user for input and returns that
std::string DataManipulation::getUserInput(std::string fileCustomMessage, std::string manualCustomMessage){
    std::string userInput = "";

    std::cout << "\nPlease make a selection\n";
    std::cout << "1. Get input from file\n";
    std::cout << "2. Get input from user\n";

    // Reading from a file
    if (getIntegerInput(1,2) == 1){
        while (userInput.empty()){
            std::cout << "\n" << fileCustomMessage << "\n> ";
            getline(std::cin, userInput);
            userInput = readStringFromFile(userInput);
        }
    }
    // Manual user input
    else {
        while (userInput.empty()){
            std::cout << "\n" << manualCustomMessage << "\n> ";
            getline(std::cin, userInput);
        }
    }
        
    return userInput;
}

// Takes a user input and returns the string as an input
// Range values are inclusive.
int DataManipulation::getIntegerInput(int lowRange, int highRange){
    std::string userInput;
    int integerInput;

    while (true){
        std::cout << "> ";
        getline(std::cin, userInput);

        // Check that the user typed something
        if (userInput.empty()){
            std::cout << "\nPlease enter a valid option.\n";
            continue;
        }

        // Convert the first character to an integer
        try {
            integerInput = std::stoi(userInput);
        }
        catch (const std::exception& e){
            std::cout << "\nPlease enter a valid input.\n";
            continue;
        }

        // Check to make sure the input is in range
        if (!(lowRange <= integerInput && integerInput <= highRange)){
            std::cout << "\nPlease enter a valid input\n";
            continue;
        }

        return integerInput;
    }
}

// Takes the first character of a user input and if its a letter
// Returns it as a capital letter
char DataManipulation::getLetterInput(){
    std::string userInput;
    char charInput;

    while (true){
        std::cout << "> ";
        getline(std::cin, userInput);

        // Check that the user typed something
        if (userInput.empty()){
            std::cout << "\nPlease enter a valid option.\n";
            continue;
        }

        // Make sure its only a single character
        if (userInput.length() > 1){
            std::cout << "\nPlease only enter a single letter.\n";
            continue;
        }

        // Grabs the character
        charInput = userInput[0];

        // Check if the character is a lowercase letter
        if (islower(charInput)){
            return toupper(charInput);
        }
        // Check if the character is a capital letter
        else if (isupper(charInput)){
            return charInput;
        }
        // If not a letter
        std::cout << "\nPlease enter a valid option.\n";
    }
}