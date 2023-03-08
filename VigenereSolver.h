// Winter Thomas and Ricardo Romanach

#ifndef VIGENERESOLVER_H
#define VIGENERESOLVER_H

#include <iostream>
#include <string>

const double VALUE_SUGGESTING_PERIOD_OF_ONE = 0.0590655;

class VigenereSolver
{
    private:
        VigenereSolver(){}
        ~VigenereSolver(){}

    public:
        // Main functions the user will use
        static void solveVigenere(std::string encryptedText);
        static std::string solveMostLikelyVigenere(std::string encryptedText, bool hasExtraInfo = false);
        static void printMostLikelyVigenere(std::string encryptedText);

        // Core functions for decrypting
        static double* calculateIdealPeriod(std::string cleanEncryptedText, int maxPeriodChecked);
        static double** calculateKeys(std::string cleanEncryptedText, int period);
        static int* calculateMostLikelyKey(double** decodedAlphabetFrequencies, int period);
        static std::string decodeVigenere(std::string encryptedText, int* key, int period);

        // Helper functions
        static double ICCalculator(std::string text);
        static std::string* splitAlphabets(std::string cleanEncryptedText, int period);

        static std::string cleanText(std::string rawEncryptedText);
        static int getHighestValueIndex(double* listOfValues, int sizeOfList);
        static void printLettersInBox(std::string text);
        static std::string combineTextWithKey(std::string text, std::string key);

        static std::string getKeyUserInput(int maxKeyLength);
        static std::string convertKeyToString(int* key, int period);
        static int* convertStringToKey(std::string stringKey);
};

#endif