# RSA-Encryption
Implemented RSA algorithm for encryption (C++).

Orginally done as a class project, it contains 3 main programs and the command 'make all' will compile the entire project. Alternatively, the program may compile according to the directions below.

---keygen---
To compile: make keygen
To run: ./keygen <a prime number> <another prime number> <public key file name> <private key file name>

The keygen program takes two prime numbers and generates RSA keys: a public key and a private key, and writes the two keys into separate files. When running the program, give <a prime number> and <another prime number>, and make sure they are not the same number and they are big enough so their product is at least 256; also you should give  a <public key file name> and  <private key file name>, where the public and private keys will be written into.

---encrypt---
To compile: make encrypt
To run: ./encrypt <public key file name> <plain text file name> <encrypted file name> 

The encrypt program uses the public RSA key to encrypt the plain text from an input file, and writes the encrypted text into an output file. When running the program, give a <public key file name> where the public key is stored, a <plain text file name> where the plain text is read, and an <encrypted file name> where the encrypted text will be written into.


---decrypt---
To compile: make decrypt
To run: ./decrypt <private key file name> <encrypted file name> <decrypted file name> 

The decrypt program uses the private RSA key to decrypt the encrypted text from an input file, and writes the decrypted text into an output file. When running the program, give a <private key file name> where the private key is stored, an <encrypted file name> where the encrypted text is read, and a <decrypted file name> where the decrypted text will be written into.
