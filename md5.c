//Theory of Algorithms 2020
//Mark Ndipenoch

/*
 * I research online and found different ways of doing
 *the md5 here are different codes from different websites
 *that I checked.
 */
 //---------------------------Sample 1-----------------------
 //https://rosettacode.org/wiki/MD5
 //Compile with: gcc -o md5 -O3 -lm md5.c
 //Run with : ./md5 "name of your string here"
 /*#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
 
typedef union uwb {
    unsigned w;
    unsigned char b[4];
} WBunion;
 
typedef unsigned Digest[4];
 
unsigned f0( unsigned abcd[] ){
    return ( abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]);}
 
unsigned f1( unsigned abcd[] ){
    return ( abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]);}
 
unsigned f2( unsigned abcd[] ){
    return  abcd[1] ^ abcd[2] ^ abcd[3];}
 
unsigned f3( unsigned abcd[] ){
    return abcd[2] ^ (abcd[1] |~ abcd[3]);}
 
typedef unsigned (*DgstFctn)(unsigned a[]);
 
unsigned *calcKs( unsigned *k)
{
    double s, pwr;
    int i;
 
    pwr = pow( 2, 32);
    for (i=0; i<64; i++) {
        s = fabs(sin(1+i));
        k[i] = (unsigned)( s * pwr );
    }
    return k;
}
 
// ROtate v Left by amt bits
unsigned rol( unsigned v, short amt )
{
    unsigned  msk1 = (1<<amt) -1;
    return ((v>>(32-amt)) & msk1) | ((v<<amt) & ~msk1);
}
 
unsigned *md5( const char *msg, int mlen) 
{
    static Digest h0 = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
//    static Digest h0 = { 0x01234567, 0x89ABCDEF, 0xFEDCBA98, 0x76543210 };
    static DgstFctn ff[] = { &f0, &f1, &f2, &f3 };
    static short M[] = { 1, 5, 3, 7 };
    static short O[] = { 0, 1, 5, 0 };
    static short rot0[] = { 7,12,17,22};
    static short rot1[] = { 5, 9,14,20};
    static short rot2[] = { 4,11,16,23};
    static short rot3[] = { 6,10,15,21};
    static short *rots[] = {rot0, rot1, rot2, rot3 };
    static unsigned kspace[64];
    static unsigned *k;
 
    static Digest h;
    Digest abcd;
    DgstFctn fctn;
    short m, o, g;
    unsigned f;
    short *rotn;
    union {
        unsigned w[16];
        char     b[64];
    }mm;
    int os = 0;
    int grp, grps, q, p;
    unsigned char *msg2;
 
    if (k==NULL) k= calcKs(kspace);
 
    for (q=0; q<4; q++) h[q] = h0[q];   // initialize
 
    {
        grps  = 1 + (mlen+8)/64;
        msg2 = malloc( 64*grps);
        memcpy( msg2, msg, mlen);
        msg2[mlen] = (unsigned char)0x80;  
        q = mlen + 1;
        while (q < 64*grps){ msg2[q] = 0; q++ ; }
        {
//            unsigned char t;
            WBunion u;
            u.w = 8*mlen;
//            t = u.b[0]; u.b[0] = u.b[3]; u.b[3] = t;
//            t = u.b[1]; u.b[1] = u.b[2]; u.b[2] = t;
            q -= 8;
            memcpy(msg2+q, &u.w, 4 );
        }
    }
 
    for (grp=0; grp<grps; grp++)
    {
        memcpy( mm.b, msg2+os, 64);
        for(q=0;q<4;q++) abcd[q] = h[q];
        for (p = 0; p<4; p++) {
            fctn = ff[p];
            rotn = rots[p];
            m = M[p]; o= O[p];
            for (q=0; q<16; q++) {
                g = (m*q + o) % 16;
                f = abcd[1] + rol( abcd[0]+ fctn(abcd) + k[q+16*p] + mm.w[g], rotn[q%4]);
 
                abcd[0] = abcd[3];
                abcd[3] = abcd[2];
                abcd[2] = abcd[1];
                abcd[1] = f;
            }
        }
        for (p=0; p<4; p++)
            h[p] += abcd[p];
        os += 64;
    }
 
    if( msg2 )
        free( msg2 );
 
    return h;
}    
 
int main( int argc, char *argv[] )
{
    int j,k;
   // const char *msg = "The quick brown fox jumps over the lazy dog.";
   char *msg = argv[1];
    unsigned *d = md5(msg, strlen(msg));
    WBunion u;
     
    printf("= 0x");
    for (j=0;j<4; j++){
        u.w = d[j];
        for (k=0;k<4;k++) printf("%02x",u.b[k]);
    }
    printf("\n");
 
    return 0;
}
//Adapted from https://gist.github.com/creationix/4710780
//-------------------Sample 2-------------------
// Compile with: gcc -o md5 -O3 -lm md5.c
// Run with : ./md5 "name of your string here"
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// leftrotate function definition
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
// These vars will contain the hash
uint32_t h0, h1, h2, h3;
void md5(uint8_t *initial_msg, size_t initial_len) {
    // Message (to prepare)
    uint8_t *msg = NULL;
    // Note: All variables are unsigned 32 bit and wrap modulo 2^32 when calculating
    // r specifies the per-round shift amounts
    uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                    5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
    // Use binary integer part of the sines of integers (in radians) as constants// Initialize variables:
    uint32_t k[] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};
    h0 = 0x67452301;
    h1 = 0xefcdab89;
    h2 = 0x98badcfe;
    h3 = 0x10325476;
    // Pre-processing: adding a single 1 bit
    //append "1" bit to message
    // Notice: the input bytes are considered as bits strings,
     //  where the first bit is the most significant bit of the byte.[37] 
    // Pre-processing: padding with zeros
    //append "0" bit until message length in bit ≡ 448 (mod 512)
    //append length mod (2 pow 64) to message
    int new_len = ((((initial_len + 8) / 64) + 1) * 64) - 8;
    msg = calloc(new_len + 64, 1); // also appends "0" bits
                                   // (we alloc also 64 extra bytes...)
    memcpy(msg, initial_msg, initial_len);
    msg[initial_len] = 128; // write the "1" bit
    uint32_t bits_len = 8*initial_len; // note, we append the len
    memcpy(msg + new_len, &bits_len, 4);           // in bits at the end of the buffer
    // Process the message in successive 512-bit chunks:
    //for each 512-bit chunk of message:
    int offset;
    for(offset=0; offset<new_len; offset += (512/8)) {
        // break chunk into sixteen 32-bit words w[j], 0 ≤ j ≤ 15
        uint32_t *w = (uint32_t *) (msg + offset);
#ifdef DEBUG
        printf("offset: %d %x\n", offset, offset);
        int j;
        for(j =0; j < 64; j++) printf("%x ", ((uint8_t *) w)[j]);
        puts("");
#endif
        // Initialize hash value for this chunk:
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        // Main loop:
        uint32_t i;
        for(i = 0; i<64; i++) {
#ifdef ROUNDS
            uint8_t *p;
            printf("%i: ", i);
            p=(uint8_t *)&a;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], a);
            p=(uint8_t *)&b;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], b);
            p=(uint8_t *)&c;
            printf("%2.2x%2.2x%2.2x%2.2x ", p[0], p[1], p[2], p[3], c);
            p=(uint8_t *)&d;
            printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], d);
            puts("");
#endif
            uint32_t f, g;
             if (i < 16) {
                f = (b & c) | ((~b) & d);
                g = i;
            } else if (i < 32) {
                f = (d & b) | ((~d) & c);
                g = (5*i + 1) % 16;
            } else if (i < 48) {
                f = b ^ c ^ d;
                g = (3*i + 5) % 16;
            } else {
                f = c ^ (b | (~d));
                g = (7*i) % 16;
            }
#ifdef ROUNDS
            printf("f=%x g=%d w[g]=%x\n", f, g, w[g]);
#endif
            uint32_t temp = d;
            d = c;
            c = b;
           // printf("rotateLeft(%x + %x + %x + %x, %d)\n", a, f, k[i], w[g], r[i]);
            b = b + LEFTROTATE((a + f + k[i] + w[g]), r[i]);
            a = temp;
        }
        // Add this chunk's hash to result so far:
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
    }
    // cleanup
    free(msg);
}
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }
    char *msg = argv[1];
    size_t len = strlen(msg);
     md5(msg, len);
    
    //var char digest[16] := h0 append h1 append h2 append h3 //(Output is in little-endian)
    uint8_t *p;
    // display result
    p=(uint8_t *)&h0;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h0);
    p=(uint8_t *)&h1;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h1);
    p=(uint8_t *)&h2;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h2);
    p=(uint8_t *)&h3;
    printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3], h3);
    puts("");
    return 0;
}*/

//Adapted from https://people.csail.mit.edu/rivest/Md5.c and
//http://altronic-srl.com.ar/md5%20algoritmo.pdf
//Compile with : Compile with: gcc -o md5 -O3 -lm md5.c
//Run with : .\md5 --run  "your string here"
//Run test cases: .\md5 --test
//Check the program file status: .\md5 --status
//Get basic info about MD5:  .\md5 --about
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define uchar unsigned char
#define uint unsigned int

// DBL_INT_ADD treats two unsigned ints a and b as one 64-bit integer and adds c to it
#define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - c) ++b; a += c;
#define ROTLEFT(a,b) ((a << b) | (a >> (32-b)))

// F, G, H and I are basic MD5 functions.
#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) (y ^ (x | ~z))

// FF, GG, HH, and II transformations for rounds 1, 2,3 and 4.
#define FF(a,b,c,d,m,s,t) { a += F(b,c,d) + m + t; \
                            a = b + ROTLEFT(a,s); }
#define GG(a,b,c,d,m,s,t) { a += G(b,c,d) + m + t; \
                            a = b + ROTLEFT(a,s); }
#define HH(a,b,c,d,m,s,t) { a += H(b,c,d) + m + t; \
                            a = b + ROTLEFT(a,s); }
#define II(a,b,c,d,m,s,t) { a += I(b,c,d) + m + t; \
                            a = b + ROTLEFT(a,s); }
typedef struct { 
   /* input buffer */
   uchar data[64]; 
   uint datalen; 
   uint bitlen[2];
   /* state (abcd) */
   uint state[4]; 
} MD5_CTX; 

//Initialize the constants and begins an MD5 operation.
void md5_init(MD5_CTX *ctx)
{
   ctx->datalen = 0;
   ctx->bitlen[0] = 0;
   ctx->bitlen[1] = 0;
   ctx->state[0] = 0x67452301;
   ctx->state[1] = 0xEFCDAB89;
   ctx->state[2] = 0x98BADCFE;
   ctx->state[3] = 0x10325476;
}

//Transforms the state based on block.
void md5_transform(MD5_CTX *ctx, uchar data[])
{
   uint a,b,c,d,m[16],i,j;

   // MD5 specifies big endian byte order, but this implementation assumes a little
   // endian byte order CPU. Reverse all the bytes upon input, and re-reverse them
   // on output (in md5_final()).
   for (i=0,j=0; i < 16; ++i, j += 4)
      m[i] = (data[j]) + (data[j+1] << 8) + (data[j+2] << 16) + (data[j+3] << 24);

   a = ctx->state[0];
   b = ctx->state[1];
   c = ctx->state[2];
   d = ctx->state[3];
   
   //Round 1
   FF(a,b,c,d,m[0],  7,0xd76aa478);
   FF(d,a,b,c,m[1], 12,0xe8c7b756);
   FF(c,d,a,b,m[2], 17,0x242070db);
   FF(b,c,d,a,m[3], 22,0xc1bdceee);
   FF(a,b,c,d,m[4],  7,0xf57c0faf);
   FF(d,a,b,c,m[5], 12,0x4787c62a);
   FF(c,d,a,b,m[6], 17,0xa8304613);
   FF(b,c,d,a,m[7], 22,0xfd469501);
   FF(a,b,c,d,m[8],  7,0x698098d8);
   FF(d,a,b,c,m[9], 12,0x8b44f7af);
   FF(c,d,a,b,m[10],17,0xffff5bb1);
   FF(b,c,d,a,m[11],22,0x895cd7be);
   FF(a,b,c,d,m[12], 7,0x6b901122);
   FF(d,a,b,c,m[13],12,0xfd987193);
   FF(c,d,a,b,m[14],17,0xa679438e);
   FF(b,c,d,a,m[15],22,0x49b40821);
   
   //Round 2
   GG(a,b,c,d,m[1],  5,0xf61e2562);
   GG(d,a,b,c,m[6],  9,0xc040b340);
   GG(c,d,a,b,m[11],14,0x265e5a51);
   GG(b,c,d,a,m[0], 20,0xe9b6c7aa);
   GG(a,b,c,d,m[5],  5,0xd62f105d);
   GG(d,a,b,c,m[10], 9,0x02441453);
   GG(c,d,a,b,m[15],14,0xd8a1e681);
   GG(b,c,d,a,m[4], 20,0xe7d3fbc8);
   GG(a,b,c,d,m[9],  5,0x21e1cde6);
   GG(d,a,b,c,m[14], 9,0xc33707d6);
   GG(c,d,a,b,m[3], 14,0xf4d50d87);
   GG(b,c,d,a,m[8], 20,0x455a14ed);
   GG(a,b,c,d,m[13], 5,0xa9e3e905);
   GG(d,a,b,c,m[2],  9,0xfcefa3f8);
   GG(c,d,a,b,m[7], 14,0x676f02d9);
   GG(b,c,d,a,m[12],20,0x8d2a4c8a);

   //Round 3
   HH(a,b,c,d,m[5],  4,0xfffa3942);
   HH(d,a,b,c,m[8], 11,0x8771f681);
   HH(c,d,a,b,m[11],16,0x6d9d6122);
   HH(b,c,d,a,m[14],23,0xfde5380c);
   HH(a,b,c,d,m[1],  4,0xa4beea44);
   HH(d,a,b,c,m[4], 11,0x4bdecfa9);
   HH(c,d,a,b,m[7], 16,0xf6bb4b60);
   HH(b,c,d,a,m[10],23,0xbebfbc70);
   HH(a,b,c,d,m[13], 4,0x289b7ec6);
   HH(d,a,b,c,m[0], 11,0xeaa127fa);
   HH(c,d,a,b,m[3], 16,0xd4ef3085);
   HH(b,c,d,a,m[6], 23,0x04881d05);
   HH(a,b,c,d,m[9],  4,0xd9d4d039);
   HH(d,a,b,c,m[12],11,0xe6db99e5);
   HH(c,d,a,b,m[15],16,0x1fa27cf8);
   HH(b,c,d,a,m[2], 23,0xc4ac5665);

   //Round 4
   II(a,b,c,d,m[0],  6,0xf4292244);
   II(d,a,b,c,m[7], 10,0x432aff97);
   II(c,d,a,b,m[14],15,0xab9423a7);
   II(b,c,d,a,m[5], 21,0xfc93a039);
   II(a,b,c,d,m[12], 6,0x655b59c3);
   II(d,a,b,c,m[3], 10,0x8f0ccc92);
   II(c,d,a,b,m[10],15,0xffeff47d);
   II(b,c,d,a,m[1], 21,0x85845dd1);
   II(a,b,c,d,m[8],  6,0x6fa87e4f);
   II(d,a,b,c,m[15],10,0xfe2ce6e0);
   II(c,d,a,b,m[6], 15,0xa3014314);
   II(b,c,d,a,m[13],21,0x4e0811a1);
   II(a,b,c,d,m[4],  6,0xf7537e82);
   II(d,a,b,c,m[11],10,0xbd3af235);
   II(c,d,a,b,m[2], 15,0x2ad7d2bb);
   II(b,c,d,a,m[9], 21,0xeb86d391);

   ctx->state[0] += a;
   ctx->state[1] += b;
   ctx->state[2] += c;
   ctx->state[3] += d;
}

/* This continues an MD5 message-digest
 operation, processing another message block, and updating the
 context.
 */
void md5_update(MD5_CTX *ctx, uchar data[], uint len)
{
   uint t,i;

   for (i=0; i < len; ++i) {
      ctx->data[ctx->datalen] = data[i];
      ctx->datalen++;
      if (ctx->datalen == 64) {
         md5_transform(ctx,ctx->data);
         DBL_INT_ADD(ctx->bitlen[0],ctx->bitlen[1],512);
         ctx->datalen = 0;
      }
   }
}

/* This  ends an MD5 message-digest operation, writing the
 the message digest and zeroizing the context.
 */
void md5_final(MD5_CTX *ctx, uchar hash[])
{
   uint i;

   i = ctx->datalen;

   // Pad whatever data is left in the buffer.
   if (ctx->datalen < 56) {
      ctx->data[i++] = 0x80;
      while (i < 56)
         ctx->data[i++] = 0x00;
   }
   else if (ctx->datalen >= 56) {
      ctx->data[i++] = 0x80;
      while (i < 64)
         ctx->data[i++] = 0x00;
      md5_transform(ctx,ctx->data);
      memset(ctx->data,0,56);
   }

   // Append to the padding the total message's length in bits and transform.
   DBL_INT_ADD(ctx->bitlen[0],ctx->bitlen[1],8 * ctx->datalen);
   ctx->data[56] = ctx->bitlen[0];
   ctx->data[57] = ctx->bitlen[0] >> 8;
   ctx->data[58] = ctx->bitlen[0] >> 16;
   ctx->data[59] = ctx->bitlen[0] >> 24;
   ctx->data[60] = ctx->bitlen[1];
   ctx->data[61] = ctx->bitlen[1] >> 8;
   ctx->data[62] = ctx->bitlen[1] >> 16;
   ctx->data[63] = ctx->bitlen[1] >> 24;
   md5_transform(ctx,ctx->data);

   // Since this implementation uses little endian byte ordering and MD uses big endian,
   // reverse all the bytes when copying the final state to the output hash.
   for (i=0; i < 4; ++i) {
      hash[i]    = (ctx->state[0] >> (i*8)) & 0x000000ff;
      hash[i+4]  = (ctx->state[1] >> (i*8)) & 0x000000ff;
      hash[i+8]  = (ctx->state[2] >> (i*8)) & 0x000000ff;
      hash[i+12] = (ctx->state[3] >> (i*8)) & 0x000000ff;
   }
}

//print the result as a hexadecimal
const char * print_hash(char hash[]) 
{
   char s1[50];
   static  char tagstr[1000] ="";
   int idx;
   //Clear array and always start from an empty array
   memset(tagstr, 0, sizeof(tagstr));
   for(idx=0; idx < 16; idx++) {
      // printf("%02x",hash[idx]&0x000000ff); 
      //convert the hexadecimal value to a string
      sprintf(s1, "%02x",hash[idx]&0x000000ff);
      //Concatenate the 16 substrings to a single string
      strcat(tagstr, s1);
      }
   return tagstr;
} 

//gitopt adpated from https://github.com/ndipenoch/Theory-of-Algorithms-Project/blob/master/md5test.c
//Main method takes a string as an input
int main(int argc, char **argv)
{
  int c;
  char hash[16];
  char *msg;
  MD5_CTX ctx;


  while (1)
    {
      static struct option long_options[] =
        {
          /* These options don’t set a flag.
             We distinguish them by their indices. */
          {"help",     no_argument,       0, 'h'},
          {"status",  no_argument,        0, 's'},
          {"test",     no_argument,       0, 't'},
          {"about",    no_argument,       0, 'a'},
		      {"run",  required_argument,     0, 'r'},
          {0, 0, 0, 0}
        };
      /* getopt_long stores the option index here. */
      int option_index = 0;
      /*r or --run takes an argument*/
      c = getopt_long (argc, argv, "hvtr:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          printf ("option %s", long_options[option_index].name);
          if (optarg)
            printf (" with arg %s", optarg);
          printf ("\n");
          break;

        case 'a':
          printf("          This is an MD5 Message-Digest Algorithm. \n");
          printf("  MD5 was designed by Ronald Rivest in 1991 to \n");
          printf("  replace an earlier hash function MD4.\n");
          printf("  The MD5 message-digest algorithm, is a widely \n");
          printf("  used hash function that takes as input \n");
          printf("  a message of arbitrary length and produces as output \n");
          printf("  a 128-bit <fingerprint> or message \n");
          printf("  digest of the input. \n");
          printf("  Copy Right: Mark Ndipenoch.\n");
          break;

        case 'h':
          printf ("Compile with : Compile with: gcc -o md5 -O3 -lm md5.c \n");
          printf ("Run with : .\\md5 --run 'your string here' \n");
          printf ("To run tests : .\\md5 --test \n"); 
          printf ("To check the version : .\\md5 --version \n"); 
          printf ("To get help : .\\md5 --help \n");
          printf ("Below are samples of inputs and results: \n");
          printf ("1) Input abc and Output: 900150983cd24fb0d6963f7d28e17f72 \n");
          printf ("2) Input 0123456789 and Output: 781e5e245d69b566979b86e28d23f2c7 \n");
          break;

        case 's':
        //Adapted from https://c-for-dummies.com/blog/?p=3004
         printf("");
         struct stat filestat;
         stat("md5.c",&filestat);
         /* newline included in ctime() output */
         printf(" File access time %s",
            ctime(&filestat.st_atime)
          );
         printf(" File modify time %s",
            ctime(&filestat.st_mtime)
          );
         printf(" File changed time %s",
            ctime(&filestat.st_ctime)
          );
          break;

        case 't':
          printf("");

         char testInputs[10][1000]=
          {"","a","abc","message digest","abcdefghijklmnopqrstuvwxyz","0123456789",
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
          "The quick brown fox jumps over the lazy dog",
          "The quick brown fox jumped over the lazy dog's back",
          "12345678901234567890123456789012345678901234567890123456789012345678901234567890"};
          char testOutputs[10][1000]=
          {"d41d8cd98f00b204e9800998ecf8427e","0cc175b9c0f1b6a831c399e269772661",
          "900150983cd24fb0d6963f7d28e17f72","f96b697d7cb7938d525a2f31aaf161d0",
          "c3fcd3d76192e4007dfb496cca67e13b","781e5e245d69b566979b86e28d23f2c7",
          "d174ab98d277d9f5a5611c2c9f419d9f","9e107d9d372bb6826bd81d3542a419d6",
          "e38ca1d920c4b8b8d3946b2c72f01680","57edf4a22be3c955ac49da2e2107b67a"};
          int loop;
          
          /*const char* testRslt = print_hash(hash);
          printf("--Return Rlst---%s\n", testRslt);*/

          //print all strings
          for(loop=0;loop<10;loop++){
          printf("");
          md5_init(&ctx);
          md5_update(&ctx,testInputs[loop],strlen(testInputs[loop]));
          md5_final(&ctx,hash);
          const char* testRslt = print_hash(hash);
          printf("Input:     %s\n", testInputs[loop]);
          printf("Expected:  %s\n", testRslt);
          printf("Actual:    %s\n", testOutputs[loop]);
          if (strcmp(testRslt,testOutputs[loop]) == 0){
               printf("Status:    PASSED\n");
               }
          else{
               printf("Status:    FAILED\n");
               }
          }
          break;

		case 'r':
          msg = optarg;

          md5_init(&ctx);
          md5_update(&ctx,msg,strlen(msg));
          md5_final(&ctx,hash);
          const char* result =  print_hash(hash);
          printf("%s\n",result);
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
    {
      printf ("non-option ARGV-elements: ");
      while (optind < argc)
        printf ("%s ", argv[optind++]);
      putchar ('\n');

   }
exit (0);
}
