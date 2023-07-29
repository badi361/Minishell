SRCS		=		minishell.c check.c routine.c list_foncs.c utils.c utils2.c routine_v2.c routine_v3.c

LIBFT		=		libft/libft.a

OBJS		=		$(SRCS:.c=.o)

NAME		=		minishell

CC			=		gcc -Wall -Wextra -Werror -g

CFLAGS		=		

RM			=		rm -rf

$(LIBFT):
			make re -C ./libft

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -lreadline $(OBJS) libft/libft.a  -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re