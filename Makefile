HEADER		=	includes/philo.h

SRCS_ONE		=	srcs_one/main.c srcs_one/parsing.c

#SRCS_P		=	srcs_push_swap/check_args.c srcs_push_swap/main.c srcs_push_swap/operations.c \
				srcs_push_swap/operations_bis.c srcs_push_swap/operations_ter.c srcs_push_swap/stack.c \
				srcs_push_swap/sort.c srcs_push_swap/little_range_algo.c  \
				srcs_push_swap/sort_utils.c srcs_push_swap/min_max_algo.c \
				 srcs_push_swap/huge_sort.c srcs_push_swap/giga_huge_sort.c srcs_push_swap/sort_utils_bis.c

NAME		=	philo_one

#NAME_P		=	push_swap

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

OBJS_ONE	=	$(SRCS_ONE:.c=.o)

#OBJS_P		=	$(SRCS_P:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS_ONE) $(HEADER)
			$(CC) -o $(NAME) $(SRCS_ONE)

#$(NAME_P):	$(OBJS_P) $(HEADER_P)
#			$(MAKE) -C ./libft
#			cp libft/libft.a .
#			$(CC) -o $(NAME_P) $(SRCS_P) $(LIBFT)

all :	$(NAME)

clean : 
		rm -rf $(OBJS_ONE)

fclean :
		rm -rf $(OBJS_ONE) $(NAME)
	
re :	fclean all

.PHONY : clean fclean re all