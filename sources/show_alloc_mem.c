/*
** show_alloc_mem.c for show_alloc_mem in /home/louis_c/rendu/PSU_2014_malloc/sources
** 
** Made by Bastien Louis
** Login   <louis_c@epitech.net>
** 
** Started on  Tue Feb  3 11:57:57 2015 Bastien Louis
** Last update Mon Feb  9 19:06:17 2015 Nathanael Landais
*/

#include	<stdio.h>
#include	"malloc.h"

void		show_alloc_mem()
{
  t_malloc_block	*block;

  block = first_allocated;
  printf("break : %p\n", sbrk(0));
  while (block != NULL && block->next != last_allocated)
    {
      if (block->is_free == 0)
      	printf("%p - %p : %i octets\n", block, block->next, block->size);
      block = block->next;
    }
}
