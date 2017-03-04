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


int main(int argc, char *argv[]) {

	FILE *fp = fopen("config", "r");
	FILE *htmlFile = fopen("index.html", "w");
	char buffer[255];

	while (fgets(buffer, 255, fp) != NULL) {
		printf("%s", buffer);
	}

	fclose(fp);
	return 0;
}
