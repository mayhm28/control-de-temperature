void nom_fichier_rapport(char *nom_fichier) {
    time_t now = time(NULL);             // récupère le temps actuel
    struct tm *t = localtime(&now);      // convertit en date/heure locale
    sprintf(nom_fichier, "rapport_%04d-%02d-%02d.txt", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
}
