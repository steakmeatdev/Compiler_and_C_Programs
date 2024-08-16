#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct occ
{
    int value;
    struct occ *next;
};
struct pos
{
    struct occ *pointer;
    struct pos *next;
};
struct node
{
    char w[100];
    struct node *lc;
    struct node *rc;
    struct occ *op;
};
int asciisum(char *word)
{
    if (*word == 0)
    {
        return 0;
    }
    else
    {
        return((*word) + asciisum(word + 1));
    }
}
void makebst(struct node **root, char *word, int p)
{
    if ((*root) == NULL)
    {
        (*root) = (struct node*)malloc(sizeof(struct node));
        strcpy(((*root)->w), word);
        (*root)->lc = NULL;
        (*root)->rc = NULL;
        (*root)->op = (struct occ*)malloc(sizeof(struct occ));
        (*root)->op->value = p;
        (*root)->op->next = NULL;
    }
    else
    {
        if ((asciisum(word)) == (asciisum((*root)->w)))
        {
            struct occ *m;
            m = (*root)->op;
            while(m->next != NULL)
            {
                m = m->next;
            }
            if (m->value != p)
            {
                m->next = (struct occ*)malloc(sizeof(struct occ));
                m->next->value = p;
                m->next->next = NULL;
            }
        }
        if (((asciisum(word)) < (asciisum((*root)->w))) && ((*root)->lc != NULL))
        {
            makebst(&((*root)->lc),word,p);
        }
        if (((asciisum(word)) > (asciisum((*root)->w))) && ((*root)->rc != NULL))
        {
            makebst(&((*root)->rc),word,p);
        }
        if (((asciisum(word)) < (asciisum((*root)->w))) && ((*root)->lc == NULL))
        {
            (*root)->lc = (struct node*)malloc(sizeof(struct node));
            strcpy(((*root)->lc->w), word);
            (*root)->lc->lc = NULL;
            (*root)->lc->rc = NULL;
            (*root)->lc->op = (struct occ*)malloc(sizeof(struct occ));
            (*root)->lc->op->value = p;
            (*root)->lc->op->next = NULL;
        }
        if (((asciisum(word)) > (asciisum((*root)->w))) && ((*root)->rc == NULL))
        {
            (*root)->rc = (struct node*)malloc(sizeof(struct node));
            strcpy(((*root)->rc->w), word);
            (*root)->rc->lc = NULL;
            (*root)->rc->rc = NULL;
            (*root)->rc->op = (struct occ*)malloc(sizeof(struct occ));
            (*root)->rc->op->value = p;
            (*root)->rc->op->next = NULL;
        }
    }
}
void listocc(struct node *root, struct pos **lsp, char *word)
{
    if(root != NULL)
    {
        if ((asciisum(word)) == asciisum(root->w))
        {
            if ((*lsp) == NULL)
            {
                (*lsp) = (struct pos*)malloc(sizeof(struct pos));
                (*lsp)->pointer = root->op;
                (*lsp)->next = NULL;
            }
            else
            {
                struct pos *tmp = (*lsp);
                while(tmp->next != NULL)
                {
                    tmp = tmp->next;
                }
                tmp->next = (struct pos*)malloc(sizeof(struct pos));
                tmp->next->pointer = root->op;
                tmp->next->next = NULL;
            }
        }
        else if ((asciisum(word)) > asciisum(root->w))
        {
            listocc(root->rc, lsp, word);
        }
        else
        {
            listocc(root->lc, lsp, word);
        }
    }
}
int sntnb(struct pos *lsp)
{
    if (lsp != NULL)
    {
        int nb = 0;
        struct occ *tmp1 = lsp->pointer;
        if (lsp->next != NULL)
        {
            struct pos *tmp2 = lsp->next;
            struct occ *tmp3 = tmp2->pointer;
            while((tmp2 != NULL) && (tmp1 != NULL))
            {
                tmp3 = tmp2->pointer;
                while((tmp3 != NULL) && (nb == 0))
                {
                    if(tmp1->value == tmp3->value)
                    {
                        nb = tmp3->value;
                    }
                    tmp3 = tmp3->next;
                }
                if (nb != 0)
                {
                    nb = 0;
                    tmp2 = tmp2->next;
                }
                else
                {
                    tmp1 = tmp1->next;
                    nb = 0;
                }
            }
            if(tmp1 == NULL) return 0;
            else return (tmp1->value);
        }
        else return lsp->pointer->value;
    }
    else return 0;
}
int exist1(struct node *root, char *word)
{
    if (root == NULL)
    {
        return 0;
    }
    else if (asciisum(root->w) == asciisum(word))
    {
        return 1;
    }
    else
    {
        return(exist1((root->lc),word) + exist1((root->rc),word));
    }
}
int main()
{
    struct node *root = NULL;
    char word[30];
    char c;
    FILE *fp;
    int snt = 1;
    int i = 0;
    printf("Le fichier que vous allez l'ouvrir ne doit pas contenir des caracteres speciaux comme (é è ç à...)\n\n");
    printf("entrer le nom du fichier (ou le chemin), puis entrer une phrase a chercher dans le fichier texte\n\n(<201 caractere pour la phrase & <31 caractere pour chaque mot)\n");
    char filename[100];
    scanf("%s\n",filename);
    fp = fopen("testfile.txt","r");
    c = fgetc(fp);
	while (c != EOF)
	{
		while ((c != ' ') && (c != '.') && (c != '!') && (c != '\n') && (c != EOF) && (c != ',') && (c != ':') && (c != '(') && (c != ')') && (c != '?'))
		{
			word[i] = c; i++; c = fgetc(fp);
		}
		if((asciisum(word)) != 0)
		{
			makebst(&root, word, snt);
		}
		for (i = 0 ; i <= 29 ; i++)
		{
			word[i] = 0;
		}
		i = 0;
		if ((c == '.') || (c == '!') || (c == EOF) || (c == '?')) 
		{
			snt++;
		}
		if (c != EOF)
		{
			c = fgetc(fp);
		}
	}
    fclose(fp);
    int j = 0;
    int v;
    i = 0;
    char sentence[200];
    struct pos *occlist = NULL;
    gets(sentence);
	c = sentence[i];
 	while(i <= 199)
    {
    	for (j = 0 ; j <= 29 ; j++)
        {
            word[j] = 0;
        }
        j = 0; 
        if (i < 200)
		{
			c = sentence[i];
		} 
        while ((c != ' ') && (c != 0) && (c != '.') && (c != '!') && (c != '\n') && (c != ',') && (c != ':') && (c != '(') && (c != ')') && (c != '?'))
		{
			word[j] = c; 
			j++; 
			i++;
            if (i < 200)
			{ 
				c = sentence[i];
			}
            else 
			{
				c = 0;
			}
		}
        if ((asciisum(word) != 0) && (v = exist1(root, word)))
        {
            listocc(root, &occlist, word);
        }
        i++;
        
    }
    v = sntnb(occlist);
	printf("\nle numero de la phrase que vous cherchez est %d\n",v);
    return 0;
}
