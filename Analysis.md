CAHIER D’ANALYSE — Projet myfind

1. Introduction
Dans le cadre du cours de systèmes d’exploitation, il nous est demandé de concevoir et implémenter une commande similaire à la commande Linux 'find', appelée 'myfind'.
Cette commande permettra à l’utilisateur de rechercher des fichiers et des répertoires dans une arborescence donnée selon certains critères.
2. Objectifs
Objectif général : Développer un programme capable de parcourir un système de fichiers.
Objectifs spécifiques :
- Parcourir récursivement un répertoire
- Lire les arguments utilisateur
- Filtrer les fichiers
- Afficher les résultats
3. Description du système
Le programme fonctionne en ligne de commande.
Exemple : myfind . -name test.txt
Le programme analyse les arguments, parcourt les fichiers et affiche les résultats.
4. Acteurs
- Utilisateur
- Système d’exploitation (Linux)
5. Besoins fonctionnels
- Rechercher dans un répertoire
- Parcourir les sous-dossiers
- Filtrer par nom
- Afficher les résultats
6. Besoins non fonctionnels
- Performance
- Utilisation mémoire
- Compatibilité Linux
- Gestion des erreurs
7. Contraintes
- Langage C
- Utilisation des appels système
- Pas de bibliothèques externes
8. Décomposition
- Parsing des arguments
- Parcours des fichiers
- Filtrage
- Affichage
9. Algorithme
main -> parse_args -> explore_directory
explore_directory : parcours récursif et affichage
10. Cas d’utilisation
myfind .
myfind . -name test.txt
11. Gestion des erreurs
- Dossier inexistant
- Permissions refusées
- Arguments invalides
12. Conclusion
Ce projet permet de comprendre les systèmes de fichiers et la programmation système en C. 

DECOMPOSITION DU PROBLEME — Projet myfind

1. Reformulation du problème
Créer une commande capable de parcourir un système de fichiers et d’afficher les fichiers correspondant à des critères donnés.
2. Décomposition en grandes parties
A. Parsing des arguments : lire et comprendre la commande utilisateur
B. Parcours du système de fichiers : explorer dossiers et fichiers
C. Filtrage : vérifier si un fichier correspond aux critères
D. Affichage : afficher les résultats
3. Décomposition détaillée
Parsing : récupérer le chemin, identifier les options (-name), lire les valeurs
Parcours : ouvrir dossier (opendir), lire contenu (readdir), récursion
Filtrage : comparer nom, type, etc.
Affichage : afficher chemin complet
4. Décomposition fonctionnelle
main()
parse_args()
explore_directory()
match_criteria()
display_result()
5. Flux d’exécution
Lire les arguments
Parcourir le dossier
Tester chaque fichier
Afficher si correspond
Explorer récursivement
6. Répartition en groupe (5 personnes)
1. Parsing
2. Parcours
3. Filtrage
4. Affichage
5. Intégration et coordination
7. Problèmes à gérer
Gestion des erreurs
Permissions
Fichiers spéciaux (., ..)
Chemins longs


