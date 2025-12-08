#include <stdio.h>
#include <stdlib.h>

arbre* min(arbre* racine) {
    if (racine == NULL) return NULL;
    arbre* temp = racine;
    while (temp->gauche != NULL) temp = temp->gauche;
    return temp;
}

arbre* max(arbre* racine) {
    if (racine == NULL){
    	return NULL;
	}
    arbre* temp = racine;
    while (temp->droite != NULL){
    	temp = temp->droite; 
	}
    return temp;
}

float somme(arbre* racine) {
    if (racine == NULL){
    	return 0;
	}
    return racine->val.temp + somme(racine->gauche) + somme(racine->droite);
}

void compter_alertes(arbre* A, int* a1, int* a2, int* a3) {
    if (!A){
    	return;
    }
    compter_alertes(A->gauche, a1, a2, a3);
    if (A->val.niv_alerte == 1){
    	(*a1)++;
	}
    else if (A->val.niv_alerte == 2){
    	(*a2)++;
	}
    else if (A->val.niv_alerte == 3){
    	(*a3)++;
	}
    compter_alertes(A->droite, a1, a2, a3);
}

// Générer le rapport à partir de l'arbre
void generer_rapport(mesure journal[], arbre* A, int n, char *nom_fichier) {
    if (A == NULL || n == 0) {
        printf("Aucune mesure. Rapport non généré.\n");
        return;
    }

    FILE *f = fopen(nom_fichier,"w");
    if (!f) {
        printf("Impossible de créer %s\n", nom_fichier);
        return;
    }
    for (int i = 0; i < n; i++){
        fprintf(f,"%s | %.2f | %d\n",journal[i].date,journal[i].temp,journal[i].niv_alerte);
    }

    fprintf(f, "\n");

    float min_val = min(A)->val.temp;
    float max_val = max(A)->val.temp;
    float somme_val = somme(A);
    float moyenne = somme_val / n;

    int a1 = 0, a2 = 0, a3 = 0;
    compter_alertes(A, &a1, &a2, &a3);

    
    fprintf(f, "Température minimale : %.2f°C\n", min_val);
    fprintf(f, "Température maximale : %.2f°C\n", max_val);
    fprintf(f, "Température moyenne : %.2f°C\n", moyenne);
    fprintf(f, "Nombre d'alertes : niv1=%d niv2=%d niv3=%d\n", a1, a2, a3);

    fclose(f);
}
