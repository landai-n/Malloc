/*
** calloc.c for malloc in /home/landai_n/rendu/malloc
** 
** Made by Nathanael Landais
** Login   <landai_n@epitech.net>
** 
** Started on  Wed Feb  4 00:05:46 2015 Nathanael Landais
** Last update Mon Feb  9 18:22:06 2015 Nathanael Landais
*/

#include	<string.h>
#include	<unistd.h>
#include	"malloc.h"

void		*calloc(size_t nmemb, size_t size)
{
  void		*new;

  if (nmemb == 0 || size == 0)
    return (NULL);
  new = malloc(size * nmemb);
  if (new == NULL)
    return (NULL);
  memset(new, 0, size * nmemb);
  return (new);
}
