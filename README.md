# CaesarTools

This repo holds a few tools for using Caesar Ciphers and Vigenère Ciphers.

## How to build the code

Run `make` in the main directory in order to create the command line programs. You can then use the `caesar` and `vigenere` commands.

## Including the code

In order to use these two tools in a program, take a look at the code and the comments in order to gain a better understanding of how it works. You should be able to copy the code over to any project you want and then include the h files as needed.

## Caesar

The Caesar solver operates based on a statistical attack. It matches the frequency of the letters in the ciphertext with the frequency of letters in the English alphabet. Then, it shifts the ciphertext according to the top five most likely shifts. (It shows the top five because the correct shift value might not be the first one)

If you are using this class in your project and you want to get a string value, the function getDecodedStringWithTopFrequency should do what you want, although be aware that the decoded text might not have been shifted with the correct shift value.

## Vigenere

For solving Vigenere ciphers, the key must be significantly shorter than the message. If the key phrase is as long as the message, then that is an entirely different cipher that cannot be solved with this vigenere tool. We cannot correlate letter frequencies with ciphertext samples of length 1!

Conversely, the vigenere solver is not optimized to solve regular caesar shifts. It may return an incorrect result if you enter a ciphertext with a period of 1. However, you should be able to manually specify a key to get a better result.

As a small note, the vigenere solver is more likely to output a correct result if there is a larger amount of ciphertext to work with. If the ciphertext is too short, it may attempt to split the ciphertext into multiple short alphabets, and these short alphabets are not long enough to accurately run in a statistical attack.

## Links

[CaesarTools - GitHub Repo](https://github.com/rawii22/CaesarTools)

## Contributors

[rawii22](https://github.com/rawii22)

[MiniMage7](https://github.com/MiniMage7)