#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Penser à inclure string.h pour strchr()
#include "revision.h"

//deuxième version
#define TEST 6

#if TEST ==1
    //tableaux
    int main(int argc, char *argv[])
    {

        int tab[DIM][DIM];

        for(int i=0;i<DIM;i++)
        {
            printf("\n\n");
            for(int j=0;j<DIM;j++)
            {
                tab[i][j] = 0;
                printf(" %d ",tab[i][j]);
            }
        }

        printf("\n Nous sommes le %s",__DATE__);
        printf("\nIl est actuellement %s",__TIME__);

        return 0;
    }





#elif TEST ==2
    //pointeurs
    int main(int argc, char *argv[])
    {
        int heures = 0, minutes = 90;
        int *Pheure = &heures;
        int *Pminutes = &minutes;
        
        decoupeMinutes(Pheure, Pminutes);
        printf("%d heures et %d minutes", *Pheure, *Pminutes);

        return 0;
    }

    void decoupeMinutes(int *Pheures, int *Pminutes)
    {
        *Pheures = *Pminutes / 60;  // 90 / 60 = 1
        *Pminutes = *Pminutes % 60; // 90 % 60 = 30
    }
#elif TEST ==3
    //structure données
    struct Personne
    {
        char nom[100];
        char prenom[100];
        char adresse[1000];
        
        int age;
        int etudiant; // Booléen : 1 = etudiant, 0 = non etudiant
    };

    typedef struct Personne Personne;

    int main(int argc, char *argv[])
    {
        Personne etudiant;
        printf("saisir infos de la personne : \n nom: ");
        scanf("%s", &etudiant.nom);
        printf("\nprenom: ");
        scanf("%s", &etudiant.prenom);
        printf("\nadresse: ");
        scanf("%s", &etudiant.adresse);
        printf("\nage: ");
        scanf("%d", &etudiant.age);
        printf("etudiant?: ");
        scanf("%d", &etudiant.etudiant);

        printf("Vous etes %s %s, vous avez %d ans, vous habitez %s.", etudiant.nom, etudiant.prenom, etudiant.age, etudiant.adresse);
    }
#elif TEST ==4
    //allocation dynamique
  int main(int argc, char *argv[])
    {
        int nbchiffre = 0; 
        int* memoireAllouee = NULL;//pointeur

        printf("Cb voulez vous saisir de chiffres?: ");
        scanf("%d", &nbchiffre);

        if(nbchiffre >0)
        {
            memoireAllouee = malloc(nbchiffre*sizeof(int));//allocation mémoire, contient adresse mémoire
            if (memoireAllouee == NULL) // Si l'allocation a échoué
            {
               
                exit(0); // On arrête immédiatement le programme
            }
            else 
            {    
                for(int i=0;i<nbchiffre;i++)
                {
                    printf("entrez un chiffre: ");
                    scanf("%d", &memoireAllouee[i]);//tableau = pointeur, case = int
                    printf("%d", memoireAllouee[i]);
                }   
            }
        }
        free(memoireAllouee); // Libération de mémoire
        return 0;
    }

#elif TEST ==5
    //liste chainée
    typedef struct Element Element;
    struct Element
    {
        int nombre;//variable
        Element *suivant;//pointeur de l'element suivant
    };

    typedef struct Liste Liste;
    struct Liste
    {
        Element *premier;//pointeur vers le 1er element de liste
    };

    Liste *initialisation()
    {
        Liste *liste = malloc(sizeof(*liste));//creation liste
        Element *element = malloc(sizeof(*element));//creation premier element

        if (liste == NULL || element == NULL)
        {
            exit(EXIT_FAILURE);
        }

        element->nombre = 0;//= *element.nombre = 0;
        element->suivant = NULL;//qu'un seul element
        liste->premier = element;//ajoute l'element dans la liste

        return liste;
    }

    void insertion(Liste *liste, int nvNombre)
    {
        /* Création du nouvel élément */
        Element *nouveau = malloc(sizeof(*nouveau));
        if (liste == NULL || nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }
        nouveau->nombre = nvNombre;

        /* Insertion de l'élément au début de la liste */
        nouveau->suivant = liste->premier;
        liste->premier = nouveau;
    }


    void suppression(Liste *liste)
    {
        if (liste == NULL)
        {
            exit(EXIT_FAILURE);
        }

        if (liste->premier != NULL)
        {
            Element *aSupprimer = liste->premier;
            liste->premier = liste->premier->suivant;
            free(aSupprimer);
        }
    }

    void afficherListe(Liste *liste)
    {
        if (liste == NULL)
        {
            exit(EXIT_FAILURE);
        }

        Element *actuel = liste->premier;

        while (actuel != NULL)
        {
            printf("%d -> ", actuel->nombre);
            actuel = actuel->suivant;
        }
        printf("NULL\n");
    }

    int main(int argc, char *argv[])
    {
        Liste *maListe = initialisation();

        insertion(maListe, 4);
        insertion(maListe, 8);
        insertion(maListe, 15);
        afficherListe(maListe);

        suppression(maListe);

        
        

        
        

        return 0;

    }



#elif TEST == 6
    //piles : structure LIFO
    //files : struture FIFO
    typedef struct Element Element;
    struct Element
    {
        int nombre;
        Element *suivant;
    };
    typedef struct Pile Pile;
    struct Pile
    {
        Element *premier;
    };

    Pile *initialiser()
    {
        Pile *pile = malloc(sizeof(*pile));//creation liste
        Element *element = malloc(sizeof(*element));//creation premier element

        if (pile == NULL || element == NULL)
        {
            exit(EXIT_FAILURE);
        }

        element->nombre = 0;//= *element.nombre = 0;
        element->suivant = NULL;//qu'un seul element
        pile->premier = element;//ajoute l'element dans la liste

        return pile;
    }

    void empiler(Pile *pile, int nvNombre)//meme démarche que liste chainée
    {
        Element *nouveau = malloc(sizeof(*nouveau));
        if (pile == NULL || nouveau == NULL)
        {
            exit(EXIT_FAILURE);
        }

        nouveau->nombre = nvNombre;
        nouveau->suivant = pile->premier;
        pile->premier = nouveau;
    }

    int depiler(Pile *pile)//structure LIFO
    {
        if (pile == NULL)
        {
            exit(EXIT_FAILURE);
        }

        int nombreDepile = 0;
        Element *elementDepile = pile->premier;//LIFO

        if (pile != NULL && pile->premier != NULL)
        {
            nombreDepile = elementDepile->nombre;
            pile->premier = elementDepile->suivant;
            free(elementDepile);
        }

        return nombreDepile;
    }

    void afficherPile(Pile *pile)
    {
        if (pile == NULL)
        {
            exit(EXIT_FAILURE);
        }
        Element *actuel = pile->premier;

        while (actuel != NULL)
        {
            printf("%d\n", actuel->nombre);
            actuel = actuel->suivant;
        }

        printf("\n");
    }

    int main()
    {
        Pile *maPile = initialiser();

        empiler(maPile, 4);
        empiler(maPile, 8);
        empiler(maPile, 15);
        empiler(maPile, 16);
        empiler(maPile, 23);
        empiler(maPile, 42);

        printf("\nEtat de la pile :\n");
        afficherPile(maPile);

        printf("Je depile %d\n", depiler(maPile));
        printf("Je depile %d\n", depiler(maPile));

        printf("\nEtat de la pile :\n");
        afficherPile(maPile);

        return 0;
    }

#elif TEST == 7

#endif
