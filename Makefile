HEADER		=	includes/philo.h

SRCS		=	srcs/main.c \
				srcs/parsing.c \
				srcs/error.c \
				srcs/forks.c \
				srcs/states.c \
				srcs/thread.c

NAME		=	philo

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

OBJS	=	$(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(HEADER)
			$(CC) -o $(NAME) $(SRCS)

all :	$(NAME)

clean : 
		rm -rf $(OBJS)

fclean :
		rm -rf $(OBJS) $(NAME)
	
re :	fclean all

.PHONY : clean fclean re all