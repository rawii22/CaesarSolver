// Winter Thomas and Ricardo Romanach

#ifndef CAESAR_H
#define CAESAR_H

#include <string>

const int LANGUAGE_LETTER_COUNT = 26;
const double ENGLISH_ALPHABET_FREQUENCIES [LANGUAGE_LETTER_COUNT] = {0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060, 0.065, 0.005, 0.005, 0.035, 0.030, 0.070, 0.080, 0.020, 0.002, 0.065, 0.060, 0.090, 0.030, 0.010, 0.015, 0.005, 0.020, 0.002};

//This class accepts a ciphertext and uses a statistical attack to figure out the plaintext.
class Caesar
{
    private:
        const int TOP_NUM = 5;
        std::string encryptedText;
        double* correlationFrequencies;
        int* topShifts;
    
    public:
        Caesar(std::string ciphertext)
        {
            std::string upperCiphertext = "";
            for (int i : ciphertext) {
                if (islower(i)) { // Capitalize the lower letters
                    upperCiphertext += toupper(i);
                }
                else if (i == 32 || isupper(i)) { // Include spaces and capital letters while excluding all other characters
                    upperCiphertext += i;
                }
            }

            encryptedText = upperCiphertext;
            correlationFrequencies = getCorrelationOfFrequencies(encryptedText);
            topShifts = getTopShifts(correlationFrequencies, TOP_NUM);
        }

        ~Caesar()
        {
            delete [] correlationFrequencies;
            delete [] topShifts;
        }

        void printResults();
        std::string getDecodedStringWithTopFrequency();

        static std::string unshift(std::string ciphertext, int shift);
        static int* getFrequencyOfLetters(std::string text);
        static int convertLetterToNumber(char letter);
        static char convertNumberToLetter(int number);
        static double* getCorrelationOfFrequencies(std::string text);
        static int* getTopShifts(double* frequencies, int topAmount);
        static std::string encrypt();
        static std::string encrypt(std::string text, int shift);
        static std::string cleanText(std::string rawEncryptedText);
};

#endif