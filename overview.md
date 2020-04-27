<p align="center">
  <b>Theory of Algorithms</b><br>
</p>

Student ID: G00352031<br/>
Name: Mark Ndipenoch<br/>

<p align="center">
  <b>Abstract</b><br>
</p>
Due to the rapid advancement of technology, the integrity of documents and security protocols should be preserved.
One of the ways to achieve this is by using a digital signature. 
A digital signature is a specific code which is generated from the function of producing a digital signature. 
One of the algorithms that is used to create the digital signature is a hash function. There are many hash functions.
One of the main hash function is MD5 message-digest algorithm [1,2,3].
In this document we will be talking about MD5 message-digest algorithm.<br/><br/>

<p align="center">
  <b>Introduction</b><br/>
</p>
MD5 was designed by Ronald Rivest in 1991 to replace an earlier hash function MD4,[8].
The MD5 message-digest algorithm, is a widely used hash function that takes as input a message of arbitrary length and produces as output a 128-bit "fingerprint" or "message digest" of the input. 
It is conjectured that it is computationally infeasible to produce two messages having the same message digest, or to produce any message having a given prespecified target message digest. 
The MD5 algorithm is intended for digital signature applications, where a large file must be "compressed" in a secure manner before being encrypted with a private (secret) key under a public-key cryptosystem such as Rivest–Shamir–Adleman(RSA).
<br/><br/>

<p align="center">
  <b>Terminology</b><br/>
</p>

- Bit - A bit has a single binary value, either 0 or 1, eight-bit unit makes one byte.
- Byte -  Byte is a series of bits, eight bits makes one byte.
- In this document a "word" is a 32-bit quantity and a "byte" is an eight-bit quantity. 
A sequence of bits can be interpreted in a natural manner as a sequence of bytes, where each consecutive group of eight bits is interpreted as a byte with the high-order (most significant) bit of each byte listed first.
Similarly, a sequence of bytes can be interpreted as a sequence of 32-bit words, where each consecutive group of four bytes is interpreted as a word with the low-order (least significant) byte given first.
</b><br/>
<p align="center">
  <b>How to Run The Code</b><br/>
</p>
To compile and run the code, do the following steps:</br>
1. Clone and download the code from GitHub. You can do this by copying the URL of the repository. Then go to your chosen folder, then open the terminal and type git clone “paste the url here” and click enter. 
The folder will be downloaded to that directory.</br>
2. Then install the compiler which is GCC, if it is not already install.</br>
•	If you are on a Linux machine</br>
To install gcc you can run the below code on the command line</br>
sudo apt install gcc</br>
But this is not the recommended way. The recommended way is<br>
sudo apt install build-essential</br>
Build-essential is a mega package with a collection of pieces of software including gcc.</br>
To test if GCC is install run</br>
gcc –version</br>
•	If you are on a Windows machine</br>
1. Download and Install Cygwin.</br>
First, download Cygwin from the official website https://www.cygwin.com either the 32- or 64-bit version of the Cygwin installer, depending on your version of Windows and run it. </br>
2. Install the required Cygwin Packages</br>
Cygwin’s setup wizard will walk you through a series of steps.
When running the setup wizard you can choose to install just C compiler from the available packages.</br>
3. Add Gcc to the build path in the environmental variable.
Go to the bin directory(where the .exe is found) in the folder where you install the gcc. 
Copy the path of the bin directory and add the path to the environmental variable on your machine.</br>
4- Test to see if GCC is install</br>
open the command prompt and type  gcc –version</br>
once the compiler is installed navigate to the directory where your .c folder is and run the below commands on the command line.</br>
To Compile run  : gcc -o md5 -O3 -lm md5.c</br>
To run : .\md5 --run  "your string here"</br>
</br>
<p align="center">
  <b>How to Run Test Cases</b><br/>
</p>
To Compile run  : gcc -o md5 -O3 -lm md5.c</br>
To run : .\md5 --test </br>
<p align="center">
  <b>MD5 Algorithm Description</b><br/>
</p>
We begin by supposing that we have a b-bit message as input, and that we wish to find its message digest. 
Here b is an arbitrary nonnegative integer; b   may be zero, it need not be a multiple of eight, and it may be arbitrarily large. 
We imagine the bits of the message written down as follows:</br>

          m_0 m_1 ... m_{b-1}</br>
The following five steps are performed to compute the message digest of the message.</br>

#### 1-	Append Padding Bits
The message is "padded" (extended) so that its length (in bits) is  congruent to 448, modulo 512. That is, the message is extended so that it is just 64 bits shy of being a multiple of 512 bits long.
Padding is always performed, even if the length of the message is
already congruent to 448, modulo 512.</br>
Padding is performed as follows: a single "1" bit is appended to the message, and then "0" bits are appended so that the length in bits of the padded message becomes congruent to 448, modulo 512. In all, at least one bit and at most 512 bits are appended.
</br>
#### 2- Append Length
A 64-bit representation of b (the length of the message before the padding bits were added) is appended to the result of the previous step. In the unlikely event that b is greater than 2^64, then only the low-order 64 bits of b are used.
(These bits are appended as two 32-bit words and appended low-order word first in accordance with the previous conventions.)</br>
At this point the resulting message (after padding with bits and with b) has a length that is an exact multiple of 512 bits.
Equivalently, this message has a length that is an exact multiple of 16 (32-bit) words.
Let M[0 ... N-1] denote the words of the resulting message, where N is a multiple of 16.
#### 3-	Initialize MD Buffer
A four-word buffer (a,b,c,d) is used to compute the message digest. Here each of a, b, c, d is a 32-bit register. 
These registers are initialized to the following values in hexadecimal, low-order bytes first):

word a = 0x67452301</br>
word b = 0xEFCDAB89</br>
word c = 0x98BADCFE</br>
word d = 0x10325476</br>

#### 4-	Process Message in 16-Word Blocks
We first define four auxiliary functions that each take as input three 32-bit words and produce as output one 32-bit word.

F(X,Y,Z) = XY v not(X) Z</br>
G(X,Y,Z) = XZ v Y not(Z)</br>
H(X,Y,Z) = X xor Y xor Z</br>
I(X,Y,Z) = Y xor (X v not(Z))</br>

In each bit position F acts as a conditional: if X then Y else Z.  The function F could have been defined using + instead of v since XY and not(X)Z will never have 1's in the same bit position.) 
It is interesting to note that if the bits of X, Y, and Z are independent and unbiased, the each bit of F(X,Y,Z) will be independent and unbiased.</br>
The functions G, H, and I are similar to the function F, in that they act in "bitwise parallel" to produce their output from the bits of X, Y, and Z, in such a manner that if the corresponding bits of X, Y, and Z are independent and unbiased, then each bit of G(X,Y,Z), H(X,Y,Z), and I(X,Y,Z) will be independent and unbiased. 
Note that the function H is the bit-wise "xor" or "parity" function of its inputs.</br>
This step uses a 64-element table T[1 ... 64] constructed from the sine function.  
Let T[i] denote the i-th element of the table, which is equal to the integer part of 4294967296 times abs(sin(i)), where i is in radians.
See the rounds in the code.</br>

#### 5-	Output
The message digest produced as output is A, B, C, D. That is, we begin  with the low-order byte of A, and end with the high-order byte of D.
This completes the description of MD5. A reference implementation in C is given in the appendix.

<p align="center">
  <b>Complexity</b><br/>
</p>
The MD5 message-digest algorithm is a widely used hash function producing a 128-bit hash value. 
Hash functions(MD5 message-digest algorithm in our case) are one-way functions with an input a string of arbitrary length (the message) and an output a fixed length string (the hash value).
The hash value is a kind of signature for that message. One-way functions work in one direction, meaning that it is easy to compute the hash value from a given message and hard to compute a message that hashes to a given hash value.
Some applications strengthen the MD5 algorithm by adding a salt value to the plaintext or by applying the hash function multiple times.
  <h4>Preliminaries</h4>
MD5 operates on 32-bit unsigned integers called words, where we will number the bits from 0 (least significant bit) up to 31 (most significant bit).
<h4>Definition of MD5</h4>
A sequence of bits will be interpreted in a natural manner as a sequence of bytes, where every group of 8 consecutive bits is considered as one byte, with the leftmost bit being the most significant bit.
However, MD5 works on bytes using Little Endian, which means that in a sequence of bytes, the first byte is the least significant byte.
<h4>MD5 Message Preprocessing</h4>
MD5 can be split up into 5 parts, which are explained above in the section MD5 Algorithm Description.
<h4>MD5 compression function</h4>
The input for the compression function MD5Compress(IHV, B) is an intermediate hash value IHV = (a, b, c, d) and a 512-bit message block B. 
There are 64 steps (numbered 0 up to 63), split into four consecutive rounds of 16 steps each. 
Each step uses a modular addition, a left rotation, and a non-linear function.</br>
<h4>Security</h4>
<h6>1-	Attempt to Reverse MD5 message-digest algorithm.</h6>

