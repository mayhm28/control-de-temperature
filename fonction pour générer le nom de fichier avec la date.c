void nom_fichier_rapport(char *nom_fichier) {
    char d[100];
    date(d);
    sprintf(nom_fichier, "rapport_%.10s.txt", d);
}



