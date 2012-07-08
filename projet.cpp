/*
  Projet Algorithmique S12 P2012, Quentin Barrand S2A2

  Ce programme et son code source sont placés sous licence Creative Commons BY 
  http://creativecommons.org/licenses/by/3.0/
*/
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;



/* 
  La structure line contient une chaine de caractères et un pointeur
  sur line qui contient l'adresse du prochain maillon de la chaîne.
*/
struct line
{
  string data;
  line *next;
};



/* Prototypes des fonctions utilisées dans le programme */
line* quickSort(line*, int);
void addToList(line*, line*);



/* 
  Cette fonction prend en paramètre deux pointeurs sur une line :
  - lineToAdd est le maillon à ajouter à une liste chaînée
  - list est le premier maillon de la liste en question.
  Elle ne retourne ni n'affiche rien et n'alloue pas de mémoire.
*/
void addToList(line* lineToAdd, line* list)
{
  line* current(list);
  
  while(current->next != NULL)  
    current = current->next;
  
  current->next = lineToAdd;
}



/* 
  Cette fonction est une implémentation de l'algorithme QuickSort pour les 
  chaînes stockées dans une liste chaînée. 
  Elle prend en paramètre un pointeur sur line qui est le premier élément de 
  la liste que l'on veut trier et un entier qui correspond au nombre de 
  maillons de la liste.
  Elle retourne un pointeur sur line : l'adresse du premier maillon de la
  chaine. Elle n'affiche rien et n'alloue pas de mémoire.
*/
line* quickSort(line* list, int nbLinks)
{
  int nbLinksList1(0), nbLinksList2(0);
  line *current(list), *pivot(NULL), *list1(NULL), *list2(NULL);

  if(nbLinks > 0)
  {      
    /* On détermine l'adresse du pivot */
    for(int i(0); i <= nbLinks/2; i++, current = current->next)
      pivot = current;
      
    current = list;

    for(int i(0); i < nbLinks; i++)
    {
      /* 
        On est obligé de faire la manip suivante pour ne pas partir dans 
        une boucle infinie dans addToList()
      */
      line* nextCurrent(current->next);
      current->next = NULL;

      if(current != pivot)
      {
        if((current->data).compare(pivot->data) < 0)
		    {
		      if(list1 == NULL)
		        list1 = current;
		      else
		        addToList(current, list1);	
		
		      nbLinksList1++;
		    }

        else
		    { 
		      if(list2 == NULL)
		        list2 = current;
		      else
		        addToList(current, list2);
		  
		      nbLinksList2++;
		    }
      }

      current = nextCurrent;
    }

    /* 
      On rappelle la fonction pour traiter complètement les deux listes par
      récursivité.
    */
    list1 = quickSort(list1, nbLinksList1);
    list2 = quickSort(list2, nbLinksList2);
  }
  
  else
    return NULL;
  
  /* On rejoint les deux listes */
  if(list1 == NULL)
    list1 = pivot;
  else
  {
    current = list1;
    
    while(current->next != NULL)
      current = current->next;

    current->next = pivot;
  }

  pivot->next = list2;

  return list1;
}



int main()
{
  int nbLinks(0);
  line *list(NULL), *current(NULL), *previous(NULL);

  /* Pour récupérer la locale du système et l'appliquer au programme */
  setlocale(LC_ALL, "");

  /* Cette boucle while() permet de lire l'intégralité de l'entrée standard */
  while(cin) 
  {
    /* 
      On alloue dynamiquement une line qu'on nomme current pour chaque 
      nouvelle ligne. 
    */
    current = new line;
    getline(cin, current->data);

    list = current;

    if(list == NULL)
      list->next = NULL;
    else
      list->next = previous;

	  previous = list;

	  nbLinks++;
  }

  /* On appelle la fonction de tri */
  list = quickSort(list, nbLinks);

  /* Boucle finale d'affichage et de désallocation */
  current = list->next;
  
  delete list;
  
  while(current != NULL)
  { 
    cout << current->data << endl;
    delete current;
    current = current->next;
  }
  delete current;

  return 0;
}