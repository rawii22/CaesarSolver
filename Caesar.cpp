// Winter Thomas and Ricardo Romanach
// Caeser Cipher Statistical Attack

#include <iostream>
#include <string>
#include "Caesar.h"
#include "DataManipulation.h"

// Returns an array with the frequency of each character in a given string
int* Caesar::getFrequencyOfLetters(std::string text){
    int* letterFrequency = new int[LANGUAGE_LETTER_COUNT + 1]; // Slot 27 is reserved for spaces
    for (int i = 0; i < LANGUAGE_LETTER_COUNT + 1; i++){
        letterFrequency[i] = 0;
    }
    for (char i : text){
        letterFrequency[convertLetterToNumber(i)]++;
    }
    return letterFrequency;
}

// Transforms a letter into its number in the alphabet 0 - 25 (Spaces as 26)
int Caesar::convertLetterToNumber(char letter){
    if (letter == ' '){
        return LANGUAGE_LETTER_COUNT;
    }
    return int(letter) - 65;
}

// Transforms a number 0 - 25 into its letter in the alphabet
char Caesar::convertNumberToLetter(int number){
    return static_cast<char>(number + 65);
}

// Returns an array of frequencies. For each possible Caesar shift, this will calculate how
// closely the letter frequencies match English letter frequencies. (e.g. Index 0 will hold
// how closely the frequencies match for a shift of 0.)
double* Caesar::getCorrelationOfFrequencies(std::string text){
    int* letterFrequencies = getFrequencyOfLetters(text);
    // Gets number of letters in text without spaces
    int numberOfLetters = text.length() - letterFrequencies[LANGUAGE_LETTER_COUNT];
    double total;
    double* correlationFrequencies = new double [LANGUAGE_LETTER_COUNT];

    for (int i = 0; i < LANGUAGE_LETTER_COUNT; i++){
        total = 0;
        for (int j = 0; j < LANGUAGE_LETTER_COUNT; j++){
            // Calculates the correlation of a letter in the cipher text with its frequency of use in the English language
            total += ((double) letterFrequencies[j] / numberOfLetters) * ENGLISH_ALPHABET_FREQUENCIES[((LANGUAGE_LETTER_COUNT + j - i) % LANGUAGE_LETTER_COUNT)];
        }
        correlationFrequencies[i] = total;
    }

    return correlationFrequencies;
}

// Returns an array of INDICES. The indices represent the positions of the highest values
// in the input array. The amount of top results to be returned is stored in topAmount.
int* Caesar::getTopShifts(double* frequencies, int topAmount){
    // Make and initialize an array for the top values
    int* topResults = new int[topAmount];
    for (int i = 0; i < topAmount; i++){
        topResults[i] = -1;
    }

    double max;
    int maxIndex;
    bool isInTopList;

    // For each value to be in top list
    for (int i = 0; i < topAmount; i ++){
        max = 0.0;

        // Check if the value is the largest value in the array
        for (int j = 0; j < LANGUAGE_LETTER_COUNT; j++){
            // If its the largest value
            if(frequencies[j] > max){
                // Check if its already in the top list
                isInTopList = false;
                for (int k = 0; k < topAmount; k++){
                    if (j == topResults[k]){
                        isInTopList = true;
                    }
                }
                // If its not, set it to the new largest
                if (!isInTopList){
                    max = frequencies[j];
                    maxIndex = j;
                }        
            }
        }
        // Store the current largest value in the top results array
        topResults[i] = maxIndex;
    }

    return topResults;
}

// Prints the top most likely shift values, the frequency it matched
// with English letter frequency using that shift, and the plaintext
// translation for each shift.
void Caesar::printResults(){
    std::cout << "\nTop " << TOP_NUM << " Shifts:\n";
    for (int i = 0; i < TOP_NUM; i++)
    {
        std::cout << "Shift = " << topShifts[i] << "\tFrequency = " << correlationFrequencies[topShifts[i]] << "\n";
        // For each letter in the encrypted text, shift and print
        std::cout << unshift(encryptedText, topShifts[i]);
        std::cout << "\n\n";
    }
}

std::string Caesar::unshift(std::string ciphertext, int shift)
{
    int storeForShift;
    std::string result = "";
    for (char i : ciphertext){
        // If there is a space, there is no shift needed
        if (i == ' '){
            result += ' ';
            continue;
        }
        // Shift character
        storeForShift = convertLetterToNumber(i);
        storeForShift -= shift;
        // Account for shift overflowing
        if (storeForShift < 0){
            storeForShift += LANGUAGE_LETTER_COUNT;
        }
        result += convertNumberToLetter(storeForShift);
    }
    return result;
}

// Returns unshifted string using the top result from the statistical attack
std::string Caesar::getDecodedStringWithTopFrequency()
{
    return unshift(encryptedText, topShifts[0]);
}

std::string Caesar::encrypt(){
    std::string text;
    int key;

    text = DataManipulation::getUserInput("Please enter the file name:", "Please enter the text to encrypt:");

    std::cout << "\nHow much would you like to shift the text?\n";

    key = DataManipulation::getIntegerInput(0, 25);

    return encrypt(text, key);
}

std::string Caesar::encrypt(std::string text, int shift){
    int storeForShift;
    std::string result = "";
    for (char i : text){
        // If there is a space, there is no shift needed
        if (i == ' '){
            result += ' ';
            continue;
        }
        // Shift character
        storeForShift = convertLetterToNumber(i);
        storeForShift += shift;
        // Account for shift overflowing
        if (storeForShift > 25){
            storeForShift -= LANGUAGE_LETTER_COUNT;
        }
        result += convertNumberToLetter(storeForShift);
    }
    return result;
}

// Removes all non letter characters and capitalizes lowercase letters
std::string Caesar::cleanText(std::string rawEncryptedText){
    std::string cleanText = "";

    for (char i : rawEncryptedText){
        if (i != ' '){
            if (islower(i)){ // Capitalize the lower letters
                cleanText += toupper(i);
            }
            else if (isupper(i)){ // Include capital letters
                cleanText += i;
            }
        }
    }

    return cleanText;
}