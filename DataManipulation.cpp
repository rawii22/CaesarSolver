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
        std::getline (inputFile, currentLine);
        fileText += currentLine;
        while (inputFile){
            std::getline (inputFile, currentLine);
            fileText += " " + currentLine;
        }
        inputFile.close();
    }
    else {
        std::cout << "\nFile" << fileName << "failed to open";
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