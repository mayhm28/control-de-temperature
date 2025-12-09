Application pour gérer un controleur Intelligent de Température 
Description du projet:
Ce programme réalise un système de monitoring de température , similaire à ceux utilisés avec des vrais capteurs .
Il lit des seuils depuis un fichier de configuration, génère des mesures, vérifie les alertes, enregistre les mesures dans un journal et crée un rapport quotidien nommé avec la date pour permettre un suivi complet (l’utilisateur peut accéder à n’importe quel rapport d’une date antérieure, car chaque rapport est conservé séparément et n’est jamais écrasé).
Fonctionnalités principales :
*Lecture des seuils depuis un fichier de configuration (config.txt):
  Seuil minimum et maximum de température.
  Nombre de mesures consécutives avant déclenchement de l’alarme.

*Génération automatique de mesures de température
  Températures aléatoires entre 0°C et 50°C.
  Obtention automatique de la date et de l’heure pour chaque mesure.

*Vérification des niveaux d’alerte
  Alerte normale (0), légère (niv1), modérée (niv2) ou critique (niv3).
  Compteur de mesures consécutives pour déclencher les alarmes.

*Affichage en temps réel des mesures et des alertes
  Affichage clair sur le terminal.
  Indication de l’état normal ou du niveau d’alerte.
  Déclenchement visuel de l’alarme lorsque le seuil de mesures consécutives est atteint.

*Journalisation des mesures dans journal.txt
  Chaque mesure enregistrée avec date, température et niveau d’alerte.
  Permet la traçabilité complète des mesures.

*Génération d’un rapport quotidien
  Rapport nommé automatiquement avec la date (ex. rapport_2025-12-07.txt).
  Contient toutes les mesures du jour avec statistiques : température minimale, maximale, moyenne et nombre d’alertes par niveau.

*Tri et stockage des mesures
  Insertion dans un arbre binaire par température pour tri automatique et accès rapide au min/max (parcours InOrder).

*Statistiques automatiques
  Calcul du minimum, maximum, moyenne et nombre d’alertes (niv1, niv2, niv3) à partir de l’arbre et du journal.

*Gestion mémoire
  L’arbre et les fichiers sont correctement libérés et fermés pour éviter les fuites.

*Pile pour alertes critiques
  Les mesures de niveau 3 sont stockées en LIFO pour notifier l’utilisateur et traiter urgemment les alertes.


