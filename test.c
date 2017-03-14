#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int n = 2;
int debug = 1;
char caps[30] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
typedef struct{
	char genotype;
}offspring;

void cross(char* progenitor1, char* progenitor2){
	int tableSide = pow(2, n);
	int lettersPerIteration = tableSide / 2;

	printf("Table side: %i\n", tableSide);
	printf("lettersPerIteration: %i\n\n", lettersPerIteration);

	char row[tableSide][n];
	char col[tableSide][n];
	int counter, iteration, allele, letter;

	int genes = (2 * n);
	char offspring[tableSide][tableSide][genes + 1];


	//Create rows and columns
	for(letter = 0; letter < n; letter++){
		printf("Letter: %i\n", letter);
		iteration = 0;
		allele = 0;
		while(iteration < tableSide){
			printf("\tIteration: %i\n", iteration);
			printf("\allele: %i\n", allele);
			//counter = 0;
			for(counter = 0; counter < lettersPerIteration; counter++){//while(counter < lettersPerIteration){
				printf("\t\tCounter: %i\n", counter);
				row[iteration][letter] = progenitor1[(letter * 2) + (allele % 2)];
				col[iteration][letter] = progenitor2[(letter * 2) + (allele % 2)];
				iteration++;
				//counter++;
			}
			allele++;
		}
		lettersPerIteration /= 2;
	}
	//Show rows and  columns
	if(debug == 1){
		printf("1: %s\n", progenitor1);
		printf("2: %s\n", progenitor2);
		printf("Cross:\n");
		for(counter = 0; counter < tableSide; counter++){
			printf("row: ");
			for(allele = 0; allele < n; allele++){
				printf("%c", row[counter][allele]);
			}
			putchar('\n');
		}
		for(counter = 0; counter < tableSide; counter++){
			printf("column: ");
			for(allele = 0; allele < n; allele++){
				printf("%c", col[counter][allele]);
			}
			putchar('\n');
		}
	}

	//Create offspring
	for(counter = 0; counter < tableSide; counter++){
		for(allele = 0; allele <tableSide; allele++){
			for(letter = 0; letter < n; letter++){
				offspring[allele][counter][2 * letter] = row[counter][letter];
				offspring[allele][counter][2 * letter + 1] = col[allele][letter]; 
			}
			offspring[allele][counter][genes] = '\0';
		}
	}

	//Show offspring
	if(debug == 1){
		for(counter = 0; counter < tableSide; counter++){
			for(allele = 0; allele <tableSide; allele++){
				//for(letter = 0; letter < n*2; letter++){
				//	putchar(offspring[counter][allele][letter]);
				//}
				printf("%s", offspring[counter][allele]);
				putchar(' ');
			}
			putchar('\n');
		}
	}
	
	char expected[16][4] = {"ABCD", "AbCD", "aBCD", "abCD", "ABCd", "AbCd", "aBCd", "abCd", "ABcD", "AbcD", "aBcD","abcD", "ABcd", "Abcd", "aBcd", "abcd"};
	
}

int main(int argc, char *arcgv[]){
	int letter = 0;
	char genotypes[n][3][2];

	if(debug == 1) { printf("Base genotypes:\n"); }
	for(letter; letter < n; letter++){
		genotypes[letter][0][0] = caps[letter];
		genotypes[letter][0][1] = caps[letter];
		
		genotypes[letter][1][0] = caps[letter];
		genotypes[letter][1][1] = tolower(caps[letter]);
		
		genotypes[letter][2][0] = tolower(caps[letter]);
		genotypes[letter][2][1] = tolower(caps[letter]);
		
		if(debug == 1) {
			printf("%c", genotypes[letter][0][0]);
			printf("%c\n", genotypes[letter][0][1]);

			printf("%c", genotypes[letter][1][0]);
			printf("%c\n", genotypes[letter][1][1]);

			printf("%c", genotypes[letter][2][0]);
			printf("%c\n", genotypes[letter][2][1]);
		}
	}

	//printf("Mixed Genotypes:\n");

	int genotype = 0;
	int genotypeRepetition = 0;
	int currentGenotype = 0;
	int genotypeAmount = pow(3, n);
	//printf("Mixed Genotype Amount: %i\n", genotypeAmount);
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


	cross("AaBbCc", "AaBbCc");
}