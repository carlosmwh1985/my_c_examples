/*
 ============================================================================
 Name        : order_list.c
 Author      : Carlos Granados
 Version     : 1.0
 Date        : 09.12.2020
 Copyright   : GNU
 Description : Program to use lists to order a random generated array...
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAX_NUM=200, NUM_COLS=5;

/* Definitions and functions associated with the list manipulation */

typedef struct list{int data; struct list *left; struct list *right;}list;

int is_empty(const list *l){return (l == NULL);}

/* Creates a list of one element */
list * create_list(int d)
{
  list * head = malloc(sizeof(list));
  head -> data = d;
  head -> left = NULL;
  head -> right = NULL;
  return head;
}

/* Adds one element to the list */
list * add_to_front(int d, list * h)
{
  list * head = create_list(d);
  head -> left = NULL;
  head -> right = h;
  h -> left = head;
  return head;
}

/* Delete the left one node...*/
list * del_left(list *a, list*b)
{
  list * l_temp;
  l_temp = a -> left;
  b -> left = l_temp;
  l_temp -> right = b;
  a -> left = NULL;
  a -> right = NULL;
  return b;
}

/* Delete the righ one node...*/
list * del_right(list *a, list*b)
{
  list * r_temp;
  r_temp = b -> right;
  a -> right = r_temp;
  r_temp -> left = a;
  b -> left = NULL;
  b -> right = NULL;
  return a;
}

/* Delete duplicates */
void del_duplicates(list * h)
{
  list * left;
  list * right;
  int a, b;

  while ( h != NULL ) {
    a = h -> data;
    left = h -> left;
    right = h -> right;
    if (right != NULL){
      b = right -> data;
      if (a == b) {
        h = del_right(h, right);
      }
    }
    if (left != NULL) {
      b = left -> data;
      if (a == b) {
        h = del_left(left, h);
      }
    }
    h = h -> right;
  }
}

/* Creates a list from an array*/
list * array_to_list(int d[], int size)
{
  list *head = create_list(d[0]);
  int i;
  for (i=1; i < size; i++){
    head = add_to_front(d[i], head);
  }
  return head;
}

void print_list(list *h)
{
  int i = 0;

  printf("\n");
  while (h != NULL) {
    printf("%d : ", h -> data);
    h = h -> right;
    if ((i+1) % NUM_COLS == 0)
      printf("\n");
    i++;
  }
  printf("\n\n");
}

/* Order the array */
int swap(list *a, list*b)
{
  list temp = *a;
  int da = a -> data;

  a -> data = b -> data;
  b -> data = da;
  return a -> data;
}

void bubble_list(list * h0)
{
  list * h1;
  int a, b, temp;

  while (h0 != NULL) {
    a = h0 -> data;
    h1 = h0 -> right;
    while (h1 != NULL){
      b = h1 -> data;
      if (a > b) {
        a = swap(h0, h1);
      }
      h1 = h1 -> right;
    }
    h0 = h0 -> right;
  }

}

/* Create a random array, of size MAX_NUM */

int * get_rand(void)
{
  static int data[MAX_NUM];
  int i = 0;

  /* Set random generator */
  srand((unsigned)time( NULL ));
  for (; i < MAX_NUM; i++){
    data[i] = rand() % 50;
  }

  return data;
}

void print_data(int d[])
{
  int i;

  printf("\n");
  for (i=0; i< MAX_NUM; i++){
    printf("%d\t", d[i]);
    if (((i+1) % NUM_COLS) == 0){
      printf("\n");
    }
  }
  printf("\n\n");
}

/* Main function */

int main(void)
{
  int i;
  int * data;
  list * list_of_rand = NULL;

  data = get_rand();

  printf("Random generated array:\n");
  print_data(data);

  /* Generate list and print it */
  list_of_rand = array_to_list(data, MAX_NUM);
  printf("\nRandom generated array in a list:\n");
  print_list(list_of_rand);

  /* Order the list and print it */
  bubble_list(list_of_rand);
  printf("\nOrdered list:\n");
  print_list(list_of_rand);

  /* Delete the duplicates */
  del_duplicates(list_of_rand);
  printf("\nList without duplicates:\n");
  print_list(list_of_rand);

  return 0;
}
