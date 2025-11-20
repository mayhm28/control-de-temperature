main(){
	int seuil_min , seuil_max;
	lire_config("config.txt",&seuil_min,&seuil_max,&consec); // fonction qui lit ces valeurs depuis le fichier config//
	mesure journal[100];
	int compteur=0;
	printf("MONITORING DE TEMPERATURE \n");
	int i;
	for (i=0;i<=10;i++){
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

