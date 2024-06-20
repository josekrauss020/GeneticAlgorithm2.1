#include <iostream>
#include<random>
#include <time.h>

int main()
{
	int nCromosomos = 4, nPopulation = 500, numInterations = 1000;
	float mutationRate, selectionPorcentage;
	float popFitness[500];
	double FuncRef[21], FuncCalculada[500], tempRes[21], somatoria = 0;

	double Population[500][5];
	// A ultima casa, vai ser apenas para armazenar puntuações de fitness

	//insere os dados aleatórios da população
	srand(time(NULL));
	for (int i = 0; i < nPopulation; i++)
	{
		for (int j = 0; j < nCromosomos; j++)
		{
			Population[i][j] = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
		}
	}

	// Genera os dados para comparação da equação resultante
	int u = 0;

	for (float x = -1; x < 1.1; x += 0.1)
	{
		printf("[%.2f] \n", x);

		FuncRef[u] = -0.3 + 0.1 * x - 0.5 * x * x + 0.4 * x * x * x;
		u++;
	}

	/*for (int i = 0; i < 20; i++)
	{
		printf("FuncResposta[%d] = [%.2lf] \n", i, FuncResposta[i]);
	}*/

	/*Agora vamos a usar o RMSE avaliar a nossa população,
	lembrando que o RMSE vai nos dar um numero, este numero quanto mais perto de zero melhor*/

	for (int i = 0; i < nPopulation; i++)
	{
		u = 0;
		for (float x = -1; x < 1.1; x+= 0.1)
		{
			tempRes[u] = Population[i][0] + Population[i][1] * x - Population[i][2] * x * x + Population[i][3] * x * x * x;
			//printf("TempRes [%d] = %.3lf \n", u, tempRes[u]);
			u++;
		}
		
		// calculo de RMSE 
		for (int z = 0; z < 21; z++)
		{
			somatoria += (FuncRef[z] - tempRes[z]);
		}
		somatoria = somatoria / 21;//calcula media fitness entre os 20 valores de comparação

		// a index 4 é para armazenar os valores de fitness
		Population[i][4] = sqrt((pow(somatoria, 2) / 4));
		printf("Population[%d][4] = %lf \n",i, Population[i][4]);
	}


}

