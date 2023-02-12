#ifndef VIGENERESOLVER_H
#define VIGENERESOLVER_H

#include <iostream>
#include <string>


class VigenereSolver
{
    private:
        std::string encryptedText;
        std::string* alphabets = NULL;
        int PERIOD;         // The likely length of the kew phrase
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
                else if (i == 32 || (i >= 65 && i <= 97)) { // Include spaces and exclude all other characters
                    upperCiphertext += i;
                }
            }
            encryptedText = upperCiphertext;

            promptPeriod();
        }

        ~VigenereSolver()
        {
            delete [] alphabets;
        }

        void promptPeriod();
        void printResults();

        static double ICCalculator(std::string text);
        static std::string removeSpaces(std::string text);

    private:
        std::string* splitAlphabets();
        void weaveAlphabets(std::string** possibleDecodeAlphabets, int encryptedTextLengthWithoutSpaces);
};

#endif