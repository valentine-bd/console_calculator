#ifndef GESTION_H_INCLUDED
#define GESTION_H_INCLUDED

int get(char *chaine, int longueur);
double calcul(double *variables, char *operateurs, int *cursor);
char getOperator(char *chaine, int *cursor);
double getVariable(char *chaine, int *cursor);
double iteration(char *chaine, int *cursor);
void give(char *chaine);

#endif //GESTION_H_INCLUDED