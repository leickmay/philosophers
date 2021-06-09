HEADER		=	includes/philo.h

SRCS		=	srcs/main.c srcs/parsing.c

#SRCS_P		=	srcs_push_swap/check_args.c srcs_push_swap/main.c srcs_push_swap/operations.c \
				srcs_push_swap/operations_bis.c srcs_push_swap/operations_ter.c srcs_push_swap/stack.c \
				srcs_push_swap/sort.c srcs_push_swap/little_range_algo.c  \
				srcs_push_swap/sort_utils.c srcs_push_swap/min_max_algo.c \
				 srcs_push_swap/huge_sort.c srcs_push_swap/giga_huge_sort.c srcs_push_swap/sort_utils_bis.c

NAME		=	philo

#NAME_P		=	push_swap

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

OBJS	=	$(SRCS:.c=.o)

#OBJS_P		=	$(SRCS_P:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS) $(HEADER)
			$(CC) -o $(NAME) $(SRCS)

#$(NAME_P):	$(OBJS_P) $(HEADER_P)
#			$(MAKE) -C ./libft
#			cp libft/libft.a .
#			$(CC) -o $(NAME_P) $(SRCS_P) $(LIBFT)

all :	$(NAME)

clean : 
		rm -rf $(OBJS)

fclean :
		rm -rf $(OBJS) $(NAME)
	
re :	fclean all

.PHONY : clean fclean re all