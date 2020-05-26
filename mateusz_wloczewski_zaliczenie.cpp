#include <iostream>
#include <time.h>

#include "Kontroler.h"

int main() {
	srand(time(NULL));
	Kontroler kontroler;
	kontroler.Start();
	return 0;
}