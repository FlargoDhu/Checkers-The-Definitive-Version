// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	time_t t;
	srand(time(&t));
	Init();
	printf("-------------------------------Checker Game Bot---------------------------------\n\n");
	printf("Author - : Pawel Olejnik\n\n");
	StartGame();
	return 0;
}
