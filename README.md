# Theory-of-Algorithms-Project
Mark Ndipenoch
This document describes the MD5 message-digest algorithm. The algorithm takes as input a
message of arbitrary length and produces as output a "message digest" of the input.
The MD5 algorithm is an extension of the MD4 message-digest algorithm.

#### How to run the porject
1. Clone and download the repository.
2. Cd to the md5.c file directory
3. Compile the code by executing : Compile with: gcc -o md5 -O3 -lm md5.c
4. The run the code by executing: .\md5 "your string here"
5. After that the result will be printed to your console.

![](/run.PNG)

#### Research
I watched and followed the lecturer's video on how to code up SHA56 in C. The final version of the SHA56 is also included in this repository in the file sha-256.c.
Also, I looked up online how different people have done the MD5 message-digest algorithm in C and different langues. Two particular examples caught my attention. I started by following these examples and doing my project like in the examples. So, I can understand better and the different concepts about MD5. I finally ended up doing my project in 3 different ways. The 3rd way was adapted from the two previous ways. All three ways are included in the md5.c file. The first two ways are commented out.
Here are some links are researched on 
- [Encode a string using an MD5 algorithm](https://rosettacode.org/wiki/MD5).
- [Simple MD5 implementation](https://gist.github.com/creationix/4710780).
- [RSA Data Security, Inc. MD5 Message Digest Algorithm](https://people.csail.mit.edu/rivest/Md5.c).
- [Ron Rivest. Request for comments: 1321, the md5 message-digest algorithm](https://tools.ietf.org/html/rfc1321).
- [Rivest, Ronald and Dusse, S The MD5 message-digest algorithm](http://altronic-srl.com.ar/md5%20algoritmo.pdf).

#### How it works.
The algorithm takes as input a message of arbitrary length.

The message is  then "padded" (extended) so that its length (in bits) is congruent to 448, modulo
512. That is, the message is extended so that it is just 64 bits shy of being a multiple of 512
bits long. Padding is always performed, even if the length of the message is already
congruent to 448, modulo 512.
Padding is performed as follows: a single "1" bit is appended to the message, and then "0"
bits are appended so that the length in bits of the padded message becomes congruent to 448,
modulo 512. In all, at least one bit and at most 512 bits are appended.
A 64-bit representation is appended to the result.
At this point the resulting message has a length that is an exact multiple of 512 bits.
Then I iniitialize the MD Buffer to compute the message digest. Here each of a, b, c,
d is a 32-bit register. These registers are initialized to the hexadecimal values.

   a = 0x67452301;
   b = 0xEFCDAB89;
   c = 0x98BADCFE;
   d = 0x10325476;
   
I then define four auxiliary functions that each take as input of 32-bit words and
produce as output one 32-bit word.
 F(X,Y,Z) = XY v not(X) Z
 G(X,Y,Z) = XZ v Y not(Z)
 H(X,Y,Z) = X xor Y xor Z
 I(X,Y,Z) = Y xor (X v not(Z))  
The message is then transform as much aspossible into 4 rounds of 16 each.

The final output is then printed as an hexadecimal.
