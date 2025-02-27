#include <stdio.h>
#include<stdlib.h>

struct Masina {
	int id;
	int nrKm;
	char* model;
	float pret;
	char tipMotor;
};

struct Masina initializare(int id, int nrKm, const char* model, float pret, char tipMotor) {
	struct Masina m;
	m.id = id;
	m.nrKm = nrKm;
	m.model = (char*)malloc(strlen(model) + 1);
	strcpy(m.model, model);
	m.pret = pret;
	m.tipMotor = tipMotor;
	return m;
}


void afisare(struct Masina m) {
	printf("Id: %d, nr km: %d, model: %s, pret: %f, tip motor: %c", m.id, m.nrKm, m.model, m.pret, m.tipMotor);
}

void modifica_Atribut(struct Masina* m, float noul_pret) {
	//modificarea unui atribut
	if (noul_pret > 0) {
		m->pret = noul_pret;
	}
}

void dezalocare(struct Masina* m) {
	//dezalocare campuri alocate dinamic
	free(m->model);
	m->model = NULL;
}

int main() {
	struct Masina masina;
	masina = initializare(10, 110000, "logan", 10000.00, 'B');
	afisare(masina);

	modifica_Atribut(&masina, 10.00);
	dezalocare(&masina);
	
	return 0;
}