##
## Makefile for malloc in /home/louis_c/rendu/PSU_2014_malloc
## 
## Made by Bastien Louis
## Login   <louis_c@epitech.net>
## 
## Started on  Tue Feb  3 11:48:53 2015 Bastien Louis
## Last update Wed Feb  4 20:16:31 2015 Nathanael Landais
##

NAME		=	libmy_malloc.so

SRCS            =	sources/malloc.c		\
			sources/realloc.c		\
			sources/calloc.c		\
			sources/free.c			\

INCLUDES	=	-I includes/

OBJS            =       $(SRCS:.c=.o)


CFLAGS          =	-Wall -Wextra -W -fPIC -shared $(INCLUDES)
CFLAGS		+=	-g


all             :       $(NAME)


$(NAME)         :       $(OBJS)
			gcc $(OBJS) $(CFLAGS) -o $(NAME)

clean           :
			rm -f $(OBJS)

fclean          :       clean
			rm -f $(NAME)

re              :       fclean all

