#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    /*=====variables=====*/
    int capacite = 2; // Taille initiale du tableau
    int taille = 0;   // Nombre actuel d'éléments
    char lignes[1024]; // pour les lignes du fichier clients.txt
    int nbl =0,total_note=0;
    //int note;
    const int MAX_NOM = 50;          // Taille maximale pour le nom du client
    const int MAX_COMMENTAIRE = 100; // Taille maximale pour le commentaire
    // Tableaux dynamiques simples
    char (*nomsClients)[MAX_NOM] = malloc(capacite * MAX_NOM * sizeof(char));
    int *notes = malloc(capacite * sizeof(int));
    char (*commentaires)[MAX_COMMENTAIRE] = malloc(capacite * MAX_COMMENTAIRE * sizeof(char));
    /*=====variables=====*/

    if (!nomsClients || !notes || !commentaires) {
        printf("Erreur d'allocation mémoire.\n");

    }

    int choix;
    do {
        printf("\n1.  Ajouter un client\n2. Afficher les avis\n3. Calculer la moyenne des notes\n4. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        if (choix == 1) {
            // Redimensionnement si nécessaire
            if (taille == capacite) {
                capacite *= 2;
                nomsClients = realloc(nomsClients, capacite * MAX_NOM * sizeof(char));
                notes = realloc(notes, capacite * sizeof(int));
                commentaires = realloc(commentaires, capacite * MAX_COMMENTAIRE * sizeof(char));
                if (!nomsClients || !notes || !commentaires) {
                    printf("Erreur de redimensionnement mémoire.\n");
                    return 1;
                }
            }

            // Lecture des données
            printf("Nom du client : ");
            scanf(" %49[^\n]", nomsClients[taille]);
            printf("Note (sur 10) : ");
            scanf("%d", &notes[taille]);
            printf("Commentaire : ");
            scanf(" %99[^\n]", commentaires[taille]);

            //enregistrer data dans clients.txt
            FILE *fichier = fopen("clients.txt", "a");
            if (fichier == NULL) {
            printf("Erreur Ouverture fichier clients!!");
            free(nomsClients); // Free memory before exiting
            return 1;
            }
            fprintf(fichier,"%s;%d;%s\n",nomsClients[taille],notes[taille],commentaires[taille]);
            fclose(fichier);
            taille++;
        }
        else if (choix == 2) {
            // Affichage des avis
            /*printf("\n--- Liste des avis ---\n");
            for (int i = 0; i < taille; i++) {
                printf("Client : %s\nNote : %d\nCommentaire : %s\n\n", nomsClients[i], notes[i], commentaires[i]);
            }*/
            FILE *fichier = fopen("clients.txt","r"); // lecture du fichier clients.txt
            printf("\n--- Liste des avis ---\n");
            while(fgets(lignes,sizeof(lignes),fichier)!= NULL){
                char *nom = strtok(lignes,";");
                char *note = strtok(NULL,";");
                char *commentaire = strtok(NULL,";");
                printf("Nom: %s \n",nom);
                printf("Note: %s\n",note);
                printf("Commentaire: %s\n",commentaire);
            }
            fclose(fichier);

        }
        else if (choix == 3) {
            // Calcul de la moyenne
            /*if (taille == 0) {
                printf("Aucune note disponible.\n");
            } else {
                int somme = 0;
                for (int i = 0; i < taille; i++) {
                    somme += notes[i];
                }
                printf("Moyenne des notes : %.2f\n", (double)somme / taille);
            }*/
            FILE *fichier = fopen("clients.txt","r"); // lecture du fichier clients.txt
            while(fgets(lignes,sizeof(lignes),fichier)!= NULL){
                char *nom = strtok(lignes,";");
                char *note = strtok(NULL,";");
                char *commentaire = strtok(NULL,";");
                total_note += atoi(note);
                nbl++;
            }
            printf("========================================\n");
            printf("%d\n",total_note);
            printf("\n%d\n",nbl+1);
            printf("Moyenne des notes : %f\n", (double)total_note / nbl);
            nbl = 0;
            total_note = 0;
            printf("========================================\n");
            fclose(fichier);
        }
        else if (choix == 4){
            system("start http://127.0.0.1:5500/avis.html");
        }
    } while (choix != 1 || choix!= 2 || choix!=3);

    // Libération de la mémoire
    free(nomsClients);
    free(notes);
    free(commentaires);

    printf("Programme terminé.\n");
    return 0;
}
