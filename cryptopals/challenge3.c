#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "crypto-utils.h"
#include "base64.h"

#define ASCII_MAX 127
#define V_LOW_STR_SCORE -999999999

//compile with gcc challenge3.c base64.c crypto-utils.c -g -o challenge3

static char* sInputStr = "1b37373331363f78151b7f2"
			 "b783431333d78397828372d"
			 "363c78373e783a393b3736";

char *findLikelyStr(char *bytes, int *bytesLen);

int main(int argc, char *argv[]){
	int bytesLen = 0;
	char *str = findLikelyStr(sInputStr, &bytesLen);
	if (!str) {
		printf("findLikelyStr failed!\n");
		return 1;
	}	

	for (int j = 0; j < bytesLen; j++){
		printf("%c", str[j]);
	}
	printf("\n");

	free(str);
}

char *findLikelyStr(char *inputStr, int *bytesLen){
	char* highestScoringStr = NULL;
	float highestScore = V_LOW_STR_SCORE; //if the string has that negative a score, we just assume it's not the right one

	for (int i = 0; i <= ASCII_MAX; i++){
		char *possibleStr = xorHexStrBySingleByte(inputStr, bytesLen, i);
		if (!xorResult) {
			printf("xorByteArrays failed!\n");
			return NULL;
		}	

		float flag = scoreText(possibleStr, *bytesLen);
		if (flag > highestScore){
			highestScore = flag;
			if (highestScoringStr) {
				free(highestScoringStr);
				highestScoringStr = NULL;
			}
			highestScoringStr = possibleStr;
		} else {
			free(possibleStr);
		}
	}

	return highestScoringStr;
}


