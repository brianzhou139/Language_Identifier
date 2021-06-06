#ifndef CATEGORY_H_INCLUDED
#define CATEGORY_H_INCLUDED

double *
receiveTitleCategory(char *text,int *Ttotal,int *Ctotal,int *count,int lang);

double *
receiveDescriptionCategory(char *text,int *Ttotal,int *Ctotal,int *count,int lang);

double *
receivePostCategory(char *text,int *Ttotal,int *Ctotal,int *count,int limit,int lang);

char *
strLWR2(char *str);

int
getEngOrRuss(char * text);


#endif // CATEGORY_H_INCLUDED
