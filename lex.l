%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bis.tab.h"
extern int numLigne;
extern int numColonne;

extern int yyparse(void);
extern YYSTYPE yyval;
extern void nom(char entite[], char *test);
extern void inserer(char entite[], char code[]);

char test[40];

void linecount(char* commentaire) {
    int i = 0;
    while (commentaire[i] != 0) {
        if (commentaire[i] == '\n') {
            numLigne++;
            numColonne = 1;
        } else {
            numColonne++;
        }
        i++;
    }
}

%}

%option noyywrap

nbr [0-9]
id [A-Z]([_]|[a-zA-Z0-9])*
integers [-]?([1-9][0-9]*|0)
reels [-]?([1-9][0-9]*|0)\.([0-9]*[1-9])

comment "//"(.|\n)*"//"

%%

"++" return incr;
"--" return decr; 

BEGIN {numColonne += yyleng; return mc_bgn;}
END {numColonne += yyleng; return mc_end;}
Return {numColonne += yyleng; return mc_return;}
If {numColonne += yyleng; return mc_if;}
else {numColonne += yyleng; return mc_else;}
CONST  {numColonne += yyleng; return mc_const;}
FOR {numColonne += yyleng; return mc_for;}
WHILE {numColonne += yyleng; return mc_while;}
INT { numColonne += yyleng; yylval.str=strdup(yytext); return mc_int;}
FLOAT { numColonne += yyleng; yylval.str=strdup(yytext); return mc_float;} 
BOOL { numColonne += yyleng; yylval.str=strdup(yytext); return mc_bool;}   

{id} {
    numColonne += yyleng; 
    int j = 0;
    int consecutiveUnderscores = 0;
    int errorDetected = 0;
    
    if (yyleng > 10) {
        printf("Erreur lexicale a la ligne %d, colonne %d : L'identifiant %s a une longueur supérieure a 10\n", numLigne, (int)(yytext - yytext_ptr) + 1, yytext);
        errorDetected = 1;
    } else {
        while (yytext[j] != '\0') {
            if (yytext[j] == '_' && yytext[j + 1] == '_') {
                printf("Erreur lexicale a la ligne %d, colonne %d : Symboles '_' successifs dans l'identifiant %s\n", numLigne, (int)(yytext - yytext_ptr) + 1 + j, yytext);
                consecutiveUnderscores = 1;
                errorDetected = 1;
                break;  
            }
            // Vérification si l'identifiant se termine par un underscore
            if (yytext[j] == '_' && yytext[j + 1] == '\0') {
                printf("Erreur lexicale a la ligne %d, colonne %d : L'identifiant %s se termine par un tiret bas '_'\n", numLigne, (int)(yytext - yytext_ptr) + yyleng, yytext);
                errorDetected = 1;
                break;
            }
            j++;
        }

        if (!consecutiveUnderscores && !errorDetected) {
            // Ajouter a la table des symboles uniquement si pas d'underscores consécutifs, pas de tiret bas en fin d'identifiant et pas d'autres erreurs
            yylval.str = strdup(yytext);
            nom(yytext, test);
            if (strcmp(yytext, test) != 0) {
                inserer(yytext, "id");
            }
            return id;
        }
    }   
}

{integers} {numColonne += yyleng; yylval.entier=atoi(yytext); return integers;}
{reels} { numColonne += yyleng; yylval.flottant = atof(yytext); return reels;}
true|false|TRUE|FALSE { numColonne += yyleng; yylval.boolll=strdup(yytext); return booll; }  
{comment}  {numColonne += yyleng; linecount(yytext);}  

: {numColonne += yyleng; return col;}
; {numColonne += yyleng; return scol;}
, {numColonne += yyleng; return com;}
= {numColonne += yyleng; return aff;}
\- {numColonne += yyleng; return minus;}
\+ {numColonne += yyleng; return plus;}
\* {numColonne += yyleng; return mult;}
\/ {numColonne += yyleng; return dvd;}
"<" {numColonne += yyleng; return inf;}
"<=" {numColonne += yyleng; return infeg;}
">" {numColonne += yyleng; return supp;}
">=" {numColonne += yyleng; return suppeg;}
"<>" {numColonne += yyleng; return diff;}
"==" {numColonne += yyleng; return egg;}
"(" {numColonne += yyleng; return paro;}
")" {numColonne += yyleng; return parf;}
"{" {numColonne += yyleng; return debutc;}
"}" {numColonne += yyleng; return finc;}
[ \t]
\n {numLigne++; numColonne = 0;}

. printf("Erreur lexicale a la ligne %d, colonne %d : L'identifiant %s \n", numLigne, numColonne , yytext);


%%
