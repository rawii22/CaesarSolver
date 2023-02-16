# CaesarSolver
https://github.com/rawii22/CaesarSolver

This repo holds a few tools for solving basic Caesar Ciphers and Vigenère Ciphers.

Run `make` in the main directory in order to create the command line programs.

You can then use the `caesar` and `vigenere` commands to help you solve Caesar Ciphers and Vigenère Ciphers, respectively.

In order to use these two tools in a program, take a look at the code and the comments in order to gain a better understanding of how it works.

### Vigenere

For solving Vigenere ciphers, the key must be significantly shorter than the message. If the key phrase is as long as the message, then that is an entirely different cipher that cannot be solved with this vigenere tool. We cannot correlate letter frequencies with ciphertext samples of length 1!

Conversely, the vigenere solver is not optimized to solve regular caesar shifts. It may return an incorrect result if you enter a ciphertext with a period of 1.

As a small note, the vigenere solver is more likely to output a correct result if there is a larger amount of ciphertext to work with. If the ciphertext is too short, it may attempt to split the ciphertext into multiple short alphabets, and these short alphabets are not long enough to accurately run in a statistical attack.