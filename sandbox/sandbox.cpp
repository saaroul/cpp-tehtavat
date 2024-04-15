/*

  Harjoitus 1

  Optimoi sini-funktion käsittely. Älä muuta kääntäjäoptioita.
  Vertaa alkuperäistä ja optimoitua versiota:

  - kuinka paljon enemmän muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  Käännös: gcc sin.c -lm -o sin

*/

#include <stdio.h>
#include <time.h>
#include <math.h>

#define DEG_TO_RAD(A) (A / 57.296)
#define ITERATIONS 1'000'000


int main()
{
	clock_t t1, t2;
	unsigned i, a;
	double val;
	double sin_table[360];
	
	for (a = 0; a < 360; ++a)
	{
		sin_table[a] = sin(DEG_TO_RAD(a));
	}

	t1 = clock();
	for (i = 0; i < ITERATIONS; ++i)
	{
		for (a = 0; a < 360; ++a)
		{
			val = sin_table[a];
			//val = sin(DEG_TO_RAD(a));
		}
	}
	t2 = clock();
	printf("%.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

	return 0;
}
