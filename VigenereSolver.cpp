// Winter Thomas and Ricardo Romanach

#include "CaesarSolver.h"
#include "VigenereSolver.h"
#include "DataManipulation.h"
#include <iomanip>
#include <string>
#include <cmath>

/////////////////////////
// Main User Functions //
/////////////////////////

// Solves the vigenere cipher and allows for the user to edit the solution
void VigenereSolver::solveVigenere(std::string encryptedText){
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
    int* key = calculateMostLikelyKey(decodedAlphabetFrequencies, period);
    // Decrypt text
    std::string decryptedText;

    decryptedText = decodeVigenere(encryptedText, key, period);
    int integerInput = 0;

    while (integerInput != 7){
        std::cout << "\nPeriod:\t" << period;
        std::cout << "\nKey:\t" << convertKeyToString(key, period);
        std::cout << "\nText:\t" << decryptedText;

        std::cout << "\n\n1. Change to next most likely period";
        std::cout << "\n2. Set period";
        std::cout << "\n3. Change to next most likely alphabet";
        std::cout << "\n4. Set an alphabet";
        std::cout << "\n5. Set the key";
        std::cout << "\n6. Output to a file";
        std::cout << "\n7. Quit\n";

        integerInput = DataManipulation::getIntegerInput(1, 7);
        // Both of these variables are used rarely in the switch case
        int tempInput;
        std::string tempString;

        switch (integerInput){
            case 1:
                // Remove the current period from the list of most likely periods
                if (period <= maxPeriodChecked){
                    periodList[period - 1] = -1;
                }

                // Get the new period
                period = getHighestValueIndex(periodList, maxPeriodChecked) + 1;

                // Recalculate all values that change from a new period
                decodedAlphabetFrequencies = calculateKeys(cleanEncryptedText, period);
                key = calculateMostLikelyKey(decodedAlphabetFrequencies, period);
                decryptedText = decodeVigenere(encryptedText, key, period);
                break;

            case 2:
                // Remove the current period from the list of most likely periods
                if (period <= maxPeriodChecked){
                    periodList[period - 1] = -1;
                }

                // Get the new period
                std::cout << "\nPlease enter a period";
                std::cout << "\nMax value is " << cleanEncryptedText.length() / 2 << "\n";
                period = DataManipulation::getIntegerInput(1, cleanEncryptedText.length() / 2);

                // Recalculate all values that change from a new period
                decodedAlphabetFrequencies = calculateKeys(cleanEncryptedText, period);
                key = calculateMostLikelyKey(decodedAlphabetFrequencies, period);
                decryptedText = decodeVigenere(encryptedText, key, period);
                break;

            case 3:
                std::cout << "\n";
                printLettersInBox(convertKeyToString(key, period));
                std::cout << "\n" << combineTextWithKey(decryptedText, convertKeyToString(key, period));

                // Get which alphabet to change
                std::cout << "Input which alphabet to change:\n";
                tempInput = DataManipulation::getIntegerInput(0, period);

                // Remove the old alphabet's key from the list of most likely keys
                decodedAlphabetFrequencies[tempInput][key[tempInput]] = -1;

                // Get the new most likely key
                key[tempInput] = getHighestValueIndex(decodedAlphabetFrequencies[tempInput], LANGUAGE_LETTER_COUNT);

                // Decrypt the text with they new key
                decryptedText = decodeVigenere(encryptedText, key, period);
                break;

            case 4:
                std::cout << "\n";
                printLettersInBox(convertKeyToString(key, period));
                std::cout << "\n" << combineTextWithKey(decryptedText, convertKeyToString(key, period));

                // Get which alphabet to change
                std::cout << "Input which alphabet to change:\n";
                tempInput = DataManipulation::getIntegerInput(0, period);

                // Remove the old alphabet's key from the list of most likely keys
                decodedAlphabetFrequencies[tempInput][key[tempInput]] = -1;

                // Get the new key
                std::cout << "\nChange the key for the alphabet to:\n";
                key[tempInput] = CaesarSolver::convertLetterToNumber(DataManipulation::getLetterInput());

                // Decrypt the text with they new key
                decryptedText = decodeVigenere(encryptedText, key, period);
                break;

            case 5:
                // Get the new key
                tempString = getKeyUserInput(cleanEncryptedText.length() / 2);
                key = convertStringToKey(tempString);

                // Recalculate everything to account for the new key
                for (int i = 0; i < period; i++){
                    delete[] decodedAlphabetFrequencies[i];
                }
                delete[] decodedAlphabetFrequencies;
                period = tempString.length();
                decodedAlphabetFrequencies = calculateKeys(cleanEncryptedText, period);
                decryptedText = decodeVigenere(encryptedText, key, period);
                break;

            case 6:
                std::cout << "\nWhat file would you like to output to?\n> ";
                getline(std::cin, tempString);
                DataManipulation::writeStringToFile(tempString, "Period: " + std::to_string(period) + "\nKey: " + convertKeyToString(key, period) + "\nDecrypted Text:\n" + decryptedText);
                break;
        }
    }

    // Delete arrays
    delete[] periodList;
    delete[] key;
    for (int i = 0; i < period; i++){
        delete[] decodedAlphabetFrequencies[i];
    }
    delete[] decodedAlphabetFrequencies;
}

// Does all steps for decrypting a vigenere cypher automatically
// hasExtraInfo also returns the period and the key in the returned string
std::string VigenereSolver::solveMostLikelyVigenere(std::string encryptedText, bool hasExtraInfo){
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
    int* key = calculateMostLikelyKey(decodedAlphabetFrequencies, period);
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
void VigenereSolver::printMostLikelyVigenere(std::string encryptedText){
    std::cout << solveMostLikelyVigenere(encryptedText, true);
}

///////////////////////////////
// Core Decryption Functions //
///////////////////////////////

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
int* VigenereSolver::calculateMostLikelyKey(double** decodedAlphabetFrequencies, int period){
    int* key = new int[period];

    for (int i = 0; i < period; i++){
        key[i] = getHighestValueIndex(decodedAlphabetFrequencies[i], LANGUAGE_LETTER_COUNT);
    }

    return key;
}

// decrypts the provided string based off the period and key supplied to it
std::string VigenereSolver::decodeVigenere(std::string encryptedText, int* key, int period){
    std::string decryptedText = "";
    int currentAlphabet = 0;

    for (char character : encryptedText){
        // If the character isn't a letter, just save the character and continue
        if (!isalpha(character)){
            decryptedText += character;
            continue;
        }
        // Check if lowercase letter 
        if (islower(character)){
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

//////////////////////
// Helper Functions //
//////////////////////

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

// Given a specified string and some internal settings, this function will print the individual letters of
// that string inside a box with its index on top of it.
void VigenereSolver::printLettersInBox(std::string text) {
    // Character per line is set to 19 unless its shorter than the length of the text, at which its set to the text's length
    const int CHARACTERS_PER_ROW = text.length() > 19 ? 19 : text.length();
    const int SPACING = 5;
    const int BOX_WIDTH = CHARACTERS_PER_ROW * SPACING + 2;
    int textLength = text.size();

    //Assuming each row of letters has CHARACTERS_PER_ROW characters with two spaces on each side
    int rows = ceil((float)textLength / CHARACTERS_PER_ROW);

    std::cout << std::setfill('-') << std::setw(BOX_WIDTH + SPACING - 1) << '-' << "\n";
    int charactersPrinted = 0;
    int numbersPrinted = 0;

    for (int i = 0; i < rows; i++){
        std::cout << std::setfill(' ') << "|" << std::setw(BOX_WIDTH + SPACING - 2) << "|" << "\n";

        std::cout << "|";
        for (int j = 0; j < CHARACTERS_PER_ROW; j++){
            int current = j + (CHARACTERS_PER_ROW * i);
            if (current < textLength){
                std::cout << std::setw(SPACING) << current;
                numbersPrinted++;
            }
        }
        // This line takes care of the last "|" to be printed for each row. If a row is full, this should only add SPACING
        // number of spaces. If the last line is not full, then it will figure out how many spaces need to go before the "|".
        std::cout << std::setw(((CHARACTERS_PER_ROW - (numbersPrinted % CHARACTERS_PER_ROW)) % CHARACTERS_PER_ROW) * SPACING + SPACING) << "|" << "\n";
        
        std::cout << "|";
        for (int j = 0; j < CHARACTERS_PER_ROW; j++){
            if (charactersPrinted < textLength){
                std::cout << std::setw(SPACING) << text.at(j + (CHARACTERS_PER_ROW * i));
                charactersPrinted++;
            }
        }
        std::cout << std::setw(((CHARACTERS_PER_ROW - (charactersPrinted % CHARACTERS_PER_ROW)) % CHARACTERS_PER_ROW) * SPACING + SPACING) << "|" << "\n";
    }
    
    std::cout << "|" << std::setw(BOX_WIDTH + SPACING - 2) << "|" << "\n";
    std::cout << std::setfill('-') << std::setw(BOX_WIDTH + SPACING - 1) << '-' << "\n";
}

// Takes the decrypted text and its key and puts them together so that it is visible
// which part of the key goes to which part of the text
std::string VigenereSolver::combineTextWithKey(std::string text, std::string key){
    const int CHARACTERS_PER_ROW = 101;
    int totalRows = ceil((double) text.length() / CHARACTERS_PER_ROW);
    int lastCharacterColumn = text.length() % CHARACTERS_PER_ROW;
    std::string finalText = "";
    std::string textPart;
    bool isLetter[CHARACTERS_PER_ROW];
    char character;
    int keyLength = key.length();
    int keyPos = 0;

    // For each row of text that will be in the output
    for (int currentRow = 0; currentRow < totalRows; currentRow++){
        textPart = "";

        // For each column in that row
        for (int currentColumn = 0; currentColumn < CHARACTERS_PER_ROW; currentColumn++){
            // Get the character at that spot
            character = text[currentRow * CHARACTERS_PER_ROW + currentColumn];
            // save if its a letter or not
            isLetter[currentColumn] = isalpha(character);
            // And add the character to the text part
            textPart += character;

            // If last character stop
            if (lastCharacterColumn == currentColumn && currentRow + 1 == totalRows){
                break;
            }
        }

        // For each column in the row
        for (int currentColumn = 0; currentColumn < CHARACTERS_PER_ROW; currentColumn++){
            // If that column is corresponding to a letter
            if (isLetter[currentColumn]){
                // Add the key part to the text
                finalText += key[keyPos];
                keyPos++;
                if (keyPos == keyLength){
                    keyPos = 0;
                }
            }
            // Otherwise put a space
            else {
                finalText += " ";
            }

            // If last character stop
            if (lastCharacterColumn == currentColumn && currentRow + 1 == totalRows){
                break;
            }
        }
        // Add the text part to the end of the key part with new lines so that it looks like
        // each key part lines up with its text part
        finalText += "\n" + textPart + "\n\n";
    }

    return finalText;
}

// Asks the user for a key, validates it, and converts it to a string of all capital letters
std::string VigenereSolver::getKeyUserInput(int maxKeyLength){
    std::string userInput;
    bool hasBadInput;

    while (true){
        std::cout << "\nPlease enter a key:\n> ";
        getline(std::cin, userInput);

        // Make sure the key is an appropriate length
        if ((int) userInput.length() > maxKeyLength){
            std::cout << "\nMax key length is " << maxKeyLength << "\n";
            continue;
        }

        // Make sure the user input something
        if (userInput.empty()){
            std::cout << "\n";
            continue;
        }

        hasBadInput = false;

        // Convert key to a string while validating it is only letters
        for (int i = 0; i < (int) userInput.length(); i++){
            // If lowercase letter
            if (islower(userInput[i])){
                userInput[i] = toupper(userInput[i]);
                continue;
            }
            // If uppercase letter
            if (isupper(userInput[i])){
                continue;
            }

            // If not a letter
            hasBadInput = true;
            std::cout << "\nThe key can only have letters in it.\n";
            break;
        }

        // If the key is complete
        if (!hasBadInput){
            return userInput;
        }
        // Otherwise ask for a new key
    }
}

// Takes the key as an integer array and returns it as a string of letters
std::string VigenereSolver::convertKeyToString(int* key, int period){
    std::string stringKey = "";

    for (int i = 0; i < period; i++){
        stringKey += CaesarSolver::convertNumberToLetter(key[i]);
    }

    return stringKey;
}

// converts a key from a string to an integer array
int* VigenereSolver::convertStringToKey(std::string stringKey){
    int keyLength = stringKey.length();
    int* key = new int[keyLength];

    for (int i = 0; i < keyLength; i++){
        key[i] = CaesarSolver::convertLetterToNumber(stringKey[i]);
    }

    return key;
}