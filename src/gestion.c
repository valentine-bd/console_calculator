#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<gestion.h>
#include<previews.h>
#include<tests.h>

/*-----------------------------------------------------------------------------------------------------------------------------*/

#define I 10   
#define DIFF_ET_OP_POSSIBLE()  chaine[*cursor] !='*' && chaine[*cursor] !='+' && chaine[*cursor] !='-' && chaine[*cursor] !='/'
#define DIFF_ET_END_OF_SRING() chaine[*cursor] != '\0' && chaine[*cursor] != ')'

/* - I                      : taille des chaines et tableaux intermédiaires en attente de l'allocation dynamique
   - DIFF_ET_OP_POSSIBLE()  : condition "Ce caractere n'est pas un opérateur"
   - DIFF_ET_END_OF_SRING() : condition "On arrive à la fin d'un bloc de calcul" (Condition d'arret d'une itération)
-----------------------------------------------------------------------------------------------------------------------------*/

// Enregistre la saisie clavier dans une chaine de caracteres en remplacant le saut de ligne par '/0'
int get(char *chaine, int longueur)
{
    char *positionEntree=NULL;
    if (fgets(chaine, longueur, stdin) != NULL )
    {
        positionEntree=strchr(chaine,'\n');
        if (positionEntree != NULL)
        {
            *positionEntree='\0';
        }
        return 1;
    }
    return 0;
}

// Coeur du programme, initie le curseur permettant de balayer la chaine
void give(char *chaine)
{
    int valeurCursor = 0;
    int *cursor = &valeurCursor;
    double resultat = 0;
    resultat = iteration(chaine, cursor);
    if (nonValide(cursor) == 1)
    {
        printf("\nErreur : Non pris en charge !\n");
    }
    else
    {
        printf("%s = %f\n",chaine,resultat);
    }
}

/* Fonction initiée par give et rapelee par elle meme à chaque nouveau bloc de calcul (opération de base sans parenthèses)
   Tri les variables et operateurs dans 2 tableaux séparés */
double iteration(char *chaine, int *cursor)
{
    int p = 0, n = 0;
    double variables[I] = {0}, resultat = 0;
    char operators[I];

    do
    {
        if (parenthese(chaine, cursor) == 1)
        {
            variables[p] = iteration(chaine, cursor);
            if (*cursor == -1)
            {
                return 0;
            }
            p++;
            *cursor += 1;
        }
        else if (operator(chaine, cursor) == 1)
        {
            operators[n] = getOperator(chaine, cursor);
            n++;
        }
        else if (variable(chaine, cursor) == 1)
        {
            variables[p] = getVariable(chaine, cursor);
            p++;
        }
        else if (chaine[*cursor] == ' ')
        {
            *cursor += 1;
        }
        else
        {
            *cursor = -1;
            return 0;
        }
    } while ( DIFF_ET_END_OF_SRING() );
    resultat = calcul(variables, operators, cursor);
    return resultat;
}

/* Effectue les calculs pour chaques blocs en considérant les priorités de calculs
   Utilise les tableaux de variables et opérateurs préalablement triés*/
double calcul(double *variables, char *operateurs, int *cursor)
{
    int k = 0;

     while (operateurs[k] != '\0')
        {
            switch (operateurs[k])
            {
                case '*':
                variables[k] *= variables[k+1];
                variables[k+1]=variables[k];
                operateurs[k] = '|';
                break;

                case '/':
                if (variables[k+1] == 0){
                    *cursor = -1;
                    return 0;
                }
                variables[k] /= variables[k+1];
                variables[k+1]=variables[k];
                operateurs[k] = '|';
                break;
            }
            k++;       
        }
        k = 0;
    
    while (operateurs[k] != '\0')
    {
        switch (operateurs[k])
        {
        case '+':
            variables[k] += variables[k+1];
        break;

        case '-':
            variables[k] -= variables[k+1];
        break;

        case '|':
            break;
        }
        variables[k+1] = variables[k];
        k++;
    }
    return variables[k];
}

// Sort l'operateur de la chaine et avance le curseur de 1
char getOperator(char *chaine, int *cursor)
{
    int k = *cursor;
    *cursor += 1;
    return chaine[k];
}

// Sort la variable de la chaine et avance le curseur de 1
double getVariable(char *chaine, int *cursor)
{
    char chaineTemp[I];
    int n = 0;
    double variable = 0;
    char *endPtr;
    while ( DIFF_ET_OP_POSSIBLE() && DIFF_ET_END_OF_SRING())
    {
        chaineTemp[n] = chaine[*cursor];
        n++;
        *cursor += 1;
    }
    chaineTemp[n] = '\0';
    variable = strtod(chaineTemp, &endPtr);
    return variable;
}

