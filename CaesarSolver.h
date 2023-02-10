// Ricardo Romanach

#ifndef CAESARSOLVER_H
#define CAESARSOLVER_H

#include <string>

//This class accepts a ciphertext and uses a statistical attack to figure out the plaintext.
//It will print out the top five most likely shift values.
class CaesarSolver
{
    private:
        std::string encryptedText;
        double* correlationFrequencies;
        int* topFive;
    
    public:
        CaesarSolver(std::string ciphertext)
        {
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
            correlationFrequencies = getCorrelationOfFrequencies(encryptedText);
            topFive = getTopFive(correlationFrequencies);
        }

        ~CaesarSolver()
        {
            delete [] correlationFrequencies;
            delete [] topFive;
        }

        void printResults();
        std::string unshift(int shift);
        std::string getDecodedStringWithTopFrequency();

    private:
        int* getFrequencyOfLetters(std::string text);
        int convertLetterToNumber(char letter);
        char convertNumberToLetter(int number);
        double* getCorrelationOfFrequencies(std::string text);
        int* getTopFive(double* frequencies);
};

#endif