typedef struct Noeud{
	mesure m;
	struct Noeud* suiv;
} Noeud ;
typedef struct File{
	Noeud *tete;
	Noeud *queue;	
}; File 
void enfiler (File* f, mesure m){
	Noeud* newNode =(Noeud*)malloc(sizeof(Noeud));
	newNode->m=m;
	newNode->suiv=NULL;
	if(f->queue){
		f->queue->suiv=newNode;
	}else{
		f->tete=newNode;
	}
	f->queue = newNode;
}
mesure defiler(File* f){
	if (!f->tete){
		printf("La file est vide !! \n");
	}
	Noeud* temp = f->tete;
	f->tete = temp->suiv
	if (!f->tete){
		f->queue = NULL;
	}
	free(temp);
	return m ;
	
}
void trait_alerte(File* f){
	printf("Traitement alertes critiques (FIFO)");
	while(f->tete){
		mesure m = defiler(f);
		printf("[%s] temperature: %.2f°C | Alerte Critique traitee \n" , m);
	}
}



int main(){
	File fileAlert = {NULL, NULL};
	
	
	
	
	if (m.niv_alerte ==3){
		enfiler(&fileAlert, m);
	}
	/*apres do .. while */
	trait_alerte(&fileAlert);
}
