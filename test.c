#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, char *arcgv[]){
	int n = 5;

	int letter = 0;
	char caps[5] = {'A','B','C','D','E'};

	char genotypes[n][3][2];

	printf("Base genotypes:\n");
	for(letter; letter < n; letter++){
		genotypes[letter][0][0] = caps[letter];
		genotypes[letter][0][1] = caps[letter];
		

		genotypes[letter][1][0] = caps[letter];
		genotypes[letter][1][1] = tolower(caps[letter]);
		
		genotypes[letter][2][0] = tolower(caps[letter]);
		genotypes[letter][2][1] = tolower(caps[letter]);
		
		printf("%c", genotypes[letter][0][0]);
		printf("%c\n", genotypes[letter][0][1]);

		printf("%c", genotypes[letter][1][0]);
		printf("%c\n", genotypes[letter][1][1]);

		printf("%c", genotypes[letter][2][0]);
		printf("%c\n", genotypes[letter][2][1]);
	}

	printf("Mixed Genotypes:\n");

	int genotype = 0;
	int genotypeRepetition = 0;
	int currentGenotype = 0;
	int genotypeAmount = pow(3, n);
	printf("Mixed Genotype Amount: %i\n", genotypeAmount);
	char possibleGenotypes[genotypeAmount][(2 * n) + 1];

	for(letter = 0; letter < n; letter++){
		currentGenotype = 0;
		while(currentGenotype < genotypeAmount){
			for(genotypeRepetition = 0; genotypeRepetition < pow(3, (n - (letter + 1))); genotypeRepetition++){
				possibleGenotypes[currentGenotype][(letter * 2)] = genotypes[letter][genotype][0];
				possibleGenotypes[currentGenotype][(letter * 2) + 1] = genotypes[letter][genotype][1];
				currentGenotype++;
			}
			genotype++;
			if(genotype == 3){
				genotype = 0;
			}
		}
	}

	printf("Genotypes: \n");
	for(currentGenotype = 0; currentGenotype < genotypeAmount; currentGenotype++){
		possibleGenotypes[currentGenotype][(n*2)] = '\0';
		printf("%s\n", possibleGenotypes[currentGenotype]);
	}
}