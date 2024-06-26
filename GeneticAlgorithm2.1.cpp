#include <iostream>
#include <random>
#include <time.h>
#include <Windows.h>

#define POPULATION_SIZE 500
#define INTERATIONS 6000
#define taxaElitismo 0.01

int main()
{
	int nCromosomos = 4, pai1, pai2, crossOver[4], crossOverInv[4];
	double FuncRef[21], tempRes[21], somatoria = 0, aleat1, aleat2;
	double melhorRMSE;

	double cumulativeProb[500], totalFitness = 0, randValue;
	double Population[POPULATION_SIZE][5], NextPopulation[POPULATION_SIZE][4];
	// A ultima casa, vai ser apenas para armazenar puntuações de fitness

	srand(time(NULL));

	// insere os dados aleatórios da população
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		for (int j = 0; j < nCromosomos; j++)
		{
			Population[i][j] = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
			//Population[i][j] = ((double)rand() / RAND_MAX) * 100;
		}
	}

	// Genera os dados para comparação da equação resultante
	int u = 0;
	for (float x = -1; x < 1.1; x += 0.1)
	{
		FuncRef[u] = -0.3 + 0.1 * x - 0.5 * x * x + 0.4 * x * x * x;
		u++;
	}
	// finaliza com u=20 mas como começa em u=0, temos 21 ciclos

	for (int w = 0; w < INTERATIONS; w++) // loop das interações
	{
		/*Agora vamos a usar o RMSE avaliar a nossa população,
		lembrando que o RMSE vai nos dar um numero, este numero quanto mais perto de zero melhor*/
		for (int i = 0; i < POPULATION_SIZE; i++)
		{
			u = 0;
			somatoria = 0; // Resetar somatoria para cada cromossomo
			for (float x = -1; x < 1.1; x += 0.1)
			{
				tempRes[u] = Population[i][0] + Population[i][1] * x + Population[i][2] * x * x + Population[i][3] * x * x * x;
				// printf("TempRes [%d] = %.3lf \n", u, tempRes[u]);
				u++;
			}

			// calculo de RMSE
			for (int z = 0; z < 21; z++)
			{
				somatoria += pow(FuncRef[z] - tempRes[z], 2);
			}
			double rmse = sqrt(somatoria / 21.0);

			// a index 4 é para armazenar os valores de fitness
			Population[i][4] = rmse;
			
			// printf("Population[%d][4] = %lf \n",i, Population[i][4]);
			
		}

		if (w > 0) 
		{
			melhorRMSE = 1;
			int indice = 0;
			for (int i = 0; i < POPULATION_SIZE; i++)
			{
				if (Population[i][4] < melhorRMSE)
				{
					melhorRMSE = Population[i][4];
					indice = i;
				}
			}
			printf("Geracao[%d] = [%.4lf][%.4lf][%.4lf][%.4lf][%.4lf]\n", w ,Population[indice][0], Population[indice][1], Population[indice][2], Population[indice][3], Population[indice][4]);
		}

		

		int contador = 0;
		// ciclo para as seguintes gerações
		while (contador < POPULATION_SIZE)
		{
			pai1 = 0;
			pai2 = 0;
			while (pai1 == pai2) // evita valores repetidos
			{
				// Procura o primeiro pai
				pai1 = rand() % POPULATION_SIZE;
				pai2 = rand() % POPULATION_SIZE;
				
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
			// gera filho 1
			// este é outro formato de if/else, não se assuste!
			//                              Pergunta               True                  False
			NextPopulation[contador][0] = crossOver[0] == 1 ? Population[pai1][0] : Population[pai2][0];
			NextPopulation[contador][1] = crossOver[1] == 1 ? Population[pai1][1] : Population[pai2][1];
			NextPopulation[contador][2] = crossOver[2] == 1 ? Population[pai1][2] : Population[pai2][2];
			NextPopulation[contador][3] = crossOver[3] == 1 ? Population[pai1][3] : Population[pai2][3];

			// gera filho 2
			NextPopulation[contador + 1][0] = crossOverInv[0] == 1 ? Population[pai1][0] : Population[pai2][0];
			NextPopulation[contador + 1][1] = crossOverInv[1] == 1 ? Population[pai1][1] : Population[pai2][1];
			NextPopulation[contador + 1][2] = crossOverInv[2] == 1 ? Population[pai1][2] : Population[pai2][2];
			NextPopulation[contador + 1][3] = crossOverInv[3] == 1 ? Population[pai1][3] : Population[pai2][3];

			// Sorteio de mutação
			int aleatMutationPoint = rand() % 3;
			int decideOcorrenciaMutacao = rand() % 10;
			if (decideOcorrenciaMutacao == 1 ) // 10% de chance de mutação
			{
				aleat1 = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;
				aleat2 = 2.0 * ((float)rand() / (float)RAND_MAX) - 1.0;

				NextPopulation[contador][aleatMutationPoint] += aleat1;
				NextPopulation[contador + 1][aleatMutationPoint] += aleat2;
			}

			int numElite = (int)(taxaElitismo * POPULATION_SIZE);

			for (int i = 0; i < numElite; i++)
			{
				int melhor = 0;

				for (int j = 1; j < POPULATION_SIZE; j++)
				{
					if (Population[j][4] < Population[melhor][4])
					{
						melhor = j;
					}
				}

				for (int k = 0; k < nCromosomos; k++)
				{
					Population[i][k] = NextPopulation[melhor][k];
				}
			}

			contador += 2;
		}

		// copiando a proxima geração para gerar o loop seguinte
		for (int i = 0; i < POPULATION_SIZE; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				Population[i][j] = NextPopulation[i][j];
			}
		}
	}



	/*for (int h = 0; h < POPULATION_SIZE; h++)
	{
		printf("Population[%d] = [%.4lf][%.4lf][%.4lf][%.4lf][%.4lf][%.4lf]\n", h, Population[h][0], Population[h][1], Population[h][2], Population[h][3], Population[h][4], Population[h][5]);
	}*/

	melhorRMSE = 1;
	int indice = 0;
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		if (Population[i][4] < melhorRMSE)
		{
			melhorRMSE = Population[i][4];
			indice = i;
		}
	}

	printf("melhor avaliado[%d]: %.5lf\n", indice, melhorRMSE);
	printf("%.4lf  %.4lfX  %.4lfX^2  %.4lfX^3\n", Population[indice][0], Population[indice][1], Population[indice][2], Population[indice][3]);
}
