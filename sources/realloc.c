/*
** realloc.c for realloc in /home/louis_c/rendu/PSU_2014_malloc/sources
** 
** Made by Bastien Louis
** Login   <louis_c@epitech.net>
** 
** Started on  Tue Feb  3 11:55:10 2015 Bastien Louis
** Last update Mon Feb  9 18:33:17 2015 Nathanael Landais
*/

#include	<string.h>
#include	<unistd.h>
#include	"malloc.h"

void			*realloc(void *ptr, size_t size)
{
  void			*new;
  t_malloc_block	*origin;

  if (ptr == NULL)
    return (malloc(size));
  origin = ptr - (sizeof(t_malloc_block));
  if (origin->size >= size)
    {
      pthread_mutex_lock(&malloc_lock);
      split_block(getSize(size), origin);
      pthread_mutex_unlock(&malloc_lock);
      return (ptr);
    }
  if ((new = malloc(size * sizeof(*new))) == NULL)
    return (NULL);
  memcpy(new, ptr, origin->size);
  free(ptr);
  return (new);
}
