###### Code Source TP ASD.c: mon propre programme que j'ai créé à partir de zéro pour le projet TP ASD

Contexte du projet: l’objectif de ce projet est d’utiliser les arbres binaires de recherches pour indexer un fichier texte donné. Cet arbre contient les différents mots du fichier texte avec les occurrences du mots dans le fichier (position du mot dans les phrases du fichier).
C’est-à-dire, Ces mots du texte seront les indexes, et pour chaque mot on lui associe la liste des occurrences du mot dans le fichier (le numéro des phrases où ces mots apparaissent). Si un mot est présent plusieurs fois dans une phrase, on le compte qu’une seule fois, on considère une seule fois la phrase.
La recherche d’une phrase dans un texte (dans le fichier texte) revient à faire l’intersection de la liste des positions des mots de la phrase dans l’arbre binaire de recherche.
1. Créer cette structure,
2. Construire l’arbre de recherche, (chercher un mot, inserer un mot s’il n’existe pas, …)
3. Créer la liste des positions, - pouvoir y ajouter des positions, - faire l’intersection de deux liste (liste en commun), qui vérifie si un élément existe dans cette liste, …
4. Chercher une phrase dans le texte.

###### mazesolver.c:
Permet de trouver un chemin entre deux points A et B sur un labyrinthe.

###### Mon propre compilateur:
Un compilateur pour mon propre langage de programmation simple, développé en utilisant Flex et Bison.
