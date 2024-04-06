#include "MyForm.h"
#include <iostream>

struct Spis2 {
	int info;
	Spis2* next, * prev;
} *Begin, * end, * t;


void CreateSpis2(Spis2**, Spis2**, int);
void AddSpis2(int, Spis2**, Spis2**, int);
void ViewSpis2(int, Spis2*);
void DelAll(Spis2**);

