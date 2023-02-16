#include "CaesarSolver.h"
#include "VigenereSolver.h"
#include <string>
#include <cmath>

// Index of Coincidence (IC) Calculator
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

// Determines the most likely period using Index of Correlation (IC) Values
void VigenereSolver::calculateIdealPeriod(){
    double originalTextIC = ICCalculator(encryptedText);

    PERIOD = compareICToPeriodTable(originalTextIC);
    bool periodNotCorrect = true;
    int numberOfAlphabetsSuggestingPeriodOfOne;
    bool add = true;
    int addBy = 1;


    while (periodNotCorrect){
        if (alphabets != NULL){ // Make sure to de-allocate memory if alphabets has already been tested!
            delete [] alphabets;
        }

        alphabets = splitAlphabets();
        numberOfAlphabetsSuggestingPeriodOfOne = 0;

        // Counts the number of split alphabets that suggests a period of 1
        for (int i = 0; i < PERIOD; i++){
            if (compareICToPeriodTable(ICCalculator(alphabets[i])) == 1){
                numberOfAlphabetsSuggestingPeriodOfOne++;
            }
        }

        // If at least half of the alphabets suggest a period of 1, exit the loop
        if (numberOfAlphabetsSuggestingPeriodOfOne >= PERIOD/2){
            periodNotCorrect = false;
        }
        else{ // Otherwise periodically go through the adjacent periods and calcualte their values
            if (add){
                PERIOD += addBy;
                add = false;
            }
            else {
                PERIOD -= addBy;
                add = true;
            }
            addBy += 1;
        }
        // If the calculations fail, set period to -1 and exit
        if (PERIOD <= 0){
            PERIOD = -1;
            return;
        }
    }

    std::cout << "Your period was calculated to be " << PERIOD << "\n\n";
}

// Compares the IC value to all the values in the table and returns the period that it most closely correlates with
int VigenereSolver::compareICToPeriodTable(double ICValue){
    int mostLikelyPeriod = 1;
    double mostLikelyIC = ENGLISH_LANGUAGE_IC_VALUES[0];

    for (int i = 0; i < NUMBER_OF_IC_VALUES; i++){
        if (std::abs(ENGLISH_LANGUAGE_IC_VALUES[i] - ICValue) < std::abs(mostLikelyIC - ICValue)){
            mostLikelyPeriod = i + 1;
            mostLikelyIC = ENGLISH_LANGUAGE_IC_VALUES[i];
        }
    }

    return mostLikelyPeriod;
}

// This function finishes attempting to decode the ciphertext using the calculated period.
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

// Splits the encrypted text into a number of alphabets equal to the calculated period and returns an array of the alphabets
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

// Takes a string and returns the string with all spaces removed
std::string VigenereSolver::removeSpaces(std::string textWithSpaces){
    std::string textWithoutSpaces = "";

    for (char i : textWithSpaces){
        if (i != ' '){
            textWithoutSpaces += i;
        }
    }

    return textWithoutSpaces;
}

// Takes an 2D array of alphabets and their specified top most likely solutions along with the size of the encrypted text's letters
// Then weaves them together in all permutations to all possible decryptions with the listed parameters
// TOP_NUM and PERIOD determine the number of results printed. (Number of results = TOP_NUM ^ PERIOD)
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