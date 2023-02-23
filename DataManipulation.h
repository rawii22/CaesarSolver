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
};


#endif