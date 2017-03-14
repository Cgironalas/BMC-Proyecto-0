#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int n = 2;
int alleles;
int offspringAmount;

//progenitor1 [Aa]
//progenitor2 [Cc]
	//		A 		a
	//C 	AC 		aC
	//c 	Ac 		ac

//progenitor1 [AaBb]
//progenitor2 [CcDd]
	// 		AB 		Ab 		aB 		ab
	//CD 	ABCD 	AbCD 	aBCD	abCD
	//Cd 	ABCd 	AbCd 	aBCd 	abCd
	//cD 	ABcD 	AbcD 	aBcD 	abcD
	//cd 	ABcd 	Abcd 	aBcd 	abcd
void cross(char* progenitor1, char* progenitor2){
	int tableSide = pow(2, n);
	int value = tableSide / 2;

	char row[tableSide][n];
	char col[tableSide][n];
	int counter, iteration, counter1, letter;

	for(letter = 0; letter < n; letter++){
		iteration = 0;
		counter1 = 0;
		while(iteration < tableSide){
			counter = 0;
			while(counter < value){
				row[iteration][letter] = progenitor1[(letter * 2) + counter1];
				col[iteration][letter] = progenitor2[(letter * 2) + counter1];
				iteration++;
				counter++;
			}
			counter1++;
			if(counter1 == n){
				counter1 = 0;
			}
		}
		value /= 2;	
	}


	printf("1: %s\n", progenitor1);
	printf("2: %s\n", progenitor2);
	printf("Cross:\n");
	for(counter = 0; counter < tableSide; counter++){
		printf("row: ");
		printf("%c", row[counter][0]);
		printf("%c\n", row[counter][1]);
	}
	for(counter = 0; counter < tableSide; counter++){
		printf("column: ");
		printf("%c", col[counter][0]);
		printf("%c\n", col[counter][1]);
	}

	char offspring[tableSide][tableSide][2 * n];
	for(counter = 0; counter < tableSide; counter++){
		for(counter1 = 0; counter1 <tableSide; counter1++){
			for(letter = 0; letter < n; letter++){
				offspring[counter][counter1][letter] = '1';
				offspring[counter][counter1][n + letter] ='1'; 
			}
		}
	}
	/*
	alleles = 2 * n;
	offspringAmount = pow(4, n);

	int letter = 0;
	int currentOffspring, allele, prog1, prog2;
	char offspring[offspringAmount][alleles];
	
	int tableSide = pow(2, n);

	//for(letter = 0; letter < n; letter++){
		currentOffspring = 0;
		while(currentOffspring < offspringAmount){
			for(allele = 0; allele < n; allele++){
				//value = pow(2, n - allele);
				printf("%i\n", value);
				printf("%i\n", currentOffspring / tableSide);
				prog1 = (2 * allele) + currentOffspring % 2;
				prog2 = (2 * allele) + currentOffspring / tableSide;

				offspring[currentOffspring][allele] = progenitor1[prog1];
				offspring[currentOffspring][n + allele] = progenitor2[prog2];

				printf("1-%i: %i - %c   ", allele, prog1, progenitor1[prog1]);
				printf("2-%i: %i - %c   ;", allele, prog2, progenitor2[prog2]);
			}
			putchar('\n');
			currentOffspring++;
		}*/
	//}
	char expected[16][4] = {"ABCD", "AbCD", "aBCD", "abCD", "ABCd", "AbCd", "aBCd", "abCd", "ABcD", "AbcD", "aBcD","abcD", "ABcd", "Abcd", "aBcd", "abcd"};
	/*
	for(currentOffspring = 0; currentOffspring < offspringAmount; currentOffspring++){
		printf("%c", expected[currentOffspring][0]);
		printf("%c - ", expected[currentOffspring][1]);
		//printf("%c", expected[currentOffspring][2]);
		//printf("%c - ", expected[currentOffspring][3]);

		printf("%c", offspring[currentOffspring][0]);
		printf("%c\n", offspring[currentOffspring][1]);
		//printf("%c", offspring[currentOffspring][2]);
		//printf("%c\n", offspring[currentOffspring][3]); 
	}*/
}

int main(int argc, char *arcgv[]){
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


	cross("AaBb", "CcDd");	
}