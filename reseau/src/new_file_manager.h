#include<stdlib.h>;
#define "new_file_manager.h"


typedef struct node * tree;
typedef struct cellule * cell;
typedef struct liste * linked_list;


struct cellule
{
  tree arbre;
  cell suivant;
};

struct node
{
  tree pere;
  char * valeur;
  linked_list fils;
};

struct liste
{
  cell first;
  int taille;
};

bool isEmpty( tree T)
{
	return T == NULL;
}

bool isEmpty( linked_list l)
{
	return l->first == NULL;
}





void addCell (linked_list l,cell c)
{
  l->taille++;
  c->suivant = l->first;
  l->first = c->suivant;
}

cell pere(linked_list l, cell c)
{
  cell cel;
  if (l->first == c)
    return NULL;
  else
    {
      cel = l->first;
      while (c->suivant =! NULL)
	{
	  if (cel->suivant == c;)
	    return cel;
	  else
	    cel = cel->suivant;
	}
    }
  exit EXIT_FAILURE;
}

void removeCell(linked_list l, cell c)
{
  cell p = pere(l, c);
  if (p == NULL)
    {
      p = l->first->suivant;
      free(l->first);
      l->first = p;
    }
  else
    p->suivant = p->suivant->suivant;
  free(c);
  l->taille--;
}

linked_list  createLL()
{
  linked_list l =(linked_list)  malloc(sizeof(struct liste));
  return l;
}

cell createCell()
{
  cell c =(cell)  malloc(sizeof(struct cellule));
  return c;
}

void addFils(tree t, cell newfils)
{
  addCell(t->fils, newfils);
}

cell find (linked_list  l, char* s)
{
  cell c = l->first;
  bool trouve = false;
  while (c !=NULL)
    {
      if (strcmp(c->arbre->valeur, s))
	{return c;}
      else
	{ c = c->suivant;}
    }
  return NULL;
}

tree goF(tree t, char* s)
{
  linked_list  l = &(t->fils);
  return ((find(l, s))->arbre);
  
}

tree goP(tree t)
{
  return t->pere;
}

void removeFils(tree t, char * s)
{
  cell c = findCell(t->fils, s);
  removeCell(t->fils, c);
}

tree createTree(char * s)
{
  tree t =(tree)  malloc(sizeof(struct node));
  t->fils = createLL();
  return t;
}
