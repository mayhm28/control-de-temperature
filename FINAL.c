#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <windows.h>
// structure de mesures 
typedef struct mesure {
    float temp; // température mesurée
    char date[100]; // date et heure
    int niv_alerte; // 0 = normal, 1 = niv1, 2 = niv2, 3 = niv3
} mesure;
//structure de la file
typedef struct Noeud{
    mesure m;
    struct Noeud* suiv;
} Noeud;
typedef struct File{
    Noeud *tete;
    Noeud *queue;
} File;
//structure de la pile
typedef struct Pile {
	Noeud* sommet; 
}Pile;
// structure de l'arbre
typedef struct arbre{
	mesure val;
	struct arbre *gauche;
	struct arbre *droite;
} arbre;
//creation d'un noeud dans larbre
arbre* nouv_arbre(mesure m){
	arbre* nouvar=(arbre*)malloc(sizeof(arbre));
	nouvar->val=m;
    nouvar->gauche=NULL;
    nouvar->droite=NULL;
    return nouvar;
}
//inserer un noeud dans larbre
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
//tri croissant des mesures
void inorder(arbre* racine){
	if (racine==NULL){
		return;
	}
	inorder(racine->gauche);
	printf("[%s] Temperature: %.2f°C ---- Alerte niveau : %d ---\n",racine->val.date,racine->val.temp,racine->val.niv_alerte);
	inorder(racine->droite);
}
//recherche de la temp min
arbre* mintemp(arbre* racine) {
    if (racine == NULL){
    	return NULL;
	}
    arbre* temp = racine;
    while (temp->gauche != NULL) {
        temp = temp->gauche;
    }
    return temp;
}
//recherche de la temp max
arbre* maxtemp(arbre* racine) {
    if (racine == NULL){
    	return NULL;
	}
    arbre* temp = racine;
    while (temp->droite != NULL) {
        temp = temp->droite;
    }
    return temp;
}
//somme des valeurs dans larbre
float somme(arbre* racine) {
    if (racine == NULL){
    	return 0;
	}
    return racine->val.temp+somme(racine->gauche)+somme(racine->droite);
}
//liberation de larbre
void liberer(arbre* racine) {
    if (racine == NULL){
	   return;
	}
    liberer(racine->gauche);
    liberer(racine->droite);
    free(racine);
}
//enfiler
void enfiler(File* f, mesure m){
    Noeud* newNode =(Noeud*)malloc(sizeof(Noeud));
    newNode->m = m;
    newNode->suiv = NULL;

    if(f->queue){
        f->queue->suiv = newNode;
    } else {
        f->tete = newNode;
    }
    f->queue = newNode;
}
//defiler
mesure defiler(File* f){
    if (!f->tete){
        printf("La file est vide !! \n");
    }
    Noeud* temp = f->tete;
    f->tete = temp->suiv;
    mesure m = temp->m;

    if (!f->tete){
        f->queue = NULL;
    }
    free(temp);
    return m;
}
// fonction empiler
void empiler (Pile* p,mesure mesr){
	Noeud* newNode =(Noeud*)malloc(sizeof(Noeud));
	newNode->m=mesr;
	newNode->suiv=p->sommet;
	p->sommet=newNode;	
}
//fonction depiler 
mesure depiler(Pile* p){
	if (p->sommet==NULL){
		printf("il n'y a pas d'alertes pour le moment");
	}
	else{
		Noeud* aux=p->sommet;
		mesure mes=aux->m;
		p->sommet=aux->suiv;
		free(aux);
		return mes;
	}
}
// fonction qui lit ces valeurs depuis le fichier config
void lire_config(const char *fichier,int *seuil_min,int *seuil_max,int *consec,int *tempsPause ){
    FILE *f = fopen(fichier,"r");
    if (f == NULL){
        printf("Erreur ouverture config !!\n");
    }
    fscanf(f,"%d%d%d%d",seuil_min,seuil_max,consec,tempsPause);
    fclose(f);
}
// fonction qui genere une temperature entre 0 et 50 dune facon aleatoire
float genererTemperature(){
    return (float)rand() / (float)RAND_MAX * 50.0;
}
//fonction pour obtenir la date/heure actuelle
void date(char *date_str){
    time_t now = time(NULL);
    strftime(date_str, 100, "%Y-%m-%d %H:%M:%S", localtime(&now));
}
//pour vérifier l'alerte :normal,dépassement léger niv1,dépassement modéré niv2,dépassement critique niv3
int verif_alerte(float x,int seuil_min,int seuil_max){
    if (x >= seuil_min && x <= seuil_max){
        return 0;
    }
    float d;
    if (x > seuil_max){
        d = x - seuil_max;
    } else {
        d = seuil_min - x;
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
//affichage
void afficher_mesure(mesure m, int compteur, int consec){
    if (compteur >= consec && m.niv_alerte != 0){
        printf("[%s] Temperature: %.2f°C ---- Alerte niveau : %d --- DECLENCHEMENT DE L'ALARME\n",
               m.date, m.temp, m.niv_alerte);
    }
    else if (m.niv_alerte != 0){
        printf("[%s] Temperature: %.2f°C ---- Alerte niveau : %d (consécutives=%d) --- alarme en attente\n",
               m.date, m.temp, m.niv_alerte, compteur);
    }
    else {
        printf("[%s] Temperature: %.2f°C --- Normal\n", m.date, m.temp);
    }
}
//fonction qui ecrit un enregistrement dans le fichier journaling
void ecrire_journal(File *f){
    FILE *fp = fopen("journal.txt","a");
    if (!fp){
        printf("Impossible d'ouvrir journal.txt\n");
    }
    Noeud *courant =f->tete;
    while (courant !=NULL){
    	mesure m=courant->m;
    	fprintf(fp,"%s | %.2f | %d\n", m.date, m.temp, m.niv_alerte);
    	courant = courant->suiv;
	}
    fclose(fp);
}
//traitement des alertes urgentes 
void traiter_alertes_urg(Pile *p ){
	if (p->sommet !=NULL){
		int i=0;
		printf ("\n IL FAUT TRAITER MAINTENANT CES ALERTES SELON L'ORDRE DONNE \n ");  
		while (p->sommet){
			i++;
        	mesure m = depiler(p);
        	printf("\n [%s] %.2f°C alerte  numero %d doit etre traitee \n " ,m.date,m.temp,i);
   		}
	}
}
//fonction pour générer le nom de fichier rapport avec la date
void nom_fichier_rapport(char *nom_fichier ) {
    char d[100];
    date(d);
    sprintf(nom_fichier, "rapport_%.10s.txt", d); // garde AAAA-MM-JJ
}
//duree en etat d'alerte niv 1 , niv2 et niv3 
char* durAlerte(File *f, int tempsPause){
	if (f->tete ==NULL){
    	return("Pas d'alertes");
	}
	int s=0,a1=0,a2=0,a3=0;
    Noeud *aux= f->tete;
    while (aux != NULL){
    	mesure m= aux->m;
        if (m.niv_alerte == 1) a1++;
        else if (m.niv_alerte == 2) a2++;
        else if (m.niv_alerte == 3) a3++;
        aux =aux->suiv;
    }
    s=(a1+a2+a3)*tempsPause;
    if (s==0){
		return("Pas d'alertes");
	}else{
   		int h,m,sec;
		h=s/3600;
		s %=3600;
		m=s/60;
		sec=s%60;
		char *str=(char*)malloc(50* sizeof(char));
		sprintf(str,"la durée totale en etat d''alertes :  %02d:%02d:%02d", h,m,sec );
		return (str  );
	}	
}
//le rapport
void generer_rapport_liste(File *f, arbre* A, int n, char *nom_fichier, int tempsPause){
    FILE *fp = fopen(nom_fichier,"w");

    if (!fp) {
        printf("La creation du fichier %s est impossible\n", nom_fichier);
        return;
    }
    if (f->tete ==NULL){
    	fprintf(fp , "Aucune mesure enregistree ! /n");
    	fclose(fp);
	}

    int a1=0,a2=0,a3=0;
    Noeud *courant= f->tete;
    while (courant != NULL){
    	mesure m= courant->m;
        if (m.niv_alerte == 1) a1++;
        else if (m.niv_alerte == 2) a2++;
        else if (m.niv_alerte == 3) a3++;
        courant =courant->suiv;
    }
    
    float min_val = mintemp(A)->val.temp;
    float max_val = maxtemp(A)->val.temp;
    float somme_val = somme(A);
    float moyenne = somme_val / n;


    fprintf(fp, "Température minimale : %.2f°C\n", min_val);
    fprintf(fp, "Température maximale : %.2f°C\n", max_val);
    fprintf(fp, "Température moyenne : %.2f°C\n", moyenne);
    fprintf(fp,"Alertes : niv1=%d niv2=%d niv3=%d\n", a1,a2,a3);
    fprintf(fp,"%s", durAlerte(f , tempsPause) );
    fclose(fp);
}
//programme principal
int main(){
    int seuil_min, seuil_max, consec, tempsPause;
    lire_config("config.txt",&seuil_min,&seuil_max,&consec,&tempsPause);
    File journal= {NULL, NULL};
    Pile pileUrgence = {NULL};
    arbre* triTemp = NULL;
    int compteur=0;
    int i=0;
    printf("MONITORING DE TEMPERATURE\n");
    printf("Appuyer sur ENTREE pour generer la premiere mesure\n");
    getchar();
    char choix='o';
    while (choix=='o' || choix=='O'){
        mesure m;
        m.temp = genererTemperature();
        date(m.date);
        m.niv_alerte = verif_alerte(m.temp,seuil_min,seuil_max);
        if (m.niv_alerte != 0) compteur++;
        else compteur = 0;
        afficher_mesure(m, compteur, consec);
        enfiler(&journal , m);
        triTemp = inserer(triTemp, m);
        if (m.niv_alerte == 3){
            empiler(&pileUrgence, m);
        }
        i++;
        Sleep(tempsPause*1000);
        do{
            printf("\nVoulez-vous generer une autre mesure ? (o/n) : ");
            scanf("%c",&choix);
            getchar();
        }while (choix!='o' && choix!='O' && choix!='n' && choix!='N');
    }
    ecrire_journal(&journal);
    traiter_alertes_urg(&pileUrgence);
    char nom_fichier[100];
    nom_fichier_rapport(nom_fichier);
    generer_rapport_liste(&journal,triTemp, i,nom_fichier, tempsPause);
    printf("\n--- MESURES TRIEES PAR TEMPERATURE ---\n");
    inorder(triTemp);
    liberer(triTemp);
    printf("\nProgramme terminé. Rapport généré (%d mesures).\n", i);
    return 0;
}



