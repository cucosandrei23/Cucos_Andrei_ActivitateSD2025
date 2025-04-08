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

typedef struct Nod Nod;

struct Nod {
	Masina info;
	Nod* next;
};

//creare structura pentru un nod dintr-o lista simplu inlantuita

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod*cap) {
	while (cap != NULL) {
		afisareMasina(cap->info);
		cap = cap->next;
	}
}

void adaugaMasinaInLista(Nod**cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* aux = malloc(sizeof(Nod));
	aux->info = masinaNoua;
	aux->next = NULL;
	if ((*cap) == NULL) {
		(*cap) = aux;
	}
	else {
		Nod* temp = (*cap);
		while (temp->next != NULL) {
			temp = temp->next;
		}
		(*cap) = aux;
	}

}

void adaugaLaInceputInLista(Nod **cap, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	Nod* aux = malloc(sizeof(Nod));
	aux->info = masinaNoua;
	if ((*cap) == NULL) {
		(*cap) = aux;
		(*cap)->next = NULL;
	}
	else {
		aux->next = (*cap);
		(*cap) = aux;
	}
}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen("masini.txt", "r");
	Nod* cap = NULL;
	while (!feof(f)) {
		adaugaMasinaInLista(&cap, citireMasinaDinFisier(f));
	}
	fclose("f");
	return cap;
}

void dezalocareListaMasini(Nod ** cap) {
	//sunt dezalocate toate masinile si lista de elemente
	while ((*cap)->next != NULL) {
		Nod* temp = (*cap)->next;
		free((*cap)->info.model);
		free((*cap)->info.numeSofer);
		free((*cap));
		(*cap) = temp;
	}
}

float calculeazaPretMediu(Nod *cap) {
	//calculeaza pretul mediu al masinilor din lista.
	if (cap != NULL) {
		float val = 0;
		int nrMasini = 0;
		while (cap->next != NULL) {
			val += cap->info.pret;
			cap = cap->next;
			nrMasini++;
		}
		return val / nrMasini;
	}
	else {
		return -1;
	}
}

void stergeMasiniDinSeria(Nod **cap, char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	if ((*cap)->info.serie == serieCautata) {
		Nod* aux = (*cap)->next;
		free(aux->info.numeSofer);
		free(aux->info.model);
		free(aux);
		(*cap) = aux;
	}
	
	while ((*cap)->next->next != NULL) {
		if ((*cap)->next->info.serie == serieCautata) {
			free((*cap)->next->info.numeSofer);
			free((*cap)->next->info.model);
			free((*cap)->next);
			(*cap)->next = (*cap)->next->next;
		}
		(*cap) = (*cap)->next;
	}


}

float calculeazaPretulMasinilorUnuiSofer(/*lista masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {


	return 0;
}
