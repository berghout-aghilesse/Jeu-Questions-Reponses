#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "JEU_QR_LL_BIBLIO.h"


listeJoueurs triJoueuersNbPrt(listeJoueurs li)
{
    if(li == NULL || li->next == NULL)
        return li;
    

    bool swap;
    listeJoueurs end = NULL;
    listeJoueurs P;
    joueur Q;

    do
    {
        swap = false;
        P = li;
        while(P->next != end)
        {
            if(P->joueur.nb_parties > P->next->joueur.nb_parties)
            {
                Q = P->joueur;
                P->joueur = P->next->joueur;
                P->next->joueur = Q; 
                swap = true;
            }
            P = P->next;
        }
        end = P;
    } while (swap);


    return li;
    
}


listeJoueurs triJoueuersScore(listeJoueurs li)
{
    if(li == NULL || li->next == NULL)
        return li;
    

    bool swap;
    listeJoueurs end = NULL;
    listeJoueurs P;
    joueur Q;

    do
    {
        swap = false;
        P = li;
        while(P->next != end)
        {
            if(P->joueur.score_total > P->next->joueur.score_total)
            {
                Q = P->joueur;
                P->joueur = P->next->joueur;
                P->next->joueur = Q; 
                swap = true;
            }
            P = P->next;
        }
        end = P;
    } while (swap);


    return li;
    
}


listeQuestions insert_qst_tail(listeQuestions li, question Q)
{
    

    questionNode* newTail = (questionNode*)malloc((sizeof(questionNode)));

    newTail->question = Q;


    if(li == NULL)
        return newTail;
    
    listeQuestions P = li;

    while(P->next != NULL)
    {
        P = P->next;
    }

    newTail->next = NULL;
    P->next = newTail;

    return li;
}


void eclater_difficulte(listeQuestions li, listeQuestions* l1, listeQuestions* l2, listeQuestions* l3)
{
    listeQuestions P = li;
    *l1 = NULL;
    *l2 = NULL;
    *l3 = NULL;

    while(P != NULL)
    {
        if(strcmp(P->question.difficulte, "Easy") == 0)
        {
            *l1 = insert_qst_tail(*l1, P->question);
        } else if (strcmp(P->question.difficulte, "Medium") == 0)
        {
            *l2 = insert_qst_tail(*l2, P->question);
        } else 
        {
            *l3 = insert_qst_tail(*l3, P->question);
        }
        P = P->next;
    }

}


void print_liste_questions(listeQuestions li)
{
    if(li == NULL)
        printf("\n\nLa liste est vide! Rien a afficher.");
    
    listeQuestions P = li;
    while(P != NULL)
    {   
        Sleep(150);
        printf("\n\n");
        printf("\nNumero de la question : %d", P->question.numero_qst);
        printf("\nDomaine : %s", P->question.domaine);
        printf("\nDifficulte : %s", P->question.difficulte);
        printf("\nContenu de la question : %s", P->question.contenu);
        printf("\nReponse de la question : %s", P->question.reponse);


        P = P->next;
    }
}


void print_liste_joueurs(listeJoueurs li)
{
    if(li == NULL)
        printf("La liste est vide! Rien a afficher.");
    else
    {
        listeJoueurs P = li;
        while(P != NULL)
        { 
            Sleep(250);  
            printf("\n\n");
            printf("\nIdentifiant : %d", P->joueur.identifiant);
            printf("\nPseudoname : %s", P->joueur.pseudoname);
            printf("\nDate d'enregistrement : %s", P->joueur.date);
            printf("\nDomaine : %s", P->joueur.domaine);
            printf("\nNombre de parties : %d", P->joueur.nb_parties);
            printf("\nScore total : %d", P->joueur.score_total);
            P = P->next;
        }
    }
}


listeJoueurs insert_player_tail(listeJoueurs li, joueur J)
{
    joueurNode* newTail = (joueurNode*)malloc(sizeof(joueurNode));
    newTail->next = NULL;
    newTail->joueur = J;

    if(li == NULL)
        return newTail;

    listeJoueurs P = li;
    while(P->next != NULL) 
        P = P->next;
    
    P->next = newTail;
    return li;
}






//-----------------------------------------------------------------------------------------------------------------------------------------

int add_player(FILE *file) {

    

    char input[1000], pseudoname[255], date[11], domaine[20];
    int nb_parties, score_total, identifiant;
    {
        getchar();
        printf("Entrez les informations du joueur : 'identifiant pseudoname date domaine nb_parties score_total' en respectant ce format \n");
        printf("> ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d %s %s %s %d %d", &identifiant, pseudoname, date, domaine, &nb_parties, &score_total) == 6) {
            fprintf(file,"%d %s %s %s %d %d \n", identifiant, pseudoname, date, domaine, nb_parties, score_total);
            fflush(file);
        }else{
            printf("\n Le format saisi est incorrect...");
        }
    }

    return 0;
}


int remove_player(FILE *file )
{
    int  ID;
    rewind(file);
    char line[1000];
    char wanted_player[500];
    //---------------------
    FILE *temp_file = fopen("temp.txt", "w"); ;
    //--------------
    if (temp_file == NULL) {
        perror("Error opening temp file");
        return 0;
    }



    int the_number_of_games,best_score;
    char date[15], the_name[100],input[1000],the_favorite_domain[100];
    printf("enter the the_name you want to delete \n");
    scanf("%s", &wanted_player);
    // wanted_player[strcspn( wanted_player, "\n")] = '\0';
    if ( wanted_player != NULL)
    {
        while (fgets(line, sizeof(line), file))
        {
           //  fgets(input,sizeof(input),file);
        if (sscanf(line, "%d %s %s %s %d %d",&ID,the_name, date, the_favorite_domain, &the_number_of_games,&best_score) == 6){
            if  (strcmp(the_name, wanted_player) == 0){
                printf("removing ...\n");
                continue  ;

            }  
            else 
            {
                fprintf(temp_file,"%s",line);
            } 
        }
        }
        
        fclose(file);
        fclose(temp_file);
    //------------------------------------------------------------------------
    temp_file = fopen("temp.txt", "r");
    file = fopen("player.txt", "w");
    if (file == NULL || temp_file == NULL) {
        perror("Error reopening files");
    }else{
    while (fgets(line, sizeof(line), temp_file))
    {
        fprintf(file,"%s", line);
    }
    }
    }
    printf("\nPlayer removed successfully!");
    fclose(file);
    fclose(temp_file);
    remove("temp.txt");
}







int add_question(FILE *file) 
{
    char domaine[20], difficulte[11], contenu[255], reponse[255], input[1000];
    int numero_qst;
    {
        getchar();
        printf("Entrez les informations sur la question 'numero_qst domaine, difficulte, contenu_choixMultiples reponse' en respectant ce formmat\n");
        printf("> ");
        fgets(input,sizeof(input),stdin);
        if (sscanf(input, "%d %s %s %s %s ",&numero_qst , domaine, difficulte, contenu, reponse) == 5)
        {
            fprintf(file,"%d %s %s %s %s \n", numero_qst , domaine, difficulte, contenu, reponse);
            fflush(file);
        } else 
            printf("\n Le format saisi est incorrect ...");
        
    }
    return 0;
}










int remove_question(FILE *file)
{
    int the_correct_answer,line_number;
    rewind(file);
    char line[1000];
    int wanted_question_nb;
    //---------------------
    FILE *temp_file = fopen("temp.txt", "w"); ;
    //--------------
    if (temp_file == NULL) {
        perror("Error opening temp file");
    }else{
    char domain[100] , question[1000],input[1000],dificulty[100];
    printf("enter the question you want to delete \n");
    scanf("%d", &wanted_question_nb);
        while (fgets(line, sizeof(line), file))
        {
           //  fgets(input,sizeof(input),file);
        if (sscanf(line, "%d %s %s %s %s ",&line_number,domain, dificulty, question, the_correct_answer) == 5){
            if  (line_number == wanted_question_nb){
              continue;
            }  
            else 
            {
                fprintf(temp_file,"%s",line);
            } 
        }
        }
        fclose(file);
        fclose(temp_file);
    //------------------------------------------------------------------------
    temp_file = fopen("temp.txt", "r");
    file = fopen("questions.txt", "w");
    if (file == NULL || temp_file == NULL) {
        perror("Error reopening files");
    }else{
    while (fgets(line, sizeof(line), temp_file))
    {
        fprintf(file,"%s", line);
    }
    }
    }fclose(file);
    fclose(temp_file);
    remove("temp.txt");



    
}









void extract_questions_by_criteria(listeQuestions li, char* domaine_cible, char* difficulte_cible) {
    listeQuestions P = li;
    
    while (P != NULL && 
          (strcmp(P->question.difficulte, difficulte_cible) != 0 || 
           strcmp(P->question.domaine, domaine_cible) != 0)) {
        P = P->next;
    }

    

    if (P != NULL) {
        printf("\n\n%d %s %s %s %s", 
               P->question.numero_qst, 
               P->question.domaine, 
               P->question.difficulte, 
               P->question.contenu, 
               P->question.reponse);
    } else {
        printf("No matching question found.\n");
    }
}


