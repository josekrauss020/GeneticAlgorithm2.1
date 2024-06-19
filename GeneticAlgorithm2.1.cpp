#include <iostream>
#include<random>
#include <time.h>

int main()
{
	srand(time(NULL));
	int nCromosomos = 4, nPopulation = 500, numInterations = 1000;
	float mutationRate, selectionPorcentage;
	double FuncResposta[21];

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

	// Genera os dados para comparação da equação resposta
	int u = 0;
	for (float x = -1; x < 1.1; x += 0.1)
	{
		printf("[%.2f] \n", x);

		FuncResposta[u] = -0.3 + 0.1 * x - 0.5 * x * x + 0.4 * x * x * x;
		u++;
	}

	/*for (int i = 0; i < 20; i++)
	{
		printf("FuncResposta[%d] = [%.2lf] \n", i, FuncResposta[i]);
	}*/






}

