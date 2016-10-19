#include	"malloc.h"

int main()
{
  /* free(malloc(50000)); */
  /* free(malloc(30000)); */
  malloc(3000);
  malloc(3000);
  malloc(3000);
  show_alloc_mem();
}
