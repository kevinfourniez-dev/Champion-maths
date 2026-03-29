#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FICHIER_SCORES "scores.txt"

void afficher_menu();
void addition();
void soustraction();
void multiplication();
void tables_multiplication();
void division();
void nombre_manquant();
void sauvegarder_score(char nom[], int s);
int  charger_score(char nom[]);

int  score = 0;
char nom_joueur[50];

void afficher_menu()
{
    printf("+-----------------------------------+\n");
    printf("|1 : Addition                       |\n");
    printf("|2 : Soustraction                   |\n");
    printf("|3 : Multiplication                 |\n");
    printf("|4 : Tables des multiplications     |\n");
    printf("|5 : Divisions                      |\n");
    printf("|6 : Nombre manquant (ex: 3+?=7)   |\n");
    printf("|0 : Sortir du jeu                  |\n");
    printf("+-----------------------------------+\n");
    printf("Score actuel : %d point(s)\n", score);
    printf("Quel est votre choix ? ");
}

void sauvegarder_score(char nom[], int s)
{
    FILE      *fichier;
    FILE      *temp;
    char       ligne[200];
    char       nom_lu[50];
    int        trouve = 0;
    time_t     maintenant;
    struct tm *info;
    char       date_str[30];

    
    time(&maintenant);
    info = localtime(&maintenant);
    strftime(date_str, sizeof(date_str), "%d/%m/%Y %H:%M:%S", info);

    fichier = fopen(FICHIER_SCORES, "r");
    temp    = fopen("scores_temp.txt", "w");

    if (temp == NULL)
    {
        printf("Erreur : impossible de sauvegarder le score.\n");
        return;
    }

    if (fichier != NULL)
    {
        while (fgets(ligne, sizeof(ligne), fichier) != NULL)
        {
            sscanf(ligne, "%s", nom_lu);

            if (strcmp(nom_lu, nom) == 0)
            {
                
                fprintf(temp, "%s | %s | %d point(s)\n", nom, date_str, s);
                trouve = 1;
            }
            else
            {
                
                fprintf(temp, "%s", ligne);
            }
        }
        fclose(fichier);
    }

    
    if (trouve == 0)
    {
        fprintf(temp, "%s | %s | %d point(s)\n", nom, date_str, s);
    }

    fclose(temp);

    
    remove(FICHIER_SCORES);
    rename("scores_temp.txt", FICHIER_SCORES);

    printf("Score sauvegarde !\n");
}

int charger_score(char nom[])
{
    FILE *fichier;
    char  ligne[200];
    char  nom_lu[50];
    int   score_lu;

    fichier = fopen(FICHIER_SCORES, "r");

    if (fichier == NULL)
    {
        return -1;   
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        
        sscanf(ligne, "%s", nom_lu);

        if (strcmp(nom_lu, nom) == 0)
        {
            sscanf(ligne, "%*s | %*s %*s | %d", &score_lu);
            fclose(fichier);
            return score_lu;
        }
    }

    fclose(fichier);
    return -1;   
}

void addition()
{
    int a, b, reponse, resultat;
    int essais = 0;

    a        = rand() % 101;
    b        = rand() % 101;
    resultat = a + b;

    printf("\n--- ADDITION ---\n");
    printf("%d + %d = ?\n", a, b);

    while (essais < 3)
    {
        printf("Entrez le resultat : ");
        scanf("%d", &reponse);
        essais++;

        if (reponse == resultat)
        {
            printf("Vous avez entre %d\n", reponse);
            printf("Bravo !\n");

            if (essais == 1)      { score += 10; printf("+10 points !\n"); }
            else if (essais == 2) { score += 5;  printf("+5 points !\n");  }
            else                  { score += 1;  printf("+1 point !\n");   }

            
            sauvegarder_score(nom_joueur, score);
            return;
        }
        else
        {
            if (essais < 3)
                printf("Mauvaise reponse, reessayez...\n");
        }
    }

    printf("Perdu ! La reponse etait : %d\n", resultat);
    printf("0 point.\n");
}

void soustraction()
{
    int a, b, temp, reponse, resultat;
    int essais = 0;

    a = rand() % 101;
    b = rand() % 101;

    
    if (a < b)
    {
        temp = a;
        a    = b;
        b    = temp;
    }

    resultat = a - b;

    printf("\n--- SOUSTRACTION ---\n");
    printf("%d - %d = ?\n", a, b);

    while (essais < 3)
    {
        printf("Entrez le resultat : ");
        scanf("%d", &reponse);
        essais++;

        if (reponse == resultat)
        {
            printf("Vous avez entre %d\n", reponse);
            printf("Bravo !\n");

            if (essais == 1)      { score += 10; printf("+10 points !\n"); }
            else if (essais == 2) { score += 5;  printf("+5 points !\n");  }
            else                  { score += 1;  printf("+1 point !\n");   }

            sauvegarder_score(nom_joueur, score);
            return;
        }
        else
        {
            if (essais < 3)
                printf("Mauvaise reponse, reessayez...\n");
        }
    }

    printf("Perdu ! La reponse etait : %d\n", resultat);
    printf("0 point.\n");
}

void multiplication()
{
    int a, b, reponse, resultat;
    int essais = 0;

    a        = rand() % 10 + 1;
    b        = rand() % 10 + 1;
    resultat = a * b;

    printf("\n--- MULTIPLICATION ---\n");
    printf("%d x %d = ?\n", a, b);

    while (essais < 3)
    {
        printf("Entrez le resultat : ");
        scanf("%d", &reponse);
        essais++;

        if (reponse == resultat)
        {
            printf("Vous avez entre %d\n", reponse);
            printf("Bravo !\n");

            if (essais == 1)      { score += 10; printf("+10 points !\n"); }
            else if (essais == 2) { score += 5;  printf("+5 points !\n");  }
            else                  { score += 1;  printf("+1 point !\n");   }

            sauvegarder_score(nom_joueur, score);
            return;
        }
        else
        {
            if (essais < 3)
                printf("Mauvaise reponse, reessayez...\n");
        }
    }

    printf("Perdu ! La reponse etait : %d\n", resultat);
    printf("0 point.\n");
}

void tables_multiplication()
{
    int table, i, reponse;
    int tous_justes = 1;

    printf("\n--- TABLES DE MULTIPLICATION ---\n");
    printf("Choisissez une table (1 a 10) : ");
    scanf("%d", &table);

    if (table < 1 || table > 10)
    {
        printf("Choix invalide.\n");
        return;
    }

    printf("\nTable de %d :\n", table);
    for (i = 1; i <= 10; i++)
    {
        printf("%d x %d = %d\n", table, i, table * i);
    }

    printf("\nMaintenant a vous de jouer !\n");
    for (i = 1; i <= 10; i++)
    {
        printf("%d x %d = ? ", table, i);
        scanf("%d", &reponse);

        if (reponse != table * i)
        {
            printf("Faux ! La reponse etait %d\n", table * i);
            tous_justes = 0;
        }
        else
        {
            printf("Correct !\n");
        }
    }

    if (tous_justes == 1)
    {
        printf("Gagne ! Toutes les reponses etaient correctes !\n");
        score += 10;
        printf("+10 points !\n");
        sauvegarder_score(nom_joueur, score);
    }
    else
    {
        printf("Perdu ! Revenez vous entrainer.\n");
    }
}

void division()
{
    int b, resultat, a, reponse;
    int essais = 0;

    b        = rand() % 9 + 1;
    resultat = rand() % 10 + 1;
    a        = b * resultat;

    printf("\n--- DIVISION ---\n");
    printf("%d / %d = ?\n", a, b);

    while (essais < 3)
    {
        printf("Entrez le resultat : ");
        scanf("%d", &reponse);
        essais++;

        if (reponse == resultat)
        {
            printf("Vous avez entre %d\n", reponse);
            printf("Bravo !\n");

            if (essais == 1)      { score += 10; printf("+10 points !\n"); }
            else if (essais == 2) { score += 5;  printf("+5 points !\n");  }
            else                  { score += 1;  printf("+1 point !\n");   }

            sauvegarder_score(nom_joueur, score);
            return;
        }
        else
        {
            if (essais < 3)
                printf("Mauvaise reponse, reessayez...\n");
        }
    }

    printf("Perdu ! La reponse etait : %d\n", resultat);
    printf("0 point.\n");
}

void nombre_manquant()
{
    int a, b, resultat, reponse, operation;
    int essais = 0;

    operation = rand() % 2;

    printf("\n--- NOMBRE MANQUANT ---\n");

    if (operation == 0)
    {
        
        a        = rand() % 51;
        b        = rand() % 51;
        resultat = a + b;
        printf("%d + ? = %d\n", a, resultat);
    }
    else
    {
        
        a        = rand() % 51;
        b        = rand() % 51;
        resultat = a + b;
        printf("%d - ? = %d\n", resultat, a);
    }

    while (essais < 3)
    {
        printf("Entrez le nombre manquant : ");
        scanf("%d", &reponse);
        essais++;

        if (reponse == b)
        {
            printf("Vous avez entre %d\n", reponse);
            printf("Bravo !\n");

            if (essais == 1)      { score += 10; printf("+10 points !\n"); }
            else if (essais == 2) { score += 5;  printf("+5 points !\n");  }
            else                  { score += 1;  printf("+1 point !\n");   }

            sauvegarder_score(nom_joueur, score);
            return;
        }
        else
        {
            if (essais < 3)
                printf("Mauvaise reponse, reessayez...\n");
        }
    }

    printf("Perdu ! Le nombre manquant etait : %d\n", b);
    printf("0 point.\n");
}

int main()
{
    int choix;
    int score_retrouve;

    srand(time(NULL));

    printf("=== CHAMPION DES MATHS ===\n\n");

    
    printf("Entrez votre nom : ");
    scanf("%s", nom_joueur);

    score_retrouve = charger_score(nom_joueur);

    if (score_retrouve == -1)
    {
        printf("Bienvenue %s ! Nouveau joueur, score de depart : 0\n\n",
               nom_joueur);
        score = 0;
    }
    else
    {
        printf("Bon retour %s ! Score recupere : %d point(s)\n\n",
               nom_joueur, score_retrouve);
        score = score_retrouve;
    }

    
    do
    {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                printf("Addition\n");
                addition();
                break;

            case 2:
                printf("Soustraction\n");
                soustraction();
                break;

            case 3:
                printf("Multiplication\n");
                multiplication();
                break;

            case 4:
                printf("Tables des multiplications\n");
                tables_multiplication();
                break;

            case 5:
                printf("Divisions\n");
                division();
                break;

            case 6:
                printf("Nombre manquant\n");
                nombre_manquant();
                break;

            case 0:
                break;

            default:
                printf("Choix invalide, entrez 0, 1, 2, 3, 4, 5 ou 6.\n");
                break;
        }

        printf("\n");

    } while (choix != 0);

    printf("Merci de votre visite, %s !\n", nom_joueur);
    printf("Score final : %d point(s)\n", score);

    return 0;
}
