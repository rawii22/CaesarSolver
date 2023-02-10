// Ricardo Romanach
// Caeser Cipher Statistical Attack

#include <iostream>
using namespace std;

int* getFrequencyOfLetters(string);
int convertLetterToNumber(char);
char convertNumberToLetter(int);
int getLengthWithoutSpaces(string);
double* getCorrelationOfFrequencies(string);
int* getTopFive(double*);
void decode(string, int);

const double ENGLISH_ALPHABET_FREQUENCIES [26] = {0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060, 0.065, 0.005, 0.005, 0.035, 0.030, 0.070, 0.080, 0.020, 0.002, 0.065, 0.060, 0.090, 0.030, 0.010, 0.015, 0.005, 0.020, 0.002};

int main(){
    string encryptedText = "IT STY XYZRGQJ TAJW XTRJYMNSL GJMNSI DTZ";
    
    double* correlationFrequencies = getCorrelationOfFrequencies(encryptedText);

    int* topFive = getTopFive(correlationFrequencies);

    cout << "\nTop Five:\n";
    for (int i = 0; i < 5; i++){
        cout << "Shift = " << topFive[i] << "\tFrequency = " << correlationFrequencies[topFive[i]] << endl;
        decode(encryptedText, topFive[i]);
    }
}

// Returns an array with the frequency of each character in a given string
int* getFrequencyOfLetters(string text){
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
int convertLetterToNumber(char letter){
    if (letter == ' '){
        return 26;
    }
    return int(letter) - 65;
}

// Transforms a number 0 - 25 into its letter in the alphabet
char convertNumberToLetter(int number){
    return static_cast<char>(number + 65);
}

double* getCorrelationOfFrequencies(string text){
    int* letterFrequencies = getFrequencyOfLetters(text);
    // Gets number of letters in text without spaces
    int numberOfLetters = text.length() - letterFrequencies[26];
    double total;
    double* correlationFrequencies = new double [26];

    // For each possible Caesar shift, this will calculate how closely the letter frequencies match English letter frequencies
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

int* getTopFive(double* frequencies){
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

void decode(string encryptedText, int shift){
    int storeForShift;

    // For each letter in the encrypted text, shift and print
    for (char i : encryptedText){
        // If a space there is no shift needed
        if (i == ' '){
            cout << ' ';
            continue;
        }
        // Shift character
        storeForShift = convertLetterToNumber(i);
        storeForShift -= shift;
        // Account for shift overflowing
        if (storeForShift < 0){
            storeForShift += 26;
        }
        cout << convertNumberToLetter(storeForShift);
    }
    cout << endl << endl;
}