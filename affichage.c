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
