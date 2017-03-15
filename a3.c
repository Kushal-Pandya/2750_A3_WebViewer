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

int getIndexOfChar(char * string, char c);
int getInfo(FILE *infile, char tag);
char *getAttribute(FILE *infile, char *tag);
int removeCharFromString(char * string, char c);


char **getArgs(char *argString) {

	int i;
	char *newStr;
	char *token;

	/*Creating args array*/
	char **args = malloc(sizeof(char*)*10);
	for (i=0; i<10; i++)
		args[i] = calloc(100, sizeof(char));


	strtok(argString, "(");
	newStr = strtok(NULL, "(");
	removeCharFromString(newStr, ')');

	if (strchr(newStr, ',') == NULL) {
		strcpy(args[0], newStr);
		return args;
	}

	i = 0;
	token = strtok(newStr, ",");
	while(token != NULL) {

		strcpy(args[i], token);
		token = strtok(NULL, ",");
		i++;
	}
	
	return args;
}


void tConvert(char **args) {

	int i;
	char *attribute;
	char *value;
	char buffer[500];

	for (i=0; i<10; i++) {
		attribute = strtok(args[i], "=");
		value = strtok(NULL, "=");

		if (value != NULL) {
			if (strcmp(attribute, "text") == 0)
				printf("%s", value);
			else if (strcmp(attribute, "file") == 0) {

				value[strcspn(value, "\r\n")] = 0;
				FILE *fp = fopen(value, "r");
				if (fp == NULL) {
					printf("ERROR FILE NOT FOUND '%s'\n", value);
					exit(0);
				}

				while (fgets(buffer, 500, fp) != NULL) {
					printf("%s", buffer);
				}
			}	
		}
	}
}

void hConvert(char **args) {

	int i;
	char *attribute;
	char *value;
	int size = 3;
	char *text = calloc(100, sizeof(char));

	for (i=0; i<10; i++) {
		attribute = strtok(args[i], "=");
		value = strtok(NULL, "=");

		if (value != NULL) {
			value[strcspn(value, "\r\n")] = 0;

			if (strcmp(attribute, "text") == 0)
				strcpy(text, value);

			else if (strcmp(attribute, "size") == 0) {
				size = atoi(value);
			}	
		}
	}
	printf("<h%d>%s</h%d>\n", size, text, size);
	free(text);
}

void pConvert(char **args) {

	int i;
	int height = 100;
	int width = 100;

	char *token;
	char *attribute;
	char *value;
	char *imageName = calloc(100, sizeof(char));

	for (i=0; i<10; i++) {
		attribute = strtok(args[i], "=");
		value = strtok(NULL, "=");

		if (value != NULL) {
			value[strcspn(value, "\r\n")] = 0;

			if (strcmp(attribute, "image") == 0)
				strcpy(imageName, value);

			else if (strcmp(attribute, "size") == 0) {
				token = strtok(value, "x");
				width = atoi(token);
				token = strtok(NULL, "x");
				height = atoi(token);
			}	
		}
	}
	printf("<img src=\"%s\" style=\"width:%dpx;height:%dpx;\">\n", imageName, width, height);
	free(imageName);
}

void lConvert(char **args) {

	int i;
	char *attribute;
	char *value;
	char *text = calloc(100, sizeof(char));
	char *url = calloc(500, sizeof(char));

	for (i=0; i<10; i++) {
		attribute = strtok(args[i], "=");
		value = strtok(NULL, "=");

		if (value != NULL) {
			value[strcspn(value, "\r\n")] = 0;

			if (strcmp(attribute, "text") == 0)
				strcpy(text, value);

			else if (strcmp(attribute, "link") == 0) {
				strcpy(url, value);
			}	
		}
	}
	printf("<a href=\"%s\">%s</a>\n", url, text);
	
	free(text);
	free(url);
}

void parseFile() {
	
	int i;
	char buffer[500];
	char tag;
	char **args;

	FILE *infile = fopen("format.txt", "r");

	while (fgets(buffer, 500, infile) != NULL) {

		/*If buffer[1] is not ( then we know its a unspecified tag*/
		if (strcmp(buffer, "\n") != 0 && buffer[1] == '(') {
			tag = buffer[0];

			args = getArgs(buffer);

			switch(tag) {
				case 'd':
					printf("<hr>\n");
					break;
				case 't':
					tConvert(args);
					break;
				case 'h':
					hConvert(args);
					break;
				case 'l':
					lConvert(args);
					break;
				case 'p':
					pConvert(args);
					break;
				default:
					break;


			}
		}
	}

	for (i=0; i<10; i++)
		free(args[i]);
	free(args);

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
				if (inString == 1 && inBrackets == 1)
					fprintf(tempfile, ".");					
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

int getIndexOfChar(char * string, char c) {
	const char *ptr = strchr(string, c);
	int index;

	if (ptr) 
		return index = ptr - string;
	return -1;
}

int removeCharFromString(char * string, char c) {
	int result = getIndexOfChar(string, c);

	if (result >= 0) {
		memmove(&string[result], &string[result + 1], strlen(string) - result);
		return 1;
	}
	return 0;
}