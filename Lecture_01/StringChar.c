#include <stdio.h>
#include <string.h>

int main(){
	char *names[5] = {"Pernik","Dupnitsa","Turnovo","Mezdra"};
	printf("%s\n", names[1]);
	printf("%c\n", names[2][3]);
	printf("%c\n", *names[1]);
	printf("%c\n", **names);
	printf("%s\n", *(names+3));
	printf("%s\n", (*names)+2);
}