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
	printf("id: %d\n", masina.id);
	printf("nrUsi: %d\n", masina.nrUsi);
	printf("float: %f\n", masina.pret);
	printf("model: %s\n", masina.model);
	printf("numeSofer: %s\n", masina.numeSofer);
	printf("serie: %c\n\n", masina.serie);

}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
	Masina* aux = (Masina*)malloc(sizeof(Masina*) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++) {
		aux[i] = (*masini)[i];
	}
	(*nrMasini)++;
	aux[(*nrMasini)] = masinaNoua;

	free(*masini);
	(*masini) = aux;
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
	Masina m;
	char sep[3] = ",\n";
	char* line[101];
	fgets(line, 100, file);
	m.id=atoi(strtok(line, sep));
	m.nrUsi = atoi(strtok(NULL, sep));
	m.pret = atof(strtok(NULL, sep));

	char* buffer = strtok(NULL, sep);
	m.model = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy_s(m.model, (strlen(buffer) + 1), buffer);

	buffer = strtok(NULL, sep);
	m.numeSofer = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy_s(m.numeSofer, (strlen(buffer) + 1), buffer);
	
	buffer = strtok(NULL, sep);
	m.serie = buffer[0];
	
	return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
	Masina* masini = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return masini;

}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
}

int main() {
	int nr = 0;
	Masina* masini = NULL;

	return 0;
}