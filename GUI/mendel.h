int totalObjectsCount = 0;
FILE * fileTableData;
char buffer[25];

typedef struct{
  int letterpos;
  char dominant[25];
  char recesive[25];
}dataInformation;

char origin[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','Ñ','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

int getPosition (char letter[1],char * alphabet[25]){
  for (int i =0;i<27;i++){
    if (strcmp(letter,alphabet[i])==0){
      return i;
    }
  }
  return 0;
}

void generateGenotypes(dataInformation initialPool[27],int size,int genotypeAmount,char possibleGenotypes[genotypeAmount][(2 * size-1) + 1] ){
	int n = size-1;
	int letter = 0;

  char caps[size];
  for (int i = 0;i<size;i++){
    caps[i] = origin[initialPool[i].letterpos];
  }

	char genotypes[n][3][2];

	printf("Base genotypes:\n");
	for(letter; letter < n; letter++){
		genotypes[letter][0][0] = caps[letter];
		genotypes[letter][0][1] = caps[letter];


		genotypes[letter][1][0] = caps[letter];
		genotypes[letter][1][1] = tolower(caps[letter]);

		genotypes[letter][2][0] = tolower(caps[letter]);
		genotypes[letter][2][1] = tolower(caps[letter]);


	}



	int genotype = 0;
	int genotypeRepetition = 0;
	int currentGenotype = 0;



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

}

int getLetterPosition(char actualetter[1]){
  char gen = toupper(actualetter);
  for (int i=0;i<27;i++){
    if (gen == origin[i]){
      return i;
      break;
    }
  }
}

dataInformation getGenInformation(dataInformation initialPool[27],int size,int posLetter){
  for (int i=0;i<size;i++){
    dataInformation actualGen = initialPool[i];

    if (actualGen.letterpos == posLetter){
      return actualGen;
    }
  }
}

char  getFenotype(dataInformation initialPool[27],int size,char genotype[size*2],char name[9+26*size] ){
  int i =0;
  int limit = size *2;
  strcpy(name,"FENOTIPO:");
  for (i;i<limit;i=i+2){
    int pos = getLetterPosition(genotype[i]);
    dataInformation gen = getGenInformation(initialPool,size,pos);

    if (genotype[i]==origin[pos]){
      strncat(name,gen.dominant,25);
      strncat(name,",",1);
    }
    else{
      strncat(name,gen.recesive,25);
      strncat(name,",",1);
    }

  }
  return name;
}


void cross(char* progenitor1, char* progenitor2,int n,int tableSide,char row[tableSide][n+1],
	char col[tableSide][n+1],int genes,char offspring[tableSide][tableSide][genes + 1]){
  int debug = 1;

	int lettersPerIteration = tableSide / 2;

	printf("Table side: %i\n", tableSide);
	printf("lettersPerIteration: %i\n\n", lettersPerIteration);


	int counter, iteration, allele, letter;






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
	for(counter = 0; counter < tableSide; counter++){
		row[counter][n] = '\0';
		col[counter][n] = '\0';
	}
	//Show rows and  columns

	if(debug == 1){
		printf("1: %s\n", progenitor1);
		printf("2: %s\n", progenitor2);
		printf("Cross:\n");
		for(counter = 0; counter < tableSide; counter++){
			printf("row: %s\n", row[counter]);
		}
		for(counter = 0; counter < tableSide; counter++){
			printf("column: %s\n", col[counter]);
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


/*Read Files*/
void fillBuffer(int _val) {
	if (strlen(buffer) == 0) {
		char dato= (char)_val;
		char auxiliar[] = {dato,'\0'};
		strcat(buffer,auxiliar);
	} else{
		char dato = (char)_val;
		char auxiliar[]={dato,'\0'};
		strcat(buffer,auxiliar);
	}
}


void cleanBuffer(){
	memset(buffer,'\0',strlen(buffer));
}

int escaner() {
	cleanBuffer();

	int ch;

	while (feof(fileTableData)==0) {

		ch = fgetc(fileTableData);
		if (ch=='\n') {
			return 0;
		}
		if (ch=='-') {
      //printf("%s\n",buffer );
			return 1;
		}
		fillBuffer(ch);
	}
	return 0;
}


void setMatriz(char matrizD[totalObjectsCount][4][25]) {


	int fila = 0;

  int columna = 0;
	int flag=0;
	int accion = escaner();

	while (fila < totalObjectsCount) {
    while (columna < 4) {
	 		if (accion == 1 ) {
        char * data = malloc(25);
	 			strcpy(data,buffer);
        strcpy(matrizD[fila][columna],buffer);
		 	}

		 	columna ++;
		 	accion = escaner();
	 	}
		columna = 0;
	 	fila ++;
	 	accion = escaner();
}
}

void fillTable (char * address,char  matrizD[totalObjectsCount][4][25]){
  fileTableData = fopen("prueba.cvs","r");
  setMatriz(matrizD);
  }



int countObjectsFiles(char * address){
	fileTableData = fopen(address,"r");
	int ch;


	while(feof(fileTableData) == 0) {
		ch = fgetc(fileTableData);
		if (ch == '\n'){
			totalObjectsCount ++;
		}
	}


	fclose(fileTableData);
	return totalObjectsCount;
}
