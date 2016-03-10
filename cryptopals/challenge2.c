#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "crypto-utils.h"
#include "base64.h"

// Instructions: write a function that takes two equal-length buffers and
// produces their XOR combintation.
// Compile with gcc challenge2.c crypto-utils.c base64.c -g -o challenge 2

static char* sInputStr2 = "1c0111001f010100061a024b53535009181c";
static char* sInputStr1 = "686974207468652062756c6c277320657965";
static char* sOutputStr = "746865206b696420646f6e277420706c6179";

int main(int argc, char *argv[]){

	int bytesLen = 0;
	char *bytes1 = hexStrToBytes(sInputStr1, &bytesLen);
	if (!bytes1) {
		printf("hexStrToBytes failed!\n");
		return 1;
	}
	char *bytes2 = hexStrToBytes(sInputStr2, &bytesLen);
	if (!bytes2) {
		printf("hexStrToBytes failed!\n");
		free(bytes1);
		return 1;
	}

	char *xorResult = xorByteArrays(bytes1, bytes2, bytesLen);
	if (!xorResult) {
		printf("xorByteArrays failed!\n");
		return 1;
	}	

	free(bytes1);
	free(bytes2);

	char *correctResult = hexStrToBytes(sOutputStr, &bytesLen);
	if (!correctResult) {
		printf("hexStrToBytes failed!\n");
		return 1;
	}

	if (memcmp(xorResult, correctResult, bytesLen) == 0){
		printf("Success!\n");
	} else {
		printf("Failure.\n");
	}
	free(correctResult);
	
	return 0;

}

