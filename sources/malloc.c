/*
** malloc.c for malloc in /home/louis_c/rendu/PSU_2014_malloc/sources
** 
** Made by Bastien Louis
** Login   <louis_c@epitech.net>
** 
** Started on  Tue Feb  3 11:55:02 2015 Bastien Louis
** Last update Fri Feb 13 15:15:00 2015 Nathanael Landais
*/

#include		<stdio.h>
#include		"malloc.h"

pthread_mutex_t		malloc_lock;
t_malloc_block		*first_allocated = NULL;
t_malloc_block		*last_allocated = NULL;

void			*malloc(size_t size)
{
  t_malloc_block	*new;

  if (first_allocated == NULL)
    pthread_mutex_init(&malloc_lock, NULL);
  pthread_mutex_lock(&malloc_lock);
  size = getSize(size);
  if ((new = find_free_block(first_allocated, size)) == NULL)
    {
      new = malloc_new_block(size);
    }
  else
    if (new->size > size)
	split_block(size, new);
  if (new == NULL)
    {
      pthread_mutex_unlock(&malloc_lock);
      return (NULL);
    }
  new->is_free = 0;
  if (first_allocated == NULL)
    first_allocated = new;
  pthread_mutex_unlock(&malloc_lock);
  return ((void *)new + sizeof(t_malloc_block));
}

void			split_block(size_t size, t_malloc_block *block)
{
  t_malloc_block	*second_block;
  size_t		size_second;

  if (block->size + sizeof(t_malloc_block) <= (unsigned int)getpagesize() * 2)
    return;
  if (block->size <= size + sizeof(t_malloc_block))
    return;
  second_block = (t_malloc_block *)((void *)block + size);
  size_second = (block->size + sizeof(t_malloc_block)) - size;
  init_new_block(second_block, size_second, block);
  block->size = size - sizeof(t_malloc_block);
}

void			init_new_block(t_malloc_block *block, size_t size, t_malloc_block *last)
{
  block->is_free = 1;
  block->size = size - sizeof(t_malloc_block);
  block->prev = last;
  block->next = NULL;
  if (last != NULL)
    {
      block->next = last->next;
      if (block->next != NULL)
  	block->next->prev = block;
      last->next = block;
    }
  else
    {
      last_allocated = block;
    }
}

void			*malloc_new_block(size_t size)
{
  t_malloc_block	*block;

  if (last_allocated == NULL)
    block = sbrk(size);
  else
    {
      if (brk((void*)last_allocated + last_allocated->size + sizeof(t_malloc_block) + size) != 0)
  	block = NULL;
      else
  	block = (void*)last_allocated + last_allocated->size + sizeof(t_malloc_block);
    }
  if (block == NULL || block == (void *)-1)
    return (NULL);
  init_new_block(block, size, last_allocated);
  last_allocated = block;
  return (block);
}

t_malloc_block		*find_free_block(t_malloc_block *elem, size_t size)
{
  t_malloc_block	*itr;
  int			i;

  itr = elem;
  i = 0;
  while (itr != NULL && itr != last_allocated)
    {
      if (itr->is_free && itr->size >= size)
	return (itr);
      itr = itr->next;
      i++;
    }
  return (NULL);
}

size_t			getSize(size_t size)
{
  size_t		total_size;

  total_size = getpagesize();
  while (total_size < size + sizeof(t_malloc_block))
    total_size = total_size << 1;
  return (total_size);
}
