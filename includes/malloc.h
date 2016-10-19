/*
** malloc.h for malloc in /home/landai_n/rendu/malloc/includes
** 
** Made by Nathanael Landais
** Login   <landai_n@epitech.net>
** 
** Started on  Tue Feb  3 14:20:39 2015 Nathanael Landais
** Last update Mon Feb  9 19:09:28 2015 Nathanael Landais
*/

#ifndef			MALLOC_H
# define		MALLOC_H

# define		MIN_MALLOC_SIZE		1024
# define		MALLOC_PADDING		4096

# include		<pthread.h>
# include		<unistd.h>

typedef struct		s_malloc_block
{
  struct s_malloc_block	*prev;
  struct s_malloc_block	*next;
  int			is_free;
  unsigned int		size;
}			t_malloc_block;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			*calloc(size_t nmemb, size_t size);
void			show_alloc_mem();

void			split_block(size_t size, t_malloc_block *block);
void			init_new_block(t_malloc_block *block, size_t size, t_malloc_block *last);
void			*malloc_new_block(size_t size);
t_malloc_block		*find_free_block(t_malloc_block *elem, size_t size);
void			fusion(t_malloc_block *first, t_malloc_block *second);
size_t			getSize(size_t size);

extern pthread_mutex_t	malloc_lock;
extern t_malloc_block	*first_allocated;
extern t_malloc_block	*last_allocated;

#endif

