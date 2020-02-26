//Mark Ndipenoch
//Padding for SHA256

#include <stdio.h>
#include <inttypes.h>

uint64_t nozerobytes(uint64_t nobits){
//set the output to be multiples of 512 bits
//ULL tells the C compiler the value should be a 64 bits
//integer.
 uint64_t result = 512ULL - (nobits%512ULL);

//if result is less than 64 bits
//append zeros at the end.
 if(result<65)
   result +=512;
 result -=72;
//divide the result by 8 to know the number 
//of zeros to add.
 return(result/8ULL);
 }

int main(int argc, char *argv[]){

 if(argc !=2){
 printf("Error: expected single filename as argument.\n");
 return 1;
 }

 FILE *infile = fopen(argv[1], "rb");
 if(!infile){
   printf("Error: couldn't open file.\n", argv[1]);
   return 1;
   }
  
   //Create an unsign 8 byte interger to read a
  //byt at a time and set a limit of 64 bits
   uint8_t b;
   uint64_t nobits;
   for(nobits=0;fread(&b,1,1,infile)==1;nobits +=8){
   printf("%02" PRIx8, b);
   }

   printf("%02" PRIx8, 0x80); //Bits 1000000

   for(uint64_t i = nozerobytes(nobits); i>0;i--){
     printf("%02" PRIx8, 0X00);
    }

   printf("%016" PRIx64, "\n", nobits);

  // printf("\n");

  fclose(infile);
return 0;
}


