#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "crypto-utils.h"
#include "base64.h"

#define V_LOW_STR_SCORE (float)-9999.8
#define ASCII_MAX 127

//compile with gcc challenge4.c base64.c crypto-utils.c -g -o challenge3

char *findLikelyStr(char *str, int* bytesLen, float *highestScore);

int main(int argc, char *argv[]){

	int strLen = 120;
	int bytesLen = 0;

	FILE *file = fopen("challenge4data.txt", "r");
	if (file == NULL) {
		printf("Failure! Couldn't read the file.\n");
		return 1;
	}
	
	float highestScore = V_LOW_STR_SCORE; 
	char* totalHighScoringStr;
	float totalHighScore = V_LOW_STR_SCORE; 
	char* hexStr = malloc(strLen/2);

	while (fgets(hexStr, strLen, file) ){
		char *cleansedStr = strtok(hexStr, "\n");
		char* highestScoringStr = findLikelyStr(cleansedStr, &bytesLen, &highestScore);
		if (!highestScoringStr) {
			printf("findLikelyStr failed!\n");
			return 1;
		}

		if (highestScore > totalHighScore){
			totalHighScore = highestScore;
			totalHighScoringStr = highestScoringStr;
		} else {
			free(highestScoringStr);
		}
	}
	free(hexStr);

	printf("Final string: ");
	for (int i = 0; i < bytesLen; i++){		
		printf("%c", totalHighScoringStr[i]);
	}
	printf("     with flag:  %f \n", totalHighScore);
	free(totalHighScoringStr);

	fclose(file);
}

//given a str, xors it against ascii characters 0-127 and returns best result
char *findLikelyStr(char *str, int* bytesLen, float *highestScore){
	*highestScore = V_LOW_STR_SCORE;
	char* highestScoringStr;
	for (int i = 0; i <= ASCII_MAX; i = i+1){
		char *possibleStr = xorHexStrBySingleByte(str, bytesLen, i);

		float flag = scoreText(possibleStr, *bytesLen);
		if (flag > *highestScore){
			*highestScore = flag;
			highestScoringStr = possibleStr;
		} else {
			free(possibleStr);
		}
	}
	return highestScoringStr;
}
