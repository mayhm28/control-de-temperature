#include <stdio.h>
#include <stdlib.h>
#include <time.h>
main(){
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
		if (compteur>=consec && m.niv_alerte !=0){
			printf(" [%s] Temperature: %.2f°C ---- Alerte niveau : %d --- DECLENCHEMENT DE L'ALARME \n", m.date,m.temp,m.niv_alerte);
			
		}else if(m.niv_alerte !=0) {
			printf(" [%s] Temperature: %.2f°C ---- Alerte niveau : %d (consécutives=%d) --- alarme en attente \n", m.date,m.temp,m.niv_alerte,compteur);			
		}else{
			printf("[%s] Temperature: %.2f°C --- Normal \n", m.date, m.temp);
		}
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
	generer_rapport(journal,10); //fonction qui fait le rapport des mesures et l enregistre dans un fichier rapport.txt//
	printf(" \n Programme terminé. Rapport generé(%d mesures) .\n" ,i);
	
	char nom_fichier[100];
	nom_fichier_rapport(nom_fichier);   // fonction pour générer le nom (avec la date)
	generer_rapport_liste(journal, nom_fichier); // utiliser ce nom pour le rapport 
	return 0;
	
