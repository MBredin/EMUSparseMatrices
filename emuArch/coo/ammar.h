typedef struct element_ {
  int row; /* the row index for the element */
  int column; /* the column index for the element */
  int value; /* the value of the element */

  struct element *next; /* next element */
  struct element *prev; /* previous element */
} element;

typedef struct list_ {
  int size; /* the size of the list (non zero values number) */

  element *head; /* first element in the list */
  element *tail; /* last element in the list */
} list;
