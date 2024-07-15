#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <string.h>
#define Coder 999

typedef enum {
	MONDAY = 1,
	TUESDAY,
	WEDNESDAY
} Week_t;

typedef struct { 
	char name[20];
	int age;
	float height;
} Human;

int main(void) {
	printf("%d\n", Coder);
	Human human;
	Human *pHuman;
	pHuman = &human;
	
	strcpy(human.name, "coderyxy");
	human.age = 18;
	human.height = 1.88;
	
	strcpy(pHuman->name, "coderyxy");
	pHuman->age = 18;
	pHuman->height = 1.88;
	
	Week_t week;
	week = MONDAY;
	week = (Week_t)1;
}
