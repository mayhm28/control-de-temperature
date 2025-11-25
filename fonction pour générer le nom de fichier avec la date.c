void nom_fichier_rapport(char *nom_fichier) {
    char d[100];
    date(d);
    d[10]='\0'
    sprintf(nom_fichier, "rapport_%s.txt", d);
}

