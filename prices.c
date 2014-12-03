 /***********************************************************************
     * Name(s)  Wesley Pollock                                             *
     * Box(s):  4507                                                       *
     * Supplemental Problem 5: Commodities and Prices                      *
     *                                                                     *
     * Assignment for December 9th, 2014                                   *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     none                                                            *
     *                                                                     *
     *   Help obtained                                                     *
     *     none                                                            *
     *                                                                     *
     *   My/our signature(s) below confirms that the above list of sources *
     *   is complete AND that I/we have not talked to anyone else          *
     *   (e.g., CSC 161 students) about the solution to this problem       *
     *                                                                     *
     *   Signature:                                                        *
     ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const maxNameLen = 50;
struct item {
  char name [50];
  double price;
  struct item * next;
};

/*
Pre-conditions :
   first it a pointer to the first struct item * node in the linked list. If 
   this is the first item to be added, the list must be initialized 
   (e.g. *first = NULL). first must be of type struct item **
Post-conditions:
   addItem prompts the users to enter the item name and price then adds the item
   to the front of the list
*/
void addItem(struct item ** first);

/*
Pre-conditions :
   first is the first struct item * node in the linked list
Post-conditions:
   print prints out the name field in each of the struct item nodes in the 
   linked list on a new line
*/
void print(struct item * first);

/*
  The following three procedures a,b,c are three arbitary example procedures 
  to manipulate the price of items in the linked list
*/

/*
Pre-conditions :
  orig_price is the original price of the item (type double)
Post-conditions:
  a returns the original price reduced by 10% (type double)
*/
double a (double orig_price);

/*
Pre-conditions :
  orig_price is the original price of the item (type double)
Post-conditions:
  b returns the original price increased linearly
*/
double b (double orig_price);

/*
Pre-conditions :
  orig_price is the original price of the item (type double)
Post-conditions:
  c returns the original price manipulated with a cosine function 
*/
double c (double orig_price);

/*
Pre-conditions :
  first is a pointer to the first struct item * node in the linked list. If the
    linked list is empty *first must equal NULL
  priceFunc is a function which manipulates a number of type double and returns
    a number of type double  
Post-conditions:
  map applies the function priceFunc to the price field in each of the item 
  nodes in the linked list *first
*/
void map (struct item ** first, double priceFunc (double));

/*
Pre-conditions :
  none
Post-conditions:
  main creates a menu of options of the above procedures from which the user 
  can choose. The menu will continue to be shown until the user chooses the quit
  option
*/ 
int main()
{
  struct item * inventory = NULL;
  char option;
  while(1)
    {
      printf("Store-inventory options:\n");
      printf("e: add an item (cost, name) to the inventory\n");
      printf("p: print all items in the inventory\n");
      printf("a: apply function \"a\" to all prices in the inventory\n");
      printf("b: apply function \"b\" to all prices in the inventory\n");
      printf("c: apply function \"c\" to all prices in the inventory\n");
      //printf("s: sort the inventory by placing the items in ascending order of price\n");
      printf("q: quit\n");
      printf("Input single character option: ");
      option = getchar();
      while(getchar() != '\n');
      switch (option) {
      case 'e':
        addItem(&inventory);
        break;
      case 'p':
        print(inventory);
        break;
      case 'a':
        map(&inventory,a);
        break;
      case 'b':
        map(&inventory,b);
        break;
      case 'c':
        map(&inventory,c);
        break;
      case 's':
        printf("Option %c is not yet implimented\n",option);
        break;
      case 'q':
        printf("Quitting\n");
        return 0;
      default:
        printf("Command not recongized\n");
        break;
      }
      printf("\n");
    }
}

void addItem(struct item ** first){
  struct item * newItem = (struct item *) malloc (sizeof(struct item));
  printf("Enter item name: ");
  char ch = getchar();
  int i = 0;
  while(ch != '\n')
    {
      newItem->name[i] = ch;
      ch = getchar();
      i++;
    }
  double p;
  printf("Enter price: ");
  scanf("%lf",&p);
  while(getchar() != '\n');
  newItem->price = p;
  newItem->next = *first;
  *first = newItem;
}

void print(struct item * first)
{
  printf("(");
  char * sep = "";
  while (first != NULL)
    {
      printf("%s\"%s : $%.2lf\"",sep,first->name,first->price);
      sep = " ";
      first = first->next;
    }
  printf(")\n");
}

void map(struct item ** first, double priceFunc(double))
{
  struct item * temp = *first;
  while (*first != NULL)
    {
      (*first)->price = priceFunc((*first)->price);
      *first = (*first)->next;
    }
  *first = temp;
}

/* reduce a price by 10% */
double a (double orig_price)
{
  return 0.90 * orig_price;
}

/* increase a price using a linear formula */
double b (double orig_price)
{
  return 2.50 + 1.15 * orig_price;
}

/* change prices up and down in a curious way, using the cosine function
from math.h (compile with -lm) */
double c (double orig_price)
{
  return 12.00 + 9 * cos(orig_price);
}

