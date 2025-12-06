#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// structure de mesures //
typedef struct {
    float temp; // température mesurée
    char date[100]; // date et heure
    int niv_alerte; // 0 = normal, 1 = niv1, 2 = niv2, 3 = niv3
} mesure;
// fonction qui lit ces valeurs depuis le fichier config//
void lire_config(const char *fichier,int *seuil_min,int *seuil_max,int *consec){
	FILE *f = fopen(fichier, "r");
	if (f == NULL){
        printf("erreur");
    }
    fscanf(f,"%d%d%d",seuil_min,seuil_max,consec);
    fclose(f);
}
// fonction qui genere une temperature entre 0 et 50 dune facon aleatoire//
float genererTemperature(){
    return (float)rand() / ((float)RAND_MAX/50.0);
}
//fonction pour obtenir la date/heure actuelle//
void date(char *date_str) {
    time_t now = time(NULL);
    strftime(date_str, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
}
//pour vérifier l'alerte :normal,dépassement léger niv1,dépassement modéré niv2,dépassement critique niv3//
int verif_alerte(float x,int seuil_min,int seuil_max){
	if (x>=seuil_min && x<=seuil_max){
		return 0; // normal
	}
	float d;
	if (x> seuil_max){
		d=x-seuil_max;
	}else{
		d=seuil_min-x;
	}
		
	if (d<5){
		return 1; // dépassement léger niv1
	}
	if (d<10){
		return 2; // dépassement modéré niv2
	}
	if(d>=10){
		return 3;  // dépassement critique niv3
	}
}
//affichage//
void afficher_mesure(mesure m, int compteur, int consec) {
	if (compteur>=consec && m.niv_alerte !=0){
		printf(" [%s] Temperature: %.2f°C ---- Alerte niveau : %d --- DECLENCHEMENT DE L'ALARME \n", m.date,m.temp,m.niv_alerte);
			
	}else if(m.niv_alerte !=0) {
		printf(" [%s] Temperature: %.2f°C ---- Alerte niveau : %d (consécutives=%d) --- alarme en attente \n", m.date,m.temp,m.niv_alerte,compteur);			
	}else{
		printf("[%s] Temperature: %.2f°C --- Normal \n", m.date, m.temp);
	}
}
//fonction pour générer le nom de fichier avec la date//
void nom_fichier_rapport(char *nom_fichier) {
    char d[100];
    date(d);
    sprintf(nom_fichier, "rapport_%.10s.txt", d);
}

//le rapport//
void generer_rapport_liste(mesure journal[], int n, char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "w");
    if (!f) {
        printf("Impossible de créer %s\n", nom_fichier);
        return;
    }
    float min = journal[0].temp;
    float max = journal[0].temp;
    float somme = 0;
    int a1 = 0, a2 = 0, a3 = 0;
    int i=0;
    for ( i =0; i < n; i++) {
        mesure m = journal[i];
        fprintf(f, "%s | %.2f | %d\n", m.date, m.temp, m.niv_alerte);
        if (m.temp < min) {
            min = m.temp;
        }
        if (m.temp > max) {
            max = m.temp;
        }
        somme += m.temp;
		if (m.niv_alerte == 1) {
            a1++;
        } else if (m.niv_alerte == 2) {
            a2++;
        } else if (m.niv_alerte == 3) {
            a3++;
        }
    }
    fprintf(f, "\nTempérature minimale : %.2f°C\n", min);
    fprintf(f, "Température maximale : %.2f°C\n", max);
    fprintf(f, "Température moyenne : %.2f°C\n", somme / n);
    fprintf(f, "Nombre d'alertes : niv1=%d, niv2=%d, niv3=%d\n", a1, a2, a3);
    fclose(f);
    printf("Rapport généré dans %s\n", nom_fichier);
}
//fonction qui ecrit un enregistrement dans le fichier journaling//
void ecrire_journal(mesure m ){
	FILE *f=fopen("journal.txt","a");
	if (f==NULL){
		printf("il est impossible d'ouvrir le fichier");
	}
	else {
		fprintf(f,"%s | %.2f | %d\n", m.date, m.temp, m.niv_alerte);
		fclose(f);
	}
}


int main(){
	int seuil_min , seuil_max, consec;
	lire_config("config.txt",&seuil_min,&seuil_max,&consec); // fonction qui lit ces valeurs depuis le fichier config//
	mesure journal[100];
	int compteur=0;
	int i=0;
	printf("MONITORING DE TEMPERATURE \n");
	char choix='o';
	printf("Appuyer sur ENTREE pour generer la premiere mesure \n");
	getchar();
	while (choix=='o' || choix == 'O'){
		mesure m;
		m.temp= genererTemperature();// fonction qui genere une temperature entre 0 et 50 dune facon aleatoire//
		date(m.date); //fonction pour obtenir la date/heure actuelle//
		m.niv_alerte=verif_alerte(m.temp,seuil_min,seuil_max);//pour vérifier l'alerte :normal,dépassement léger niv1,dépassement modéré niv2,dépassement critique niv3			//
		if (m.niv_alerte !=0){
			compteur++;
		}else{
			compteur=0;
		}	
		//affichage//
		afficher_mesure(m, compteur, consec);
		journal[i]=m;
		ecrire_journal(m);//fonction qui ecrit un enregistrement dans le fichier journaling//
		i++;
		do {
			printf("Voulez vous generer une autre mesure ? (o/n) : ");
			scanf("%c" ,&choix);
			getchar();
			if (choix!='n'&& choix!='N' && choix!='O'&& choix!='o') {
				printf(" \n Entree invalide ! Tapez uniquement 'o' ou 'n'. \n");
			}
		}while (choix!='n'&& choix!='N' && choix!='O'&& choix!='o');
	}
	
	char nom_fichier[100];
	nom_fichier_rapport(nom_fichier);   // fonction pour générer le nom (avec la date)
	generer_rapport_liste(journal,i, nom_fichier); // utiliser ce nom pour le rapport 
	printf(" \n Programme terminé. Rapport generé(%d mesures) .\n" ,i);
	return 0;
}
