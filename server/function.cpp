#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <cmath>
using namespace std;
//int to binary 
//for port 16bit
void IntToBin(unsigned int dec,char ch[] ) {
      int i = 16;
      while(i >= 0)
      {
         int temp  = dec;
         temp = temp >> i;
         ch[17-i-1] = (temp & 1)+'0';
         i--;
      }
}

void CharToBin(char c) {
	unsigned char k = 0x80;
	for (int i=0; i<8; i++, k >>= 1)
	{
		if (c & k)
			cout<<"1";
		else
			cout<<"0";
	}
	cout<<" ";
}

void IntToChar(char *changeBuffer, int changeInt) {
	sprintf(changeBuffer, "%d", changeInt);
	strcat(changeBuffer, "\0");
}

int charToInt(char *changeBuffer) {
	int length = strlen(changeBuffer);
	int sum = 0;
	for(int i = 0; i < length; i++) {
		sum = sum + pow(10, length - i - 1) * (changeBuffer[i] - '0');
	}
	return sum;
}

int bCharToInt(char *changeBuffer) {
	int length = strlen(changeBuffer);
	int sum = 0;
	for(int i = 0; i < length; i++) {
		sum = sum + pow(2, length - i - 1) * (changeBuffer[i] - '0');
	}
	return sum;
}

void divide(char * dest,char * src,int start,int n)
{
	src=src+start-1;
	while ( (* dest++ = * src++) && n-1)
		n--;
	* dest='\0';
}