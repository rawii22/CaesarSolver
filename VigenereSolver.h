#ifndef VIGENERESOLVER_H
#define VIGENERESOLVER_H

#include <iostream>
#include <string>

const double VALUE_SUGGESTING_PERIOD_OF_ONE = 0.0590655;
// TODO: move LANGUAGE_LETTER_COUNT to ceaserSolver and remove magic numbers representing the number of letters
const int LANGUAGE_LETTER_COUNT = 26;

class VigenereSolver
{
    private:
        VigenereSolver(){}
        ~VigenereSolver(){}

    public:
        static double ICCalculator(std::string text);
        static double* calculateIdealPeriod(std::string cleanEncryptedText, int maxPeriodChecked);
        static std::string* splitAlphabets(std::string cleanEncryptedText, int period);
        static std::string cleanText(std::string rawEncryptedText);
        static int getHighestValueIndex(double* listOfValues, int sizeOfList);
        static double** calculateKeys(std::string cleanEncryptedText, int period);
        static int* CalculateMostLikelyKey(double** decodedAlphabetFrequencies, int period);
        static std::string convertKeyToString(int* key, int period);
        static std::string decodeVigenere(std::string encryptedText, int* key, int period);
        static std::string solveVigenere(std::string encryptedText, bool hasExtraInfo);
        static void printSolveVigenere(std::string encryptedText);
};

#endif