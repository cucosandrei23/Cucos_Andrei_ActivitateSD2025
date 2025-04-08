#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	//afiseaza toate atributele unei masini
	printf("Id: %d\nNr usi: %d\nPret %.2f\nModel %s\nNumeSofer %s\nserie %c\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++) {
		aux[i] = (*masini)[i];
		aux[i].numeSofer = (*masini)[i].numeSofer;
		aux[i].model = (*masini)[i].model;
	}

	aux[(*nrMasini)] = masinaNoua;
	(*nrMasini)++;
	free(*masini);
	(*masini) = aux;
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
	Masina temp;

	char sep[3] = "\n,";
	char line[100];
	fgets(line, 100, file);
	temp.id = atoi(strtok(line, sep));
	temp.nrUsi = atoi(strtok(NULL, sep));
	temp.pret = atof(strtok(NULL, sep));
	char* buffer = strtok(NULL, sep);
	temp.model = (char*)malloc(strlen(buffer) + 1);
	strcpy(temp.model, buffer);
	buffer = strtok(NULL, sep);
	temp.numeSofer = (char*)malloc(strlen(buffer) + 1);
	strcpy(temp.numeSofer, buffer);
	temp.serie = strtok(NULL, sep)[0];
	return temp;

}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* f = fopen("masini.txt", "r");
	Masina* vectorNou = NULL;
	while (!feof(f)) {
		adaugaMasinaInVector(&vectorNou, nrMasiniCitite, citireMasinaFisier(f));
	}

	fclose(f);
	return vectorNou;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	for (int i = 0; i < (*nrMasini); i++) {
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
	}
	free(*vector);
	(*vector) = NULL;
	*nrMasini = 0;
}

int main() {
	int nrMasini = 0;
	Masina* vector = citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(vector, nrMasini);
	dezalocareVectorMasini(&vector, &nrMasini);
	afisareVectorMasini(vector, nrMasini);
	return 0;
}
