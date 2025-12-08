//arbre
#include<stdio.h>
#include<stlib.h>
typedef struct arbre{
	mesure val;
	struct arbre *gauche;
	struct arbre *droite;
} arbre;
arbre* nouv_arbre(mesure m){
	arbre* nouvar=(arbre*)malloc(sizeof(arbre));
	nouvar->val=m;
    nouvar->gauche=NULL;
    nouvar->droite=NULL;
    return nouvar;
}
arbre* inserer(arbre* racine,mesure m){
    if (racine==NULL){
        return nouv_arbre(m);
    }
    if (m.temp<racine->val.temp){
        racine->gauche=inserer(racine->gauche,m);
    } else if (m.temp>racine->val.temp) {
        racine->droite=inserer(racine->droite,m);
    }
    return racine;
}
void inorder(arbre* racine){
	if (racine==NULL){
		return;
	}
	inorder(racine->gauche);
	printf("[%s] Temperature: %.2f°C ---- Alerte niveau : %d ---\n",racine->val.date,racine->val.temp,racine->val.niv_alerte);
	inorder(racine->droite);
}

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

void liberer(arbre* racine) {
    if (racine == NULL){
		return;
	}
    liberer(racine->gauche);
    liberer(racine->droite);
    free(racine);
}
