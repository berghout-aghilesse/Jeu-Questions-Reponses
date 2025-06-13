#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#include "JEU_QR_BIBLIO.h"



void print_line(char ch, int length) {
    for (int i = 0; i < length; ++i)
        putchar(ch);
    putchar('\n');
}

void center_text(const char *text, int width) {
    int padding = (width - strlen(text)) / 2;
    for (int i = 0; i < padding; ++i)
        putchar(' ');
    printf("%s\n", text);
}



int main(void)
{
    FILE* playerFile = fopen("player.txt", "a+");
    if(playerFile == NULL)
    {
        printf("File opening failed ...");
        exit(1);
    }





    FILE* questionFile = fopen("questions.txt", "a+");
    if(questionFile == NULL)
    {
        printf("File opening failed ...");
        exit(1);
    }

    char ligne[1000];


    
    printf(".\n");
    
    int width = 148;

    print_line('_', width);
    printf("\n");

    center_text("TP 1 ALSDD (Listes Lineaire Chainees)\n", width);

    print_line('_', width);

    printf("\n\n");
    center_text("BERGHOUT Aghilesse G02", width);
    center_text("HEBABCHA Riadh G02\n", width);

    print_line('_', width);


    



    init:

    listeQuestions listQst = NULL;
    rewind(questionFile);  // <--- Reset file pointer
    while (fgets(ligne, sizeof(ligne), questionFile)) {
        question q;
        sscanf(ligne, "%d %s %s %s %s", &q.numero_qst, q.domaine, q.difficulte, q.contenu, q.reponse);
        listQst = insert_qst_tail(listQst, q);
    }

    
    

    listeJoueurs listPl = NULL;
    rewind(playerFile);  // <--- Reset file pointer
    while (fgets(ligne, sizeof(ligne), playerFile)) {
        joueur j;
        sscanf(ligne, "%d %s %s %s %d %d", &j.identifiant, j.pseudoname, j.date, j.domaine, &j.nb_parties, &j.score_total);
        listPl = insert_player_tail(listPl, j);
    }




    listeQuestions qstFaciles = NULL, qstMoyennes = NULL, qstDifficiles = NULL;
    listeJoueurs joueursTriesScore = NULL, joueursTriesNbParties = NULL;


    char line[1000];



    


    while(true)
    {


        

        
        print_line('_', width);
        printf("\n\n\n\n\n\n");
        center_text("Menu", width);

        printf("\n1 - Afficher la liste des questions.");
        printf("\n2 - Afficher la liste des joueurs.");

        printf("\n3 - Ajouter une question.");
        printf("\n4 - Supprimer une question.");
        printf("\n5 - Ajouter un joueur.");
        printf("\n6 - Supprimer un joueur.");

        printf("\n7 - Eclater ma liste des quesitons en trois selon la difficulte.");

        printf("\n8 - Choisir une question d'un domaine 'x' ayant un niveau de difficulte 'y'.");

        printf("\n9 - Trier les joueurs.");

        printf("\n10 - Lancer une partie du jeu.");

        printf("\n11 - Quitter.");

        printf("\n\nVotre choix : ");
        int choice;
        scanf("%d", &choice);


        printf("\n\n\n");
        joueur J;
        question Q;



        


        switch (choice)
        {
        case 1:
            /* Afficher la liste des questions */
            printf("AFFICHER LA LISTE DES QUESTIONS\n\n\n");
            print_liste_questions(listQst);

            break;
        
        
        case 2:
            /* Afficher la liste des joueurs */
            printf("AFFICHER LA LISTE DES JOUEURS\n\n\n");
            print_liste_joueurs(listPl);
            break;
        
        
        case 3:
            /* Ajouter une question */
            add_question(questionFile);
            goto init;
            break;
        
        
        case 4:
            /* Supprimer une question */
            remove_question(questionFile);
            goto init;
            break;
        
        
        case 5:
            /* Ajouter un joueur */
            add_player(playerFile);
            goto init;
            break;
        
        
        case 6:
            /* Supprimer un joueur */
            remove_player(playerFile);
            goto init;
            break;
        
        
        case 7:
            /* Eclater selon la difficulté */
            eclater_difficulte(listQst, &qstFaciles, &qstMoyennes, &qstDifficiles);
            printf("\n\n\nQUESTIONS FACILES\n\n");
            print_liste_questions(qstFaciles);
            printf("\n\n\nQUESTIONS MOYENNES\n\n");
            print_liste_questions(qstMoyennes);
            printf("\n\n\nQUESTIONS DIFFICILES\n\n");
            print_liste_questions(qstDifficiles);
            break;
        
        
        case 8:
            char chosen_domain[20];
            printf("\nEntrez le domaine : ");
            getchar();
            fgets(chosen_domain, sizeof(chosen_domain), stdin);
            chosen_domain[strcspn(chosen_domain, "\n")] = '\0';
            

            char chosen_diff[11];
            printf("\nEntrez la difficulte : ");
            fgets(chosen_diff, sizeof(chosen_diff), stdin);
            
            chosen_diff[strcspn(chosen_diff, "\n")] = '\0';




            extract_questions_by_criteria(listQst, chosen_domain, chosen_diff);
            break;
        
        
        case 9:
            int choix;
            printf("\n1 - Trier les joueurs selon le nombre de parties jouees.");
            printf("\n2 - Trier les joueurs selon le score total.");
            printf("\n\nVotre choix : ");
            scanf("%d", &choix);

            if (choix == 1)
            {
                joueursTriesNbParties = triJoueuersNbPrt(listPl);
                print_liste_joueurs(joueursTriesNbParties);
            
            }else 
            {
                joueursTriesScore = triJoueuersScore(listPl);
                print_liste_joueurs(joueursTriesScore);

            }
            break;
        
        
        case 10:
            /* Lancer une parite du jeu */
            break;

        default:
            print_line('_', width);
            printf("\n");

            center_text("FIN DU PROGRAMME\n", width);

            print_line('_', width);
            exit(1);
            break;
        }



        printf("\n\n\n\n\n\n\n------------------------------------------------------------------------------------------------");

        


    }


    fclose(playerFile);
    fclose(questionFile);





    
    










    return 0;
}