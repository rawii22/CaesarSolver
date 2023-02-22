#include "CaesarSolver.h"
#include "VigenereSolver.h"
#include <string>
#include <cmath>

// Does all steps for decrypting a vigenere cypher automatically
// hasExtraInfo also returns the period and the key in the returned string
std::string VigenereSolver::solveVigenere(std::string encryptedText, bool hasExtraInfo = false){
    // Simplify text for calculating period and keys
    std::string cleanEncryptedText = cleanText(encryptedText);
    // Set a max period to check for
    int maxPeriodChecked = sqrt(cleanEncryptedText.length()) + 1;
    // Calculate the most likely periods
    double* periodList = calculateIdealPeriod(cleanEncryptedText, maxPeriodChecked);
    // Get most likely period
    int period = getHighestValueIndex(periodList, maxPeriodChecked) + 1;
    // Calculate the correlation frequencies for the alphabets
    double** decodedAlphabetFrequencies = calculateKeys(cleanEncryptedText, period);
    // Get most likely key
    int* key = CalculateMostLikelyKey(decodedAlphabetFrequencies, period);
    // Decrypt text
    std::string decryptedText = "";

    if (hasExtraInfo){
        decryptedText += "\nYour period is calculated to be " + std::to_string(period) + "\n\n";
        decryptedText += "Your key is " + convertKeyToString(key, period) + "\n\n";
        decryptedText += "Decrypted Text:\n";
    }

    decryptedText += decodeVigenere(encryptedText, key, period);

    // Delete arrays
    delete[] periodList;
    delete[] key;
    for (int i = 0; i < period; i++){
        delete[] decodedAlphabetFrequencies[i];
    }
    delete[] decodedAlphabetFrequencies;

    return decryptedText;
}

// Prints the result of solveVigenere with extra info
void VigenereSolver::printSolveVigenere(std::string encryptedText){
    std::cout << solveVigenere(encryptedText, true);
}


// Index of Coincidence (IC) Calculator
// This is used to calculate if the period of a key is valid. If this returns a value greater than 0.06,
// then it is more likely that the period of the alphabet is one. If this is true for the majority of
// the alphabets in a Vigenere cipher, then you have most likely selected a valid period length.
double VigenereSolver::ICCalculator(std::string text){
    int* freq = CaesarSolver::getFrequencyOfLetters(text);
    int totalLetters = 0;

    for (int i = 0; i < LANGUAGE_LETTER_COUNT; i++){
        totalLetters += freq[i];
    }

    double total = 0;

    for (int i = 0; i < LANGUAGE_LETTER_COUNT; i++){
        total += freq[i] * (freq[i] - 1);
    }

    total *= 1 / (double) (totalLetters * (totalLetters - 1));

    return total;
}

// Determines the most likely period using Index of Correlation (IC) Values
double* VigenereSolver::calculateIdealPeriod(std::string cleanEncryptedText, int maxPeriodChecked){
    int numberOfAlphabetsSuggestingPeriodOfOne;
    std::string* alphabets;
    double* periodsList = new double[maxPeriodChecked];


    for (int periodBeingChecked = 1; periodBeingChecked <= maxPeriodChecked; periodBeingChecked++){
        alphabets = splitAlphabets(cleanEncryptedText, periodBeingChecked);
        numberOfAlphabetsSuggestingPeriodOfOne = 0;

        // Counts the number of split alphabets that suggests a period of 1
        for (int i = 0; i < periodBeingChecked; i++){
            if (ICCalculator(alphabets[i]) > VALUE_SUGGESTING_PERIOD_OF_ONE){
                numberOfAlphabetsSuggestingPeriodOfOne++;
            }
        }

        delete[] alphabets;
        periodsList[periodBeingChecked - 1] = (double) numberOfAlphabetsSuggestingPeriodOfOne / periodBeingChecked;
    }

    return periodsList;
}

// Returns a 2D array that has for each alphabet (number of alphabets = period)
// an array that contains the corerelation freqeuncy for each possible shift
double** VigenereSolver::calculateKeys(std::string cleanEncryptedText, int period){
    double** decodedAlphabetFrequencies = new double*[period];
    std::string* alphabets = splitAlphabets(cleanEncryptedText, period);

    for (int i = 0; i < period; i++){
        decodedAlphabetFrequencies[i] = CaesarSolver::getCorrelationOfFrequencies(alphabets[i]);
    }

    delete[] alphabets;
    return decodedAlphabetFrequencies;
}

// Returns the most likely key from the information gathered from the alphabet frequencies
int* VigenereSolver::CalculateMostLikelyKey(double** decodedAlphabetFrequencies, int period){
    int* key = new int[period];

    for (int i = 0; i < period; i++){
        key[i] = getHighestValueIndex(decodedAlphabetFrequencies[i], LANGUAGE_LETTER_COUNT);
    }

    return key;
}

// Takes the key as an integer array and returns it as a string of letters
std::string VigenereSolver::convertKeyToString(int* key, int period){
    std::string stringKey = "";

    for (int i = 0; i < period; i++){
        stringKey += CaesarSolver::convertNumberToLetter(key[i]);
    }

    return stringKey;
}

// decrypts the provided string based off the period and key supplied to it
std::string VigenereSolver::decodeVigenere(std::string encryptedText, int* key, int period){
    std::string decryptedText = "";
    int currentAlphabet = 0;

    for (char character : encryptedText){
        // If the character isn't a letter, just save the character and continue
        if (character < 65 || (character > 90 && character < 97) || character > 122){
            decryptedText += character;
            continue;
        }
        // Check if lowercase letter 
        if (character >= 97 && character <= 122){
            character -= key[currentAlphabet];
            // Check for underflow
            if (character < 97){
                character += 26;
            }   
        }
        // Check if uppercase letter
        else {
            character -= key[currentAlphabet];
            // Check for underflow
            if (character < 65){
                character += 26;
            }
        }
        decryptedText += character;

        // Increment which alphabet is currently being used
        currentAlphabet++;
        if (currentAlphabet == period){
            currentAlphabet = 0;
        }
    }

    return decryptedText;
}

// Splits the encrypted text into a number of alphabets equal to the calculated period and returns an array of the alphabets
std::string* VigenereSolver::splitAlphabets(std::string cleanEncryptedText, int period){
    std::string* alphabets = new std::string[period];
    int periodTracker = 0;

    for (int i = 0; i < period; i++){
        alphabets[i] = "";
    }
    for (char i : cleanEncryptedText){
        alphabets[periodTracker] += i;
        periodTracker++;
        //Resets counter if exceed period
        periodTracker %= period;
    }
    return alphabets;
}

// Removes all non letter characters and capitalizes lowercase letters
std::string VigenereSolver::cleanText(std::string rawEncryptedText){
    std::string cleanText = "";

    for (char i : rawEncryptedText){
        if (i != ' '){
            if (i >= 97 && i <= 122){ // Capitalize the lower letters
                cleanText += toupper(i);
            }
            else if (i >= 65 && i <= 90){ // Include capital letters
                cleanText += i;
            }
        }
    }

    return cleanText;
}

// Returns the index of the highest value in an array
int VigenereSolver::getHighestValueIndex(double* listOfValues, int sizeOfList){
    int highestValueIndex = 0;
    double highestValue = listOfValues[0];;

    for (int i = 0; i < sizeOfList; i++){
        if (listOfValues[i] > highestValue){
            highestValue = listOfValues[i];
            highestValueIndex = i;
        }
    }

    return highestValueIndex;    
}