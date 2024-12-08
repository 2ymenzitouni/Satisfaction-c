#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    /*=====variables=====*/
    int choix;
    int Q1,Q2,Q3,Q4,Q5;
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


    do {
        printf("\n1.Repondre a la satisfaction\n2. Afficher les avis\n3. Calculer la moyenne des notes\n4. Quitter\n");
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
                    printf("Erreur de redimensionnement memoire.\n");
                    return 1;
                }
            }

            // Lecture des données
            printf("Votre Nom:");
            scanf(" %49[^\n]", &nomsClients[taille]);

            printf("1.Quelle est votre satisfaction generale concernant votre expérience dans notre restaurant ? : \n");
            printf("Note /10: ");
            scanf("%d",&Q1);

            printf("Comment evaluez-vous la qualite des plats que vous avez commandes ?: \n");
            printf("Note /10: ");
            scanf("%d",&Q2);

            printf("3.Comment evaluez-vous la rapidite et l efficacite du service ? \n");
            printf("Note /10: ");
            scanf("%d",&Q3);

            printf("4.Dans quelle mesure le cadre et l ambiance du restaurant ont repondu a vos attentes ?: \n");
            printf("Note /10: ");
            scanf("%d",&Q4);

            printf("5.Recommanderiez-vous notre restaurant a vos proches ou amis ?: \n");
            printf("Note /10: ");
            scanf("%d",&Q5);

            notes[taille] = Q1 + Q2 + Q3 + Q4 + Q5;

            printf("Commentaire : ");
            scanf(" %99[^\n]", commentaires[taille]);

            //enregistrer data dans clients.txt
            FILE *fichier = fopen("clients.txt", "a");
            if (fichier == NULL) {
            printf("Erreur Ouverture fichier clients!!");
            free(nomsClients); // Free memory before exiting
            return 1;
            }
            fprintf(fichier,"%s;%d;%s\n",nomsClients[taille],notes[taille]/5,commentaires[taille]);
            fclose(fichier);
            taille++;
        }
        else if (choix == 2) {
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
            FILE *fichier = fopen("clients.txt","r"); // lecture du fichier clients.txt
            while(fgets(lignes,sizeof(lignes),fichier)!= NULL){
                char *nom = strtok(lignes,";");
                char *note = strtok(NULL,";");
                char *commentaire = strtok(NULL,";");
                total_note += atoi(note);
                nbl++;
            }
            printf("========================================\n");
            printf("Moyenne des notes : %.2f\n", (double)total_note / nbl);
            //initiation à 0 de nbl et total_note
            nbl = 0;
            total_note = 0;
            printf("========================================\n");
            fclose(fichier);
        }
        else if (choix == 4){
            printf("Merci cher Client.");
            break;
        }
    } while (choix != 1 || choix!= 2 || choix!=3 || choix!=4 || choix!=5);

    // Libération de la mémoire
    free(nomsClients);
    free(notes);
    free(commentaires);

    printf("Programme terminé.\n");
    return 0;
}
