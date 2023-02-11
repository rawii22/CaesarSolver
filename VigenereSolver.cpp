#include "CaesarSolver.h"
#include "VigenereSolver.h"
#include <string>
#include <regex>
#include <cmath>

// Index of Coincidence calculator
// This is used to calculate if the period of a key is valid. If this returns a value greater than 0.06,
// then it is more likely that the period of the alphabet is one. If this is true for the majority of
// the alphabets in a Vigenere cipher, then you have most likely selected a valid period length.
double VigenereSolver::ICCalculator(std::string text){
    int* freq = CaesarSolver::getFrequencyOfLetters(text);
    int totalLetters = 0;
    for (int i = 0; i < 26; i++)
    {
        totalLetters += freq[i];
    }

    double total = 0;

    for (int i = 0; i < 26; i++){
        total += freq[i] * (freq[i] - 1);
    }

    total *= 1 / (double) (totalLetters * (totalLetters - 1));

    return total;
}

void VigenereSolver::promptPeriod()
{
    int periodIn;
    bool satisfied = false;
    std::string buffer;
    std::regex onlyInt("^[0-9]*$");

    while(!satisfied)
    {
        periodIn = 0;

        while (periodIn < 1)
        {
            std::cout << "\nPlease enter the period (length) of the key phrase:\n";
            getline(std::cin, buffer);
            if (!buffer.empty() && std::regex_match(buffer, onlyInt)) // Obsessive fool-proofing user input before conversion to int.
            {
                periodIn = std::stoi(buffer);
            }
        }

        std::cout << "\nTesting ciphertext with period " << periodIn << ":\n\n";
        PERIOD = periodIn;
        if (alphabets != NULL) // Make sure to de-allocate memory if alphabets has already been tested!
            delete [] alphabets;

        alphabets = splitAlphabets();
        
        // Display all IC values for each alphabet before continuing with decoding
        for (int i = 0; i < periodIn; i++){
            std::cout << alphabets[i] << "\t\tIC: " << VigenereSolver::ICCalculator(alphabets[i]);
            std::cout << "\n";
        }
        std::cout << "\nAn IC above or near 0.06 for most rows indicates a good period.\n\n";
        std::cout << "Would you like to continue decoding the ciphertext with period " << periodIn << "? (y/n)\n";
        bool valid = false;
        while(!valid)
        {
            getline(std::cin, buffer);
            if (buffer.compare("y") == 0)
            {
                valid = true;
                satisfied = true;
            }
            else if (buffer.compare("n") == 0)
            {
                valid = true;
            }
            else
            {
                std::cout << "Please enter a valid answer (y/n):\n";
            }
        }
    }
}

void VigenereSolver::printResults()
{
    std::string** possibleDecodedAlphabets = new std::string*[PERIOD];
    for (int i = 0; i < PERIOD; i++)
    {
        possibleDecodedAlphabets[i] = new std::string[TOP_NUM];
    }

    // For each alphabet, translate all of them using their most favorable shift values.
    std::cout << "\nMost likely key:\n";
    for (int i = 0; i < PERIOD; i++){
        double* correlationFrequencies = CaesarSolver::getCorrelationOfFrequencies(alphabets[i]);
        int* topFive = CaesarSolver::getTopShifts(correlationFrequencies, TOP_NUM);

        for (int j = 0; j < TOP_NUM; j++){
            possibleDecodedAlphabets[i][j] = CaesarSolver::unshift(alphabets[i], topFive[j]);
        }
        std::cout << CaesarSolver::convertNumberToLetter(topFive[0]);

        delete[] correlationFrequencies;
        delete[] topFive;
    }

    std::cout << "\n\n";

    for (int i = 0; i < PERIOD; i++){
        std::cout << possibleDecodedAlphabets[i][0];
        std::cout << "\n";
    }

    std::cout << "\n";

    std::cout << "Most likely plain text:\n";
    weaveAlphabets(possibleDecodedAlphabets, removeSpaces(encryptedText).length());
    
    for (int i = 0; i < PERIOD; i++)
        delete[] possibleDecodedAlphabets[i];
    delete[] possibleDecodedAlphabets;
}

std::string* VigenereSolver::splitAlphabets(){
    std::string cleanedText = removeSpaces(encryptedText);
    std::string* alphabets = new std::string[PERIOD];
    int periodTracker = 0;

    for (int i = 0; i < PERIOD; i++){
        alphabets[i] = "";
    }
    for (char i : cleanedText){
        alphabets[periodTracker] += i;
        periodTracker++;
        //Resets counter if exceed period
        periodTracker %= PERIOD;
    }
    return alphabets;
}

std::string VigenereSolver::removeSpaces(std::string textWithSpaces){
    std::string textWithoutSpaces = "";

    for (char i : textWithSpaces){
        if (i != ' '){
            textWithoutSpaces += i;
        }
    }

    return textWithoutSpaces;
}

// Reconstructs the translated letters according to the period. The higher the top number, the more results will be printed.
// The number of results printed will be equal to <TOP_NUM> ^ <PERIOD>.
void VigenereSolver::weaveAlphabets(std::string** possibleDecodeAlphabets, int encryptedTextLengthWithoutSpaces){
    int numberOfCharactersPrinted = 0;

    for (int i = 0; i < pow(TOP_NUM, PERIOD); i++){ // For each most likely translation for each individual alphabet...
        for (int j = 0; j < encryptedTextLengthWithoutSpaces / PERIOD + 1; j++){ // ...print out a letter...
            for (int k = 0; k < PERIOD; k++){ // ...from each row, and keep cycling through the rows in order to interlace the letters back into their original order.
                std::cout << possibleDecodeAlphabets[k][(i / (int) pow(TOP_NUM, k)) % TOP_NUM][j]; // This chooses which permutation (of all the most likely translations for EACH alphabet) to reconstruct and print out.
                numberOfCharactersPrinted++;
                if (numberOfCharactersPrinted == encryptedTextLengthWithoutSpaces){ // Don't print more letters than exist in the original text.
                    break;
                }
            }
        }
        std::cout << "\n\n";
    }
}