#ifndef VIGENERESOLVER_H
#define VIGENERESOLVER_H

#include <iostream>
#include <string>

// Calculated IC Values for each possible period 1-20
const int NUMBER_OF_IC_VALUES = 20;
const double ENGLISH_LANGUAGE_IC_VALUES [NUMBER_OF_IC_VALUES] = {0.065933, 0.052198, 0.047619, 0.045330, 0.043956, 0.043041, 0.042386, 0.041896, 0.041514, 0.041209, 0.040959, 0.040751, 0.040575, 0.040424, 0.040293, 0.040179, 0.040078, 0.039988, 0.039908, 0.039836};

class VigenereSolver
{
    private:
        std::string encryptedText;
        std::string* alphabets = NULL;
        int PERIOD;         // The likely length of the key phrase
        int TOP_NUM;    // The number of results to use from the Caesar cipher statistical attack.

    public:
        VigenereSolver(std::string ciphertext, int outputFactor = 1)
        {
            TOP_NUM = outputFactor;
            // Validate ciphertext input
            std::string upperCiphertext = "";
            for (int i : ciphertext) {
                if (i >= 97 && i <= 122) { // Capitalize the lower letters
                    upperCiphertext += toupper(i);
                }
                else if (i == 32 || (i >= 65 && i <= 90)) { // Include spaces and exclude all other characters
                    upperCiphertext += i;
                }
            }
            encryptedText = upperCiphertext;

            // Calculate the period of the text
            calculateIdealPeriod();
        }

        ~VigenereSolver()
        {
            delete [] alphabets;
        }

        void printResults();

        static double ICCalculator(std::string text);
        static std::string removeSpaces(std::string text);
        static int compareICToPeriodTable(double ICValue);

    private:
        std::string* splitAlphabets();
        void weaveAlphabets(std::string** possibleDecodeAlphabets, int encryptedTextLengthWithoutSpaces);
        void calculateIdealPeriod();
};

#endif