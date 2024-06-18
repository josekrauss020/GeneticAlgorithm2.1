#include <iostream>
#include<random>
#include <time.h>

int main()
{
	srand(time(NULL));
	int nCromosomos = 4, nPopulation = 500, numInterations = 100;
	float mutationRate, selectionPorcentage;

	float Population[500][5];
	// A ultima casa, vai ser apenas para armazenar puntuações de fitness

	//insere os dados aleatórios da população
	for (int i = 0; i < nPopulation; i++)
	{
		for (int j = 0; j < nCromosomos; j++)
		{
			Population[i][j] = (float)rand() / (float)RAND_MAX;
		}
	}

	






}

