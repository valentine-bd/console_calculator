#include<tests.h>

/*-----------------------------------------------------------------------------------------------------------------------------*/

#define EGAL_PARENTHESE()  chaine[*cursor] == '('
#define EGAL_OR_OPERATOR() chaine[*cursor] == '+' || chaine[*cursor] == '-' || chaine[*cursor] == '*' || chaine[*cursor] == '/'
#define EGAL_OR_VARIABLE() chaine[*cursor] == '0' || chaine[*cursor] == '1' || chaine[*cursor] == '2' || chaine[*cursor] == '3' || \
                           chaine[*cursor] == '4' || chaine[*cursor] == '5' || chaine[*cursor] == '6' || chaine[*cursor] == '7' || \
                           chaine[*cursor] == '8' || chaine[*cursor] == '9'

/* - EGAL_PARENTHESE()  : condition "Ce caractere est une parenthèse ouvrante"
   - EGAL_OR_OPERATOR() : condition "Ce caractère est un opérateur"
   - EGAL_OR_VARIABLE() : condition "Ce caractere est un nombre"
-----------------------------------------------------------------------------------------------------------------------------*/

// Teste si le caractere actuel est une parenthese ouvrante renvoie 1 si oui. Avance le curseur pour débuter l'itération suivante
int parenthese(char *chaine, int *cursor)
{
    if(EGAL_PARENTHESE())
    {
        *cursor += 1;
        return 1;
    }
    return 0;
}

// Teste si le caractère actuel est un opérateur
int operator(char *chaine, int *cursor)
{
    if(EGAL_OR_OPERATOR())
    {
        return 1;
    }
    return 0;
}

// Teste si le caractère actuel est un nombre
int variable(char *chaine, int *cursor)
{
    if(EGAL_OR_VARIABLE())
    {
        return 1;
    }
    return 0;
}

// Teste si le curseur vaut -1 == erreur dans la lecture de la chaine (division par 0 / presence de caractères non autorisés...)
int nonValide(int *cursor)
{
    if(*cursor == -1)
    {
        return 1;
    }
    return 0;
}