# CaesarTools

This repo holds a few tools for using Caesar Ciphers and Vigenère Ciphers.

## How to build the code

Run `make` in the main directory in order to create the command line programs. You can then use the `caesar` and `vigenere` commands.

## Including the code

In order to use these two tools in a program, take a look at the code and the comments in order to gain a better understanding of how it works. You should be able to copy the code over to any project you want and then include the h files as needed.

## **Caesar**
------

## How it works

The caesar solver operates based on a statistical attack. It matches the frequency of the letters in the ciphertext with the frequency of letters in the English alphabet. Then, it shifts the ciphertext according to the most likely shifts. (It can show multiple shifts because the correct shift value might not be the first one.)

## How to use

If you are using this class in your project and you want to get a string value, the function `getMostLikelyDecryption` returns just the decrypted string after the attack, although be aware that the decoded text might not have been shifted with the correct shift value.

The provided `main` function for caesar has the number of likely shifts set to 5, but that can be edited to the user's needs. This value has to be between 1 and 26 inclusive.

If you already know the shift of the encrypted text, you can use the `decrypt` function to pass in the text and the shift, and it will return the string of that text unshifted.

The `encrypt` function does the exact same thing as the `decrypt` function, but it shifts the text by the given amount instead. If you call the `encrypt` function without passing any values to it, it prompts the user for the text to shift and the shift amount and then encrypts it.

## **Vigenère**
--------

## Ideal use

For solving vigenere ciphers, the key must be significantly shorter than the message. If the key phrase is a significant portion of the message, then that is an entirely different cipher that cannot be reliably solved with this vigenere tool. We cannot correlate letter frequencies with ciphertext samples of length 1!

Conversely, the vigenere solver is not optimized to solve regular caesar shifts. It may return an incorrect result if you enter a ciphertext with a period of 1. However, you should be able to manually specify a key or period to get a better result.

As a small note, the vigenere solver is more likely to output a correct result if there is a larger amount of ciphertext to work with. If the ciphertext is too short, it may attempt to split the ciphertext into multiple short alphabets, and these short alphabets are not long enough to accurately run in a statistical attack.

## How to use

There are 4 functions that are most likely to be used by the user.

* `solveVigenere` is the most versatile function. When given an encrypted text, it solves it for the most likely decryption and then gives the user options to modify the decryption if it is wrong. The user can then ask it to change to its next most likely calculated period, or set the period to what the user wants. They can do the same for the shift (or key) of a single alphabet. They can set the key to a value of their choice if they know the key. And they can have the current result stored into a file.

* `solveMostLikelyVigenere` returns the most likely decryption of the text. (This is the same value the `solveVigenere` function initially calculates.) If you set the hasExtraInfo parameter to true, it also returns the period and key at the top of the string.

* `printMostLikelyVigenere` prints `solveMostLikelyVigenere` with its extra info to the console.

* The `encrypt` function takes encrypted text and a key and then encrypts the text with that key. If you call the `encrypt` function without passing any values to it, it prompts the user for the text to encrypt and the key and then encrypts it.

## **DataManipulation**
--------

This class is used for getting information from the user, making sure information retrieved is what the program needs, and for file reading and writing.

## How to use

* `readStringFromFile` reads a file and returns it as a string. NOTE: *It converts newlines into spaces.*

* `writeStringToFile` writes a string to a file given the filename and the string.

* `getUserInput` first prompts if the user wants to provide information mnaually or from a file. Based off what they select, the corresponding message passed to the function will be shown to the user before prompting them for either a manually entered string or the file name.

* `getIntegerInput` prompts the user for an integer and only accepts values between a specified range (range is inclusive).

* `getLetterInput` prompts the user for a letter. NOTE: *It will return the capitalized version of that letter.*

# Links

[CaesarTools - GitHub Repo](https://github.com/rawii22/CaesarTools)

# Contributors

[rawii22](https://github.com/rawii22)

[MiniMage7](https://github.com/MiniMage7)