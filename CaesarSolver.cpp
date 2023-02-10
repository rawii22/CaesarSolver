// Ricardo Romanach
// Caeser Cipher Statistical Attack

#include <iostream>
#include <string>
#include "CaesarSolver.h"

const double ENGLISH_ALPHABET_FREQUENCIES [26] = {0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060, 0.065, 0.005, 0.005, 0.035, 0.030, 0.070, 0.080, 0.020, 0.002, 0.065, 0.060, 0.090, 0.030, 0.010, 0.015, 0.005, 0.020, 0.002};

// Returns an array with the frequency of each character in a given string
int* CaesarSolver::getFrequencyOfLetters(std::string text){
    int* letterFrequency = new int[27]; // Slot 27 is reserved for spaces
    for (int i = 0; i < 27; i++){
        letterFrequency[i] = 0;
    }
    for (char i : text){
        letterFrequency[convertLetterToNumber(i)]++;
    }
    return letterFrequency;
}

// Transforms a letter into its number in the alphabet 0 - 25 (Spaces as 26)
int CaesarSolver::convertLetterToNumber(char letter){
    if (letter == ' '){
        return 26;
    }
    return int(letter) - 65;
}

// Transforms a number 0 - 25 into its letter in the alphabet
char CaesarSolver::convertNumberToLetter(int number){
    return static_cast<char>(number + 65);
}

// Returns an array of frequencies. For each possible Caesar shift, this will calculate how
// closely the letter frequencies match English letter frequencies. (e.g. Index 0 will hold
// how closely the frequencies match for a shift of 0.)
double* CaesarSolver::getCorrelationOfFrequencies(std::string text){
    int* letterFrequencies = getFrequencyOfLetters(text);
    // Gets number of letters in text without spaces
    int numberOfLetters = text.length() - letterFrequencies[26];
    double total;
    double* correlationFrequencies = new double [26];

    for (int i = 0; i < 26; i++){
        total = 0;
        for (int j = 0; j < 26; j++){
            // Calculates the correlation of a letter in the cipher text with its frequency of use in the English language
            total += ((double) letterFrequencies[j] / numberOfLetters) * ENGLISH_ALPHABET_FREQUENCIES[((26 + j - i) % 26)];
        }
        correlationFrequencies[i] = total;
    }

    return correlationFrequencies;
}

// Returns an array of five indices. The indices represent the positions of the five highest values
// in the input array.
int* CaesarSolver::getTopFive(double* frequencies){
    // Make and initialize an array for the top 5 values
    int* topFive = new int[5];
    for (int i = 0; i < 5; i++){
        topFive[i] = -1;
    }

    double max;
    int maxIndex;
    bool isInTopFive;

    // For each value to be in top 5
    for (int i = 0; i < 5; i ++){
        max = 0.0;

        // Check if the value is the largest value in the array
        for (int j = 0; j < 26; j++){
            // If its the largest value
            if(frequencies[j] > max){
                // Check if its already in the top 5
                isInTopFive = false;
                for (int k = 0; k < 5; k++){
                    if (j == topFive[k]){
                        isInTopFive = true;
                    }
                }
                // If its not, set it to the new largest
                if (!isInTopFive){
                    max = frequencies[j];
                    maxIndex = j;
                }        
            }
        }
        // Store the current largest value in the top 5 array
        topFive[i] = maxIndex;
    }

    return topFive;
}

// Prints the top five most likely shift values, the frequency it matched
// with English letter frequency using that shift, and the plaintext
// translation for each shift.
void CaesarSolver::printResults(){
    std::cout << "\nTop Five:\n";
    for (int i = 0; i < 5; i++)
    {
        std::cout << "Shift = " << topFive[i] << "\tFrequency = " << correlationFrequencies[topFive[i]] << "\n";
        // For each letter in the encrypted text, shift and print
        std::cout << unshift(topFive[i]);
        std::cout << "\n\n";
    }
}

std::string CaesarSolver::unshift(int shift)
{
    int storeForShift;
    std::string result = "";
    for (char j : encryptedText){
        // If there is a space, there is no shift needed
        if (j == ' '){
            result += ' ';
            continue;
        }
        // Shift character
        storeForShift = convertLetterToNumber(j);
        storeForShift -= shift;
        // Account for shift overflowing
        if (storeForShift < 0){
            storeForShift += 26;
        }
        result += convertNumberToLetter(storeForShift);
    }
    return result;
}

// Returns unshifted string using the top result from the statistical attack
std::string CaesarSolver::getDecodedStringWithTopFrequency()
{
    return unshift(topFive[0]);
}