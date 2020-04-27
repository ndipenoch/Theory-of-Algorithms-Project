<p align="center">
  <b>Theory of Algorithms</b><br>
</p>


<p align="center">
  <b>Overview</b><br>
</p>
Due to the rapid advancement of technology, the integrity of documents and security protocols should be preserved.
One of the ways to achieve this is by using a digital signature. 
A digital signature is a specific code which is generated from the function of producing a digital signature. 
One of the algorithms that is used to create the digital signature is a hash function. There are many hash functions.
One of the main hash function is MD5 message-digest algorithm [1,2,3].
In this document we will be talking about MD5 message-digest algorithm.<br/>
Also, to do this project, I watched and followed the lecturer's video on how to code up SHA56 in C. The final version of the SHA56 is also included in this repository in the file sha-256.c.<br/>
I also looked up online on how different people have done the MD5 message-digest algorithm in C and in different languages. Two particular examples caught my attention.<br/> I started by following these examples and doing my project like in the examples. So, I can understand better the different concepts about MD5 digest Algorithm.<br/> I finally ended up doing my project in 3 different ways. The 3rd way was adapted from the two previous ways. All three ways are included in the md5.c file.
The first two ways are commented out.<br/>


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
<h4>Sample Test and Results</h4>
-Input: "abc" OutPut: "900150983cd24fb0d6963f7d28e17f72"<br/>
-Input: "The quick brown fox jumps over the lazy dog" OutPut: "9e107d9d372bb6826bd81d3542a419d6"<br/>
-Input: "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" OutPut: "d174ab98d277d9f5a5611c2c9f419d9f"
<p align="center">
  <b>Tool used</b><br/>
</p>
-Google Cloud SSH
-GitHup
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
A salt is random data that is used as an additional input to a one-way function that hashes data.
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
If you ask me personally, can you reverse a message digest to get the original message ? From all my researches and the papers/articles I have read, my answer is no and yes.<br>
No, because practically it is impossible.  Since a lot of information is lost in producing a message digest. A message of any size produces a 32 digit (32 byte) hex number. Trying to reproduce a message from its hash is like trying to rebuild a burned building from a hand full of its ashes. You can identify the building from the wreckage, but cannot reconstruct it.
Also, in some scenarios we can have very large or infinite possibilities and might not have the computer with enough power to compute all the possible possibilities. Imagine building the tallest building in the world Burj Khalifa  from a hand full of it ashes.
In addition, this can be made harder or complicated if the MD5 hash is using a good salt.
The salt, will increase the possible possibilities by a very large amount depending on how the salt is done.</br>
Yes because, theoretically it sounds possible. if we have a database that contains all the possible buildings that can be gotten from that particular ashes, then one of the building will be correct/original building used. We can use brut force to do this. But this also can be made harder or complicated if the MD5 hash is using a good salt. 
So, theoretically if we use brut force on a very power computer we can get the original message form the MD5 message digest. By brut force I mean trying out every single possible possibilities until we get the results. In some cases if the system is poorly constructed that it will allow users to give a hirt of what they use to compute the message digest. This will narrow down the possibilities when using brut force.
<h6>2- Collision detection</h6>
The MD5 message-digest algorithm, was initially designed to be used as a cryptographic hash function, it has been found to suffer from extensive vulnerabilities. It can still be used as a checksum to verify data integrity, but only against unintentional corruption. It remains suitable for other non-cryptographic purposes, for example for determining the partition for a particular key in a partitioned database.</br>
Practically it is impossible to reverse or compute an original message from a MD5 message digest but there are other security flaws like collision detection. Collision detection is having the same message digest from 2 or more different messages. </br>
A collision attack exists that can find collisions within seconds on a computer with a 2.6 GHz Pentium 4 processor as explained by M.M.J. Stevens (June 2007). "On Collisions for MD5",[6] in section 5 - Collision Finding Improvements.</br>
Also, in 1993, B. den Boer and A. Bosselaers,[7] showed a weakness in MD5 by finding a ”pseudo collision” for MD5 consisting of the same message with different initial values.</br>
Also, as explained by M.M.J. Stevens (June 2007). "On Collisions for MD5",[6] in section 1.2. MD5 returns a hash value of 128 bits, which is small enough for a brute force birthday attack of order 264. Such a brute force attack was attempted by the distributed computing project MD5CRK which started in March 2004. </br>
In addition, H. Dobbertin[5] published in 1996 a semi free-start collision which
consisted of two different 512-bit messages with a chosen initial value. This attack does not produce collisions for the full MD5, however it reveals that in MD5, differences in the higher order bits of the working state do not diffuse fast enough.</br>
Furthermore, X. Wang and H. Yu [4] revealed in 2005 their new powerful attack on MD5 which allowed them to find the collisions presented in their publication of 2004 [10] efficiently.
Their attack is based on a combined additive and XOR differential method. Using this differential they have constructed 2 differential paths for the compression function of MD5 which are to be used consecutively to generate a collision of MD5 itself. Their constructed differential paths describe precisely how differences between the two pairs (IHV, B) and (IHV 0, B0), of an
intermediate hash value and an accompanying message block, propagate through the compression function. They described the integer difference (−1, 0 or +1) in every bit of the intermediate working states Qt and even specific values for some bits.</br>
Also, the setting of digital certificates is not entirely safe as Lenstra and de Weger[11] presented two colliding X.509 certificates with different public keys, but with identical signatures from a Certificate Authority. Although as they contain the same identity there is no realistic abuse scenario.
<h4>Running Time</h4>
The MD5 message-digest algorithm  was designed to be fast and it is. This is demonstrated as seen in the image below when the Running Time is compared to SHA256 Algorithm by D Rachmawati1, J T Tarigan1 and A B C Ginting,[9] in section 3.3.</br>
 <p align="center">
  <img width="460" height="300" src="https://github.com/ndipenoch/Theory-of-Algorithms-Project/blob/master/runningTime.PNG">
</p>
<p align="center">
  <b>Conclusion</b><br/>
</p>
The MD5 message-digest algorithm is simple to implement, and provides
a "fingerprint" or message digest of a message of arbitrary length. It is conjectured that the difficulty of coming up with two messages having the same message digest is on the order of 2^64 operations, and that the difficulty of coming up with any message having a given message digest is on the order of 2^128 operations. The MD5 algorithm has been carefully scrutinized for weaknesses. It is, however, a relatively new algorithm and further security analysis is of course justified, as is the case with any new proposal of this sort.
<p align="center">
  <b> References</b><br/>
</p>
1-	Md5 message-digest  paper by Ronald L. Rivest  - 
 http://altronic-srl.com.ar/md5%20algoritmo.pdf </br>
2-	Ron Rivest. Request for comments: 1321, the md5 message-digest algorithm. - https://tools.ietf.org/html/rfc1321 </br>
3-	RSA Data Security, Inc. MD5 Message Digest Algorithm - https://people.csail.mit.edu/rivest/Md5.c </br>
4-	Xiaoyun Wang and Hongbo Yu, How to break MD5 and other hash functions, EUROCRYPT 2005 (Ronald Cramer, ed.), LNCS, vol. 3494, Springer, 2005, pp. 19–35. - https://link.springer.com/content/pdf/10.1007/11426639_2.pdf </br>
5-	Hans Dobbertin, Cryptanalysis of MD5 compress, 1996, presented at the rump session of Eurocrypt’96. </br>
6-	M.M.J. Stevens (June 2007). "On Collisions for MD5" </br>
 https://www.win.tue.nl/hashclash/On%20Collisions%20for%20MD5%20-%20M.M.J.%20Stevens.pdf </br>
7-	Collisions for the compression function of MD5 by B. den Boer and A. Bosselaers - https://link.springer.com/content/pdf/10.1007/3-540-48285-7_26.pdf </br>
8-	The MD4 message digest algorithm by Rivest, Ronald L</br>
https://link.springer.com/content/pdf/10.1007/3-540-38424-3_22.pdf </br>

9-	Comparison of Running Time between MD5 Algorithm and SHA256 Algorithm  by Rachmawati_2018, section 3.3.
https://iopscience.iop.org/article/10.1088/1742-6596/978/1/012116/pdf </br>
10-	Xiaoyun Wang, Dengguo Feng, Xuejia Lai, and Hongbo Yu, Collisions for hash functions  MD4, MD5, HAVAL-128 and RIPEMD, Cryptology ePrint Archive, Report 2004/199, 2004 – 
https://www.researchgate.net/profile/Xuejia_Lai/publication/220336420_Collisions_for_Hash_Functions_MD4_MD5_HAVAL-128_and_RIPEMD/links/0deec525de0417d8eb000000.pdf </br>
11-	Arjen K. Lenstra and Benne de Weger, On the possibility of constructing meaningful hash collisions for public keys, ACISP 2005 (Colin Boyd and Juan Manuel Gonz´alez Nieto, eds.), LNCS, vol. 3574, Springer, 2005, pp. 267–279.
 https://link.springer.com/chapter/10.1007/11506157_23 </br>
 12 - [Simple MD5 implementation](https://gist.github.com/creationix/4710780).

	
