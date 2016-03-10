#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "crypto-utils.h"
#include "base64.h"

#define NUM_HEX_DIGITS 16
#define NUM_DEC_DIGITS 10


//Compile with: gcc challenge5.c crypto-utils.c base64.c -g -lm -o challenge5

static char *sInputStr = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

static char *sOutputStr = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202"
			"d623d63343c2a26226324272765272a282b2f20430a652e2c652"
			"a3124333a653e2b2027630c692b20283165286326302e27282f";

char *repeatingKeyXOR(char *input, char *key, int *bytesLen);
char *asciiToHex(char *inputStr, int *hexStrLen);

int main(int argc, char *argv[]){
	char *key = "ICE";

	int bytesLen = strlen(sInputStr);
	int keyLen = strlen(key);

	char *hexKey = asciiToHex(key, &keyLen);
	char *hexStr = asciiToHex(sInputStr, &bytesLen);

	char *encodedStr = repeatingKeyXOR(hexStr, hexKey, &bytesLen);
	free(hexKey);
	free(hexStr);

	char *correctResult = hexStrToBytes(sOutputStr, &bytesLen);
	if (!correctResult) {
		printf("hexStrToBytes failed!\n");
		return 1;
	}


	if (memcmp(encodedStr, correctResult, bytesLen) == 0){
		printf("Success!\n");
	} else {
		printf("Failure.\n");
	}
	free(encodedStr);
	free(correctResult);
}

//Takes an input string and its length, and then encodes it against a given key
char *repeatingKeyXOR(char *input, char *key, int *bytesLen){
	int keyLen = 0;

	char *keyBytes = hexStrToBytes(key, &keyLen);
	if (!keyBytes) {
		printf("hexStrToBytes failed in %s\n, key", __PRETTY_FUNCTION__);
		return NULL;
	}

	char *bytes = hexStrToBytes(input, bytesLen);
	if (!bytes) {
		printf("hexStrToBytes failed in %s, bytes \n", __PRETTY_FUNCTION__);
		return NULL;
	}

	char *encodedStr = malloc(*bytesLen);
	for (int i = 0; i < *bytesLen; i++){
		encodedStr[i] = bytes[i]^keyBytes[i % keyLen];
	}

	return encodedStr;
}

//given an input ascii string and its length, converts to a string in hex
char *asciiToHex(char *inputStr, int *hexStrLen){
	char *hexStr = malloc(*hexStrLen * 2 + 1);

    	for(int i = 0; i < *hexStrLen; i++){
		int character = inputStr[i];
		int hexOnesPlace = character % NUM_HEX_DIGITS;
		int hexSixteensPlace = floor((float)character / NUM_HEX_DIGITS);
		char *alphaChars = "abcdef";
		
		if (hexSixteensPlace >= NUM_HEX_DIGITS){
			printf("Failure! Invalid character. char: %d \n", character);
  			return NULL;
		} else if (hexSixteensPlace >= 0 && hexSixteensPlace < NUM_DEC_DIGITS) {
    			hexStr[2 * i] = hexSixteensPlace+'0';
  		} else if (hexSixteensPlace >= NUM_DEC_DIGITS) {
    			hexStr[2 * i] = alphaChars[hexSixteensPlace - NUM_DEC_DIGITS];
  		}
		
		if (hexOnesPlace >= 0 && hexOnesPlace < NUM_DEC_DIGITS) {
    			hexStr[2 * i + 1] = hexOnesPlace+'0';
  		} else if (hexOnesPlace >= NUM_DEC_DIGITS) {
    			hexStr[2 * i + 1] = alphaChars[hexOnesPlace - NUM_DEC_DIGITS];
  		}
    	}

	*hexStrLen = *hexStrLen * 2;
	return hexStr;
}
