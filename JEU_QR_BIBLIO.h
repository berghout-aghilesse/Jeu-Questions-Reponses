// Question : numero_qst
//                domaine
//                difficulté
//                contenu
//                reponse



// Defintion de la strcuture d'une question
typedef struct question
{
    int numero_qst;
    char domaine[25];
    char difficulte[20];
    char contenu[255];
    char reponse[255];
}question;


//Defintion de la structure d'une liste de question
typedef struct questionNode
{
    question question;
    struct questionNode* next;
}questionNode, *listeQuestions;


/*
    Joueur   : identifiant
               pseudoname
               date_d'enregistrement
               domaines de prédilection
               nb de parites jouées
               score total
*/


// Définition de la structure d'un joueur
typedef struct joueur
{
    int identifiant;
    char pseudoname[255];
    char date[11];
    char domaine[20]; 
    int nb_parties;
    int score_total;
}joueur;



// Définition de la structure d'une liste de joueurs
typedef struct joueurNode
{
    joueur joueur;
    struct joueurNode* next;
}joueurNode, *listeJoueurs;




// Partie   : identifiant du joueur l'ayant joué
//             niveau_de_partie
//             liste_des_qst auxquelles il a repondues : la qst
//                                                       la reponse
//                                                       le score





typedef struct qst_partie
{
    char question[255];
    char reponse_donnee[255];
    int score_obtenu;
}qst_partie;


typedef struct qst_partie_Node
{
    qst_partie question;
    struct qst_partie_Node* next;
}qst_partie_Node, *liste_qst_partie;




// Définition de la structure d'une partie
typedef struct partie
{
    int identifiant; // identifiant du joueur l'ayant jouée
    int niveau;   
    liste_qst_partie li;                 // Liste des qst auxquelles il a repondues : qst + reponse donnée + score obtenu
}partie;


// Définition de la structure d'une liste de parties
typedef struct partieNode
{
    partie partie;
    struct partieNode* next;
}partieNode, *listeParties;






//-----------------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>




void print_liste_questions(listeQuestions li);


void eclater_difficulte(listeQuestions li, listeQuestions* l1, listeQuestions* l2, listeQuestions* l3);


listeQuestions insert_qst_tail(listeQuestions li, question Q);


listeJoueurs triJoueuersScore(listeJoueurs li);

listeJoueurs triJoueuersNbPrt(listeJoueurs li);

listeJoueurs insert_player_tail(listeJoueurs li, joueur J);

void print_liste_joueurs(listeJoueurs li);


int add_player(FILE *file);

int remove_player(FILE *file);

int add_question(FILE *file);

int remove_question(FILE *file);

void extract_questions_by_criteria(listeQuestions li, char* domaine_cible, char* difficulte_cible);