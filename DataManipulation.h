// Winter Thomas and Ricardo Romanach

#ifndef DATAMANIPULATION_H
#define DATAMANIPULATION_H

#include <iostream>
#include <string>

class DataManipulation
{
    private:
        DataManipulation(){}
        ~DataManipulation(){}

    public:
        static std::string readStringFromFile(std::string fileName);
        static void writeStringToFile(std::string fileName, std::string stringToWrite);

        static std::string getUserInput(std::string fileCustomMessage, std::string manualCustomMessage);
        static int getIntegerInput(int lowRange, int highRange);
        static char getLetterInput();
};


#endif