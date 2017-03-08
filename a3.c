/*
	CIS 2750
	A3
	Author: Kushal Pandya
	Due Date: March 10 2017

	Configuration File Convertor
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int isWhiteSpace(char ch) {
	switch(ch) {
		case ' ':
		case '\t':
		case '\n':
		case '\r':
			return 0;
		default:
			return 1;
	}
}


void parseFile(FILE *infile) {
	char c;

	char tag;
	char *attribute = calloc(50, sizeof(char));
	char *value = calloc(100, sizeof(char));

	char *temp = calloc(2, sizeof(char));

	int nextTag = 0;
	int nextAttribute = 0;
	int nextValue = 0;

	int inBrackets = 0;

	while ((c = fgetc(infile)) != EOF) {

		switch(c) {
			case '.':
				if (inBrackets == 0)
					nextTag = 1;
				break;
			case '(': 
				nextTag = 0;
				inBrackets = 1;
				break;
			case ')':
				nextTag = 0;
				inBrackets = 0;
				break;
			default:
				if (inBrackets == 0 && c != '.' && isWhiteSpace(c)) {
					tag = c;
					printf("%c\n", tag);
					nextTag = 0;
					nextAttribute = 1;
				}
				break;
		}

		/*if (c == '.' && inBrackets == 0)
			nextTag = 1;
		else if (c == '(') {
			nextTag = 0;
			inBrackets = 1;
		}

		/*Getting HTML Tag here
		if (inBrackets == 0 && c != '.' && isWhiteSpace(c)) {
			tag = c;
			printf("%c\n", tag);
			nextTag = 0;
			nextAttribute = 1;
		}

		if (c == ')') {
			nextTag = 0;
			inBrackets = 0;
		}*/
	}
}


int main(int argc, char *argv[]) {

	FILE *fp = fopen("config", "r");
	printf("<!DOCTYPE html>\n<html>\n");
	
	parseFile(fp);

	printf("</html>\n");
	fclose(fp);

	return 0;
}
