%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "bis.tab.h"  

extern FILE* yyin;  // Déclaration de yyin comme une variable externe


int numLigne = 1;
int numColonne = 1;
int yyparse();
int yylex();
int yywrap(void);
int yyerror(char *s);
extern YYSTYPE yylval;
extern int numLigne;
extern int numColonne;
extern int yylex();
extern int yyerror(char *s);
#include "tbsbl.h"
int codeOPR=0; // 1:+, 2=-, 3:*, 4:/
char sauvType[20];
char typecnst[50];
char typecnstt[50];
char nomIdf[20];
char sauvNom[50];
char uno[50];
char dos[50];
char tp1[50];
char tp2[50];
char  typevar[50];


%}


%union{
    int entier;
    float flottant;
    char* str;
    char* boolll;
}

%token <str>id  mc_bgn mc_end mc_for mc_if mc_int mc_bool mc_float mc_const mc_return mc_else mc_while 
%token col scol com egg plus mult dvd minus decr incr
%token inf infeg supp suppeg diff paro parf aff debutc finc
%token <entier>integers
%token <flottant>reels
%token <boolll>booll
%%

S:  Listdec mc_bgn ListInst mc_end {printf("syntaxe correcte\n"); YYACCEPT;};

Listdec: DecV Listdec | DecV;

DecV: Type ListeId scol {
    afd(sauvType, numLigne);
    

} | Type ListeIdd scol {
    afd(sauvType, numLigne);
    
       if (strcmp(sauvType, typecnst) != 0) {
        printf("erreur semantique : non compatibilite de type lorsque une declaration d'une variable a la ligne %d\n", numLigne);
    }
} | mc_const Typec ListeCst scol {
    afc(sauvType, numLigne);
     
    if (strcmp(sauvType, typecnst) != 0) {
        printf("erreur semantique : non compatibilite de type lorsque une declaration d'une constante a la ligne %d\n", numLigne);
    }
} | mc_const Typec ListeId scol {
    
};

Type: mc_int {strcpy(sauvType, $1);}| mc_float {strcpy(sauvType, $1);}| mc_bool {strcpy(sauvType, $1);};

Typec: mc_int {strcpy(sauvType, $1);}| mc_float {strcpy(sauvType, $1);}

ListeId: id com ListeId {ajouterIdNom($1);}| id {ajouterIdNom($1);};

ListeIdd: id aff cnst com ListeIdd {ajouterIdNom($1);} | id aff cnst {ajouterIdNom($1);};

ListeCst:  id aff cnstt com ListeCst {InitConst($1);ajouterIdNom($1);}| id aff cnstt {InitConst($1);ajouterIdNom($1);}

cnst: integers {strcpy(typecnst, "INT");} | reels {strcpy(typecnst, "FLOAT");} |booll{strcpy(typecnst,"BOOL");}

cnstt:  integers {strcpy(typecnst, "INT");} | reels {strcpy(typecnst, "FLOAT");} 

ListInst: Inst ListInst | Inst;

Inst: Affectation | Boucle | Condition;
Affectation: id col aff EXP scol {
    nom($1, uno);
    if (doubleDeclaration($1) == 0) {
        printf("erreur semantique a la ligne %d : l'identificateur %s n'a pas ete declare \n", numLigne, $1);
    } else {
        if (ConstanteInitialise($1) == 1) {
            printf("erreur semantique : changement de la valeur de la constante %s a la ligne %d\n", $1, numLigne);
        } else {
            typee($1, typevar);
            if (strcmp(typevar, tp1) != 0 && strcmp(typevar, tp2) != 0) {
                
                printf("erreur semantique : non compatibilite de type lors d'une affectation  a la ligne  %d\n", numLigne);
            }
             
            
        }
    }
};

EXP: id OPR EXP {
    nom($1, uno);
    if (doubleDeclaration($1) == 0) {
        printf("erreur semantique a la ligne %d : l'identificateur %s n'a pas ete declare \n", numLigne, $1);
    } else {
        typee($1, tp1);
        if (strcmp(tp1, tp2) != 0) {
            printf("erreur semantique : non compatibilite de type %s avec type %s dans une expression  a la ligne %d\n", tp1, tp2, numLigne);
        }

        
    }
}
| id {
    nom($1, dos);

    if (doubleDeclaration($1) == 0) {
        printf("erreur semantique a la ligne %d : l'identificateur %s n'a pas ete declare \n", numLigne, $1);
    } else {
        typee($1, tp2);
      
    }
}
| integers OPR EXP 
{
    strcpy(tp1, "INT");
   
   if (strcmp(tp1, tp2) != 0) {
            printf("erreur semantique : non compatibilite de type %s avec type %s dans une expression  a la ligne %d\n", tp1, tp2, numLigne);
        }
       
}
| reels OPR EXP  
{
    strcpy(tp1, "FLOAT");
    
    if (strcmp(tp1, tp2) != 0) {
            printf("erreur semantique : non compatibilite de type %s avec type %s dans une expression  a la ligne %d\n", tp1, tp2, numLigne);
        }
        
}
| reels    
{
    strcpy(tp2, "FLOAT");
    if (codeOPR == 4 && $1 == 0) {
        printf("Erreur : division par zero a la ligne %d\n", numLigne);
    }
  
}
| integers
{
    strcpy(tp2, "INT");
     if (codeOPR == 4 && $1 == 0) {
        printf("Erreur : division par zero a la ligne %d\n", numLigne);
    }
   
}
|booll
{
    strcpy(tp2, "BOOL");
     
}



OPR: plus {codeOPR=1;}| minus {codeOPR=2;}| mult {codeOPR=3;}| dvd {codeOPR=4;}

Condition:  mc_if paro Cond parf debutc ListInst finc | mc_if paro Cond parf debutc ListInst finc mc_else debutc ListInst finc ;

Boucle: Bouclefor | Bouclewhile;

Bouclewhile: mc_while paro Cond parf debutc ListInst finc;

Bouclefor: mc_for paro forCond parf debutc ListInst finc;

Cond: id CMP Cond | cnst CMP Cond | id | cnst;

forCond: id col aff cnst scol Cond scol id incr;

CMP: supp | suppeg | inf | infeg | diff | egg;




%%
int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            printf("Failed to open the file: %s\n", argv[1]);
            return 1;
        } else {
            inittab();
            init(); 
            printf("File is successfully opened: %s\n", argv[1]);
        }
    } else {
        printf("Error: No file detected.\n");
        return 1;
    }
    yyparse();
    afficher();
    fclose(yyin);
    return 0;
}

int yywrap() {
    return 1;
}

int yyerror(char *msg) {
 
     printf("Erreur syntaxique a la ligne %d, colonne %d  \n", numLigne, numColonne);
}
