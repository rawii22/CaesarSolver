# CaesarTools

This repo holds a few tools for using Caesar Ciphers and Vigenère Ciphers.

## How to build the code

Run `make` in the main directory in order to create the command line programs. You can then use the `caesar` and `vigenere` commands.

## Including the code

In order to use these two tools in a program, take a look at the code and the comments in order to gain a better understanding of how it works. You should be able to copy the code over to any project you want and then include the h files as needed.

## Caesar

The caesar solver operates based on a statistical attack. It matches the frequency of the letters in the ciphertext with the frequency of letters in the English alphabet. Then, it shifts the ciphertext according to the most likely shifts. (It can show multiple shifts because the correct shift value might not be the first one)

The run provided has the number of shifts set to 5, but that can be edited to the user's needs. This value has to be between 1 and 26 inclusive.

If you are using this class in your project and you want to get a string value, the function getMostLikelyDecryption returns just the decrypted string after the attack, although be aware that the decoded text might not have been shifted with the correct shift value.

If you already know the shift of the encrypted text, you can use the decrypt function to pass in the text and the shift and it'll return the string of that text unshifted.

The encrypt function does the exact same thing as the decrypt function, but it shifts the text by the given amount instead. If you call the encrypt function without passing any values to it, it prompts the user for the text to shift and the shift amount and then encrypts it.

## Vigenere

For solving vigenere ciphers, the key must be significantly shorter than the message. If the key phrase is as long as the message, then that is an entirely different cipher that cannot be solved with this vigenere tool. We cannot correlate letter frequencies with ciphertext samples of length 1!

Conversely, the vigenere solver is not optimized to solve regular caesar shifts. It may return an incorrect result if you enter a ciphertext with a period of 1. However, you should be able to manually specify a key to get a better result.

As a small note, the vigenere solver is more likely to output a correct result if there is a larger amount of ciphertext to work with. If the ciphertext is too short, it may attempt to split the ciphertext into multiple short alphabets, and these short alphabets are not long enough to accurately run in a statistical attack.

There are 5 functions that are most likely to be used by the user.

solveVigenere is the most versatile function. When given an encrypted text, it solves it for the most likely decryption and then gives the user options of ways to modify the decryption if it is wrong. The user can ask it to change to its next most likely calculated period, or set the period to what the user wants. They can do the same for the shift (or key) of a single alphabet. They can set the key to a value of their choice if they know the key. And they can have the current result stored into a file.

solveMostLikelyVigenere returns the most likely decryption of the text. (This is the same value the solveVigenere function starts with). If you set hasExtraInfo to true, it also returns the period and key at the top of the string. printMostLikelyVigenere prints solveMostLikelyVigenere with its extra info to the console

The encrypt function takes encrypted text and a key and then encrypts the text with that key. If you call the encrypt function without passing any values to it, it prompts the user for the text to encrypt and the key and then encrypts it.

## DataManipulation

This class is used for getting information from the user and making sure it is the user the program needs, and for reading and writing from files.

readStringFromFile reads a file and returns it as a string. It converts newlines into spaces.

writeStringToFile writes a string to the given file.

getUserInput first prompts if the user wants to provide information from a file or to be manually entered. Based off what they select, the corresponding message passed to the function will be shown to the user before prompting them for either the file name or a manually entered string.

getIntegerInput prompts the user for an integer and only accepts values between what is passed to it inclusively.

getLetterInput prompts the user and will only accept a letter. It will return the capitalized version of that letter.



## Links

[CaesarTools - GitHub Repo](https://github.com/rawii22/CaesarTools)

## Contributors

[rawii22](https://github.com/rawii22)

[MiniMage7](https://github.com/MiniMage7)