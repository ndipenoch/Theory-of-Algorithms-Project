//Mark Ndipenoch
//
//The secure Hash Algorithm 256-bit version

#include<stdio.h>
#include<stdint.h>

//section 4.2.2
const uint32_t K[]={

};

//Section 5.3.3
const uint32_t H[] = {

};
uint32_t Ch(uint32_t x,uint32_t y,uint32_t z){

return (x &y) ^(~x & z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
return (x & y)^(x & z)^(y & z);
}

uint32_t SHR(uint32_t x, int n){
return x>>n;
}

uint32_t ROTR(uint32_t x, int n){
return (x>>n) | (x<<(32-n));
}

uint32_t Sig0(uint32_t x){
return ROTR(x,2)^ROTR(x,13)^ROTR(x,22);
}

uint32_t Sig1(uint32_t x){
return ROTR(x,6)^ROTR(x,18)^ROTR(x,25);
}

uint32_t sig0(uint32_t x){
return ROTR(x,7)^ROTR(x,18)^SHR(x,3);
}

uint32_t sig1(uint32_t x){
return ROTR(x,17)^ROTR(x,19)^SHR(x,10);
}

