##
## Makefile for PSU_2015_philo
##
## Made by	Adrien WERY
## Login	wery_a
##
## Started on	Mon Feb 01 15:12:24 2016 Adrien WERY
## Last update	Mon Feb 01 15:12:24 2016 Adrien WERY
##

CC		=	gcc

RM		=	rm -rf

NAME	=	philo

SRC		= 	main.c \
			philo.c

CFLAGS	=	-W -Wall -Wextra -Werror -D_REENTRANT -ansi -pedantic

LDFLAGS	=	-lpthread -L. -lriceferee

OBJ		=	$(SRC:.c=.o)

$(NAME)	: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS)	-o $(NAME)

all		:	$(NAME)

clean	:
	$(RM) $(OBJ)

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
