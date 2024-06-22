#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>

#define POPULATION_SIZE 500
#define INTERATIONS 1000

int main()
{
	int nCromosomos = 4, pai1, pai2, crossOver[4], crossOverInv[4];
	float mutationRate, selectionPorcentage;
	float popFitness[500];
	double FuncRef[21], FuncCalculada[500], tempRes[21], somatoria = 0;

	double cumulativeProb[500], totalFitness = 0, randValue;
	double Population[POPULATION_SIZE][6], NextPopulation[POPULATION_SIZE][6];
	// A ultima casa, vai ser apenas para armazenar puntuações de fitness

	// insere os dados aleatórios da população
	srand(time(NULL));

	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < nCromosomos; j++)
		{
			Population[i][j] = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
			// printf("Population[%d][%d] = %.4lf \n", i, j, Population[i][j]);
		}
	}

	// Genera os dados para comparação da equação resultante
	int u = 0;
	for (float x = -1; x < 1.1; x += 0.1)
	{
		/*printf("x = [%.2f] \n", x);
		printf("u = [%.2d] \n", u);*/

		FuncRef[u] = -0.3 + 0.1 * x - 0.5 * x * x + 0.4 * x * x * x;
		u++;
	}
	// finaliza com u=20 mas como começa em u=0, temos 21 ciclos

	for (int w = 0; w < INTERATIONS; w++)
	{
		/*Agora vamos a usar o RMSE avaliar a nossa população,
		lembrando que o RMSE vai nos dar um numero, este numero quanto mais perto de zero melhor*/
		for (int i = 0; i < POPULATION_SIZE; i++)
		{
			u = 0;
			for (float x = -1; x < 1.1; x += 0.1)
			{
				tempRes[u] = Population[i][0] + Population[i][1] * x - Population[i][2] * x * x + Population[i][3] * x * x * x;
				// printf("TempRes [%d] = %.3lf \n", u, tempRes[u]);
				u++;
			}

			// calculo de RMSE
			for (int z = 0; z < 21; z++)
			{
				somatoria += (FuncRef[z] - tempRes[z]);
			}
			somatoria = somatoria / 21;
			// calcula media fitness entre os 21 valores de comparação

			// a index 4 é para armazenar os valores de fitness
			Population[i][4] = sqrt((pow(somatoria, 2) / POPULATION_SIZE));
			// printf("Population[%d][4] = %lf \n",i, Population[i][4]);
			Population[i][5] = 1 - Population[i][4];
			// printf("Population[%d][5] = %lf \n", i, Population[i][5]);

			// aqui temos a somatoria dos valores de fitness para utilizar no sorteio via roleta viciada
			totalFitness += Population[i][5];
		}

		cumulativeProb[0] = Population[0][5] / totalFitness;
		for (int i = 1; i < POPULATION_SIZE; i++)
		{
			cumulativeProb[i] = cumulativeProb[i - 1] + (Population[i][5] / totalFitness);
		}

		int contador = 0;
		// ciclo para as seguintes gerações
		while (contador < POPULATION_SIZE)
		{

			// Procura o primeiro pai
			randValue = (double)rand() / RAND_MAX;
			for (int i = 0; i < POPULATION_SIZE; i++)
			{
				if (randValue <= cumulativeProb[i])
				{
					pai1 = i;
					break;
				}
			}

			
			randValue = (double)rand() / RAND_MAX;
			for (int i = 0; i < POPULATION_SIZE; i++)
			{
				if (randValue <= cumulativeProb[i])
				{
					pai2 = i;
					break;
				}
			}
			/*printf("Pai1 = %d \nPai2 = %d\n", pai1, pai2);
			printf("================\n");*/

			// CrossOver uniforme
			/* vamos gerar 2 filhos, a forma de distribuição de genes vai ser sorteando 4 numeros entre 1 e 2 onde cada numero
			vai indicar qual gene vai preservar
				filho1                         filho2
			[1]     [2]   [2]  [1]         [2]     [1]   [1]  [2]
			[pai1][pai2][pai2][pai1]   <-> [pai2][pai1][pai1][pai2]  */
			for (int i = 0; i < 4; i++)
			{
				crossOver[i] = rand() % 2 + 1; // sorteia numeros entre 1 e 2
				if (crossOver[i] == 1)
				{
					crossOverInv[i] = 2;
				}
				else if (crossOver[i] == 2)
				{
					crossOverInv[i] = 1;
				}
			}

			// Fazendo o cruzamento
			if (crossOver[0] == 1)
			{
				NextPopulation[contador][0] = Population[pai1][0];
			}
			else
			{
				NextPopulation[contador][0] = Population[pai2][0];
			}
			if (crossOver[0] == 1)
			{
				NextPopulation[contador][1] = Population[pai1][1];
			}
			else
			{
				NextPopulation[contador][1] = Population[pai2][1];
			}
			if (crossOver[0] == 1)
			{
				NextPopulation[contador][2] = Population[pai1][2];
			}
			else
			{
				NextPopulation[contador][2] = Population[pai2][2];
			}
			if (crossOver[0] == 1)
			{
				NextPopulation[contador][3] = Population[pai1][3];
			}
			else
			{
				NextPopulation[contador][3] = Population[pai2][3];
			}

			if (crossOverInv[0] == 1)
			{
				NextPopulation[contador + 1][0] = Population[pai1][0];
			}
			else
			{
				NextPopulation[contador + 1][0] = Population[pai2][0];
			}
			if (crossOverInv[0] == 1)
			{
				NextPopulation[contador + 1][1] = Population[pai1][1];
			}
			else
			{
				NextPopulation[contador + 1][1] = Population[pai2][1];
			}
			if (crossOverInv[0] == 1)
			{
				NextPopulation[contador + 1][2] = Population[pai1][2];
			}
			else
			{
				NextPopulation[contador + 1][2] = Population[pai2][2];
			}
			if (crossOverInv[0] == 1)
			{
				NextPopulation[contador + 1][3] = Population[pai1][3];
			}
			else
			{
				NextPopulation[contador + 1][3] = Population[pai2][3];
			}

			// zerando as avaliações RMSE
			if (w < 999)
			{
				NextPopulation[contador][4] = 0;
				NextPopulation[contador][5] = 0;
				NextPopulation[contador + 1][4] = 0;
				NextPopulation[contador + 1][5] = 0;
			}

				contador += 2;
		}
		// copiando a proxima geração para gerar o loop seguinte
		for (int i = 0; i < POPULATION_SIZE; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				Population[i][j] = NextPopulation[i][j];
			}
		}
	}
	
	
	
	int melhorIndice = 1;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (Population[i][4] < melhorIndice) {
			melhorIndice = Population[i][4];
		}
	}
	printf("Population[400][4] = %.4lf\n", Population[400][4]);
	printf("melhor avaliado: %d\n", melhorIndice);
	printf("%.4lf + %.4lfX - %.4lfX^2 + %.4lfX^3\n", Population[melhorIndice][3], Population[melhorIndice][2], Population[melhorIndice][1], Population[melhorIndice][0]);
}
