/***********************************************************************
     * Name(s)  Wesley Pollock                                             *
     * Box(s):  4507                                                       *
     * Supplemental Problem 5: Commodities and Prices                      *
     *                                                                     *
     * Assignment for Tuesday, December 9th 2014                           *
     ***********************************************************************/

    /* *********************************************************************
     * Academic honesty certification:                                     *
     *   Written/online sources used:                                      *
     *     None                                                            *
     *                                                                     *
     *   Help obtained                                                     *
     *     None                                                            *
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

struct item {
  char name [51];
  double price;
  struct item * next;
};

/*
Pre-conditions :
   first it a pointer to the first struct item * node in the linked list. If 
   this is the first item to be added, the list must be initialized 
   (e.g. *first = NULL). first must be of type struct item **
   When prompted, the name of the item must be a string no longer than 50 
   characters long and the price must be a positive number
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
  first is a pointer to the first struct item * node in the linked list. If the
    linked list is empty *first must equal NULL
Post-conditions:
  priceSort sorts the items in the inventory, *first, from the lowest price to 
  to the highest
*/
void priceSort (struct item ** first);

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
      printf("s: sort the inventory by placing the items in ascending order of price\n");
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
        priceSort(&inventory);
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
  printf("[Inventory] \n");
  while (first != NULL)
    {
      printf("%s : $%.2lf \n",first->name,first->price);
      first = first->next;
    }
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

double a (double orig_price)
{
  return 0.90 * orig_price;
}

double b (double orig_price)
{
  return 2.50 + 1.15 * orig_price;
}

double c (double orig_price)
{
  return 12.00 + 9 * cos(orig_price);
}

void priceSort (struct item ** first)
{
  if (*first != NULL)
    {
      struct item * rest; //The list of the unsorted items
      struct item * keyPtr; //The current item being sorted
      struct item * searchPtr;
      struct item * prevPtr;
      rest = (*first)->next;
      (*first)->next = NULL;
      while (rest != NULL)
        {
          keyPtr = rest;
          /* Move the pointer to the list of the unsorted items down*/
          rest = rest->next;
          /*
            Insert keyPtr to front of the list, if it is less than the first
            item
          */
          if ((*first)->price > keyPtr->price)
            {
              keyPtr->next = *first;
              *first = keyPtr;
            }
          /*
            Else go through the sorted list and insert keyPtr to the correct 
            place
          */
          else
            {
              /* Start comparisons from the beginning of the list */
              searchPtr = (*first)->next;
              prevPtr = *first;
              /*
                Move down the list while price of the item at keyPtr is
                larger than the price at searchPtr 
              */
              while (searchPtr != NULL && searchPtr->price < keyPtr->price)
                {
                  prevPtr = searchPtr;
                  searchPtr = searchPtr->next;
                }
              /*insert keyPtr back into list at sorted position*/
              keyPtr->next = searchPtr;
              prevPtr->next = keyPtr;   
            }
        } 
    }
}
