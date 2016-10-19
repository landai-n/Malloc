/*
** free.c for free in /home/louis_c/rendu/PSU_2014_malloc/sources
** 
** Made by Bastien Louis
** Login   <louis_c@epitech.net>
** 
** Started on  Tue Feb  3 11:55:15 2015 Bastien Louis
** Last update Tue Feb 10 19:34:15 2015 Nathanael Landais
*/

#include	<stdio.h>
#include	"malloc.h"

void			fusion(t_malloc_block *first, t_malloc_block *second)
{
  t_malloc_block	*next;

  next = second->next;
  first->next = next;
  if (next != NULL)
    next->prev = first;
  first->size += second->size + sizeof(t_malloc_block);
}

void			free(void *ptr)
{
  t_malloc_block	*block;

  if (ptr == NULL)
      return;
  pthread_mutex_lock(&malloc_lock);
  block = ptr - sizeof(t_malloc_block);
  if (block->is_free)
    {
      pthread_mutex_unlock(&malloc_lock);
      return ;
    }
  block->is_free = 1;
  if (block->prev != NULL && block->prev->is_free)
    fusion(block->prev, block);
  if (block->next != NULL && block->next->is_free)
    fusion(block, block->next);
  pthread_mutex_unlock(&malloc_lock);
}
