#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct funDep
{
    char *partG;
    char *partD;
} funDep;


void calculate_closure(char *relation, funDep *DF, int nbr, char *closure);
int alreadyin(char *R, char A);
int addtoclos(int i, char *R, char *closure, int *ind);


int main()
{
    int nbr,i;
    int choix;
    funDep *DF;
    char* relation = malloc(sizeof(char) * 50);
    char* closure = malloc(sizeof(char) * 50);


    printf("\n  Enter the attributes of the relation R: ");

    scanf("%s", relation);

    do
    {
        printf("\n  Enter the number of FDs: ");
        scanf("%d", &nbr);
    }
    while (nbr < 1);

    DF = (funDep*)malloc(nbr*sizeof(funDep));
    for (i=0; i<nbr; i++)
    {
        DF[i].partG = (char*)malloc(50*sizeof(char));
        DF[i].partD = (char*)malloc(50*sizeof(char));
        printf("\n  Enter the FD %d: \n\n", i+1);
        printf("\t");
        scanf("  %s",DF[i].partG);
        printf(" \t  -> ");
        scanf("  %s",DF[i].partD);
    }
    system("cls");
    while(1)
    {
        printf("\n  The Relation: R{%s}\n", relation);
        printf("\n  Functional Dependencies:\n\n");
        for (i=0; i<nbr; i++)
        {
            printf("\t%s -> %s\n", DF[i].partG, DF[i].partD);
        }

        char *attribut = malloc(sizeof(char) * 50);

        printf("\n -- press '1' to calculate the closure of the attribute \n -- press any key to exit \n");
        scanf("%d",&choix);

        switch (choix)
        {
        case 1:
            printf("\n  Enter the attribute u want to calculate the closure for: ");
            scanf("%s", attribut);

            char *attrb_closure = malloc(sizeof(char) * 50);
            calcul_clos(attribut, DF, nbr, attrb_closure);
            if (strspn(attribut, relation) != strlen(attribut))
            {
                printf("\n  the attribut given is not valid \n");
            }
            else
                printf("\n  **The closure of (%s) is {%s}+ = {%s}\n\n", attribut,attribut, attrb_closure);

            break;

        default:
            exit(33);

        }
        /*printf("\n\t*do u want to exit the programme : y/n\n");
        scanf("%s",&choix);
        system("cls");*/
    }
    return 0;
}


void calcul_clos(char *attribut, funDep *DF, int nbr, char *closure)
{
    int i, j, k, nbr_attrb = strlen(attribut);

    strcpy(closure, attribut);
    do
    {
        k = strlen(closure);

        for (i = 0; i < nbr; i++)
        {
            if (strspn(DF[i].partG, closure) == strlen(DF[i].partG))
            {
                for (j = 0; j < strlen(DF[i].partD); j++)
                {
                    addtoclos(j, DF[i].partD, closure, &nbr_attrb);
                }
            }
        }
    }
    while (strlen(closure) > k);
}

int alreadyin(char *R, char A)
{
    int i = 0;
    while (R[i] != '\0')
    {
        if (R[i] == A) return 1;
        i++;
    }
    return 0;
}

int addtoclos(int i,char*R,char *closure,int *j)
{
    int flag=0;
    while(R[i]!='\0')
    {
        if(alreadyin(closure,R[i])==0)
        {
            closure[*j]=R[i];
            *j=*j+1;
            closure[*j]='\0';
            flag=1;
        }
        i++;
    }
    if(flag) return 1;
    else return 0;
}
