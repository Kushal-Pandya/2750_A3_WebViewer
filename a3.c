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


int getInfo(FILE *infile, char tag);
char *getAttribute(FILE *infile, char *tag);



void parseFile() {
	
	char buffer[500];
	char tag;
	unsigned long position = 0;

	FILE *infile = fopen("format.txt", "r");

	while (fgets(buffer, 500, infile) != NULL) {

		if (strcmp(buffer, "\n") != 0) {
			tag = buffer[0];

			switch(tag) {
				case 'd':
					printf("\t<hr>\n");


			}
		}
	}

	fclose(infile);
}


void formatFile(FILE *infile) {
	char c;
	int inBrackets = 0;
	int inString = 0;
	FILE *tempfile = fopen("format.txt", "w");

	while ((c = fgetc(infile)) != EOF) {

		switch(c) {
			case '.':
				if (inBrackets == 0 && inString == 0)
					fprintf(tempfile, "\n");
				break;
			case '(': 
				if (inString == 0)
					inBrackets = 1;
				fprintf(tempfile, "%c", c);
				break;
			case '"':
				if (inString == 1 && inBrackets == 1)
					inString = 0;
				else if (inBrackets == 1)
					inString = 1;

				if (inBrackets == 0)
					fprintf(tempfile, "%c", c);
				break;
			case ')':
				if (inString == 0)
					inBrackets = 0;
				fprintf(tempfile, "%c", c);
				break;
			default:
				fprintf(tempfile, "%c", c);
				break;
		}
	}
	fclose(tempfile);
}

int main(int argc, char *argv[]) {

	FILE *fp = fopen("config.wpml", "r");
	printf("<!DOCTYPE html>\n<html>\n");
	
	formatFile(fp);
	parseFile();

	printf("</html>\n");
	fclose(fp);

	return 0;
}
