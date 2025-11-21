#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// structure de mesures //
typedef struct {
    float temp;
    char date[100];
    int niv_alerte;
} mesure;
// fonction qui lit ces valeurs depuis le fichier config//
int lire_config(const char *fichier,float *min,float *max,int *consec){
	FILE *f = fopen(fichier, "r");
	if f==NULL{
        return -1;
    }
    fscanf(f,"%f%f%d",min,max,consec);
    fclose(f);
    return 0;
}
// fonction qui genere une temperature entre 0 et 50 dune facon aleatoire//
float genererTemperature(){
    return (float)rand()/((float)RAND_MAX/50.0));
}
//fonction pour obtenir la date/heure actuelle//
void date(){
    time_t now = time(NULL);      
    printf("Date/Heure : %s", ctime(&now));  
}
//pour vérifier l'alerte :normal,dépassement léger niv1,dépassement modéré niv2,dépassement critique niv3//
int verif_alerte(float x,float min,float max){
	if (x>=min && x<=max){
		return 0;
	}
	float d=x-max;
	if (d>0 && d<5){
		return 1;
	}
	if (d>=5 && d<10){
		return 2;
	}
	if(d>=10){
		return 3;
	}
}
//fonction qui ecrit un enregistrement dans le fichier journaling//
void ecrire_journal(m){
main(){
	int seuil_min , seuil_max;
	lire_config("config.txt",&seuil_min,&seuil_max,&consec); // fonction qui lit ces valeurs depuis le fichier config//
	mesure journal[100];
	int compteur=0;
	printf("MONITORING DE TEMPERATURE \n");
	int i;
	for (i=0;i<10;i++){
		printf("Veuillez appuir sur entree pour generer la mesure %d :\n ", i+1);
		getchar();
		
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
		if (compteur>=consec && m.niv_alerte !=0){
			printf(" [%s] Temperature: %.2f°C ---- Alerte niveau : %d --- DECLENCHEMENT DE L'ALARME \n", m.date,m.temp,m.niv_alerte);
			
		}else if(m.niv_alerte !=0) {
			printf(" [%s] Temperature: %.2f°C ---- Alerte niveau : %d (consécutives=%d) --- alarme en attente \n", m.date,m.temp,m.niv_alerte,compteur);			
		}else{
			printf("[%s] Temperature: %.2f°C --- Normal \n", m.date, m.temp);
		}
		
		journal[i]=m;
		ecrire_journal(m);//fonction qui ecrit un enregistrement dans le fichier journaling//
		
	}	
	generer_rapport(journal,10); //fonction qui fait le rapport des mesures et l enregistre dans un fichier rapport.txt//
	return 0;
	
	
}






