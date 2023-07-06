# ZAPPY

Projet De Fin d'Année à Epitech Paris 2e Année PGE

Ce projet a été réalisé dans le cadre du projet final de la 2ème année du cursus PGE à Epitech Paris.

Participants:
- Louis De-Macedo
- Amaury Bariety
- Guillaume Clement Bonniel Veyron
- Malek Gatoufi
- Nicolas Poupon
- Theo Villemer

## Sujet

### Introduction

Le projet ZAPPY consiste à développer un jeu en réseau simulant un environnement dans lequel des habitants IA en équipes appelés "Trantoriens" interagissent pour se nourrir et collecter des pierres pour évoluer sur une carte plane quadrillée. Les IA se battent ou coopérent pour survire. La première équipe avec 6 joueurs à l'évolution maximale l'emporte.

### Objectifs

Les objectifs du projet sont les suivants :

- Implémenter un serveur qui gère la logique du jeu et la communication entre les clients.
- Développer un client graphique permettant aux joueurs d'interagir avec le serveur et de visualiser l'environnement de jeu.
- Mettre en place une architecture réseau robuste et efficace pour assurer la fluidité du jeu en temps réel.

### Activités

Les habitants de Trantor se préoccupent principalement de deux activités :

- Se nourrir : Les Trantoriens ont besoin de collecter de la nourriture pour survivre. Chaque unité de nourriture leur permet de vivre pendant X secondes.
- Collecter des pierres : Les Trantoriens doivent collecter des pierres pour effectuer le rituel d'élévation et gagner en niveau.

### Individus

Les habitants de Trantor sont des êtres sans corps, flous et pacifistes. Ils occupent la totalité de la tuile dans laquelle ils se trouvent et se déplacent joyeusement à la recherche de nourriture et de pierres. Les Trantoriens peuvent rencontrer facilement d'autres habitants sur la même tuile, mais il est impossible de distinguer leur direction lorsqu'ils se rencontrent. Les Trantoriens se reproduisent et peuvent ainsi se dupliquer.

### Ressources

Il existe 2 types de ressources : Les pierres et la nourriture. La nourriture permet aux Trantoriens de survivre, les pierres sont nécessaires à l'évolution. Un trantorien en fonction du nombre de joueur sur la carte a besoin d'un plus ou moins grand nombre de pierres. Les pierres sont au nombre de 6 :

- Linemate
- Deraumere
- Sibur
- Mendiane
- Phiras
- Thystame

### Le rituel d'élévation

Le rituel d'élévation est le but ultime des Trantoriens. Chaque nouvelle élévation demande plus de pierres. Pour effectuer ce rituel, ils doivent rassembler les éléments suivants sur la même tuile :

| Élévation | Nb de joueurs| Linemate | Deraumere | Sibur | Mendiane | Phiras | Thystame |
|-----------|--------------|----------|-----------|-------|----------|--------|----------|
| 1->2      | 1            | 1        | 0         | 0     | 0        | 0      | 0        |
| 2->3      | 2            | 1        | 1         | 1     | 0        | 0      | 0        |
| 3->4      | 2            | 2        | 0         | 1     | 0        | 2      | 0        |
| 4->5      | 4            | 1        | 1         | 2     | 0        | 1      | 0        |
| 5->6      | 4            | 1        | 2         | 1     | 3        | 0      | 0        |
| 6->7      | 6            | 1        | 2         | 3     | 0        | 1      | 0        |
| 7->8      | 6            | 2        | 2         | 2     | 2        | 2      | 1        |

La première équipe qui possède au moins 6 joueurs de niveau 8 gagne la partie.

### Vision


La vision des joueurs est limitée. À chaque élévation, la vision s'étend d'une unité vers l'avant et d'une unité de chaque côté de la nouvelle ligne. Au premier niveau, un personnage est définie à valeure "1". Les joueurs peuvent utiliser la commande "look" pour explorer leur environnement et recevoir une liste des objets présents sur chaque tuile.

### Exécution du programme

Le projet nécessite la création de trois binaires :

- Serveur : Un serveur développé en langage C qui génère le monde du jeu.
- Client graphique : Un client graphique développé en C++ pour observer ce qui se passe dans le monde.
- Client AI : Un client autonome développé en Python, permettant de contrôler les personnage directement en envoyant des commandes au serveur.

### Commandes du joueur

Chaque joueur peut répondre aux actions suivantes :

    Move : Déplacer le joueur d'une tuile vers l'avant.
    Turn : Tourner le joueur de 90 degrés à droite ou à gauche.
    Look : Obtenir la liste des objets présents sur les tuiles environnantes.
    Inventory : Afficher l'inventaire du joueur, indiquant les quantités d'objets qu'il possède.
    Broadcast : Émettre un message pour tous les joueurs.
    Connect_nbr : Obtenir le nombre de slots disponibles dans l'équipe.
    Fork : Reproduire le joueur en créant un nouvel œuf.
    Eject : Éjecter les joueurs présents sur la même tuile.
    Take : Ramasser un objet présent sur la tuile.
    Set : Déposer un objet sur la tuile.
    Incantation : Lancer une élévation pour passer au niveau supérieur.

Les commandes sont transmises au serveur sous forme de chaînes de caractères se terminant par un saut de ligne. Si une commande est incorrecte ou inconnue, le serveur répondra par "ko".

- Voir protocole GUI dans "/docs/"

### Communication client-serveur

La communication entre le client AI et le serveur s'effectue via des sockets TCP. Le client envoie ses requêtes au serveur, qui renvoie un message confirmant l'exécution correcte de la commande ou un message d'erreur en cas d'échec.

### Communication

La communication entre le serveur et les clients ainsi qu'entre les clients eux-mêmes se fait via le protocole TCP/IP. Différents messages sont échangés pour permettre le déroulement du jeu, tels que la connexion d'un client au serveur, les mouvements des joueurs, les collectes de ressources, etc.

### Serveur

Le serveur est le principal composant du projet. Il gère la logique du jeu, la gestion des connexions et des déconnexions des clients, ainsi que la communication entre les clients. Le serveur maintient une visualisation graphique de l'état du jeu, comprenant la position des joueurs, les ressources disponibles, etc.

### Client

Le client est l'interface graphique permettant aux joueurs d'interagir avec le serveur. Il affiche l'environnement de jeu et permet aux joueurs de se déplacer, de collecter des ressources, de communiquer avec les autres joueurs, etc.

### COMMANDE DE TEST

Ici les commandes de test pour lancer le projet, ce dans 2 terminaux séparés:

```bash
./zappy_gui -p 55555 -h 127.0.0.1
```

```bash
./zappy_server -p 55555 -x 15 -y 20 -n name1 name2 name3 -c 5 -f 300
```

### Norme de Commits

En envoyant nos projets sur Github, nous avons respecté une certaine norme pour chaque envoit. Ci-dessous leur signification :

- [ADD] : Ajout d'un nouveau fichier ou feature
- [FIX] : Correction d'une erreur, de "coding style" (apparence du code, intendation)
- [DOC] : Ajout ou update lié à la documentation
- [DEL/RM] : Supression d'un élément quel qu'il soit
- [UPD] : Mise à jour d'un ou plusieur fichiers
- [REBASE] : Rebase

### Conclusion du projet

- Note : /////

- Bilan : //////
