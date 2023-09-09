SRCS		=		minishell.c check.c routine.c list_foncs.c utils.c utils2.c routine_v2.c routine_v3.c utils3.c \
					routine_v4.c routine_v5.c cd.c routine_v6.c	routine_v7.c routine_v8.c here_doc.c routine_v9.c \
					routine_v10.c routine_v11.c

LIBFT		=		libft/libft.a

OBJS		=		$(SRCS:.c=.o)

NAME		=		minishell

CC			=		gcc -Wall -Wextra -Werror -g

CFLAGS		=		

RM			=		rm -rf

all:		$(NAME)

$(LIBFT):
			make re -C ./libft

$(NAME):	$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) -lreadline $(OBJS) libft/libft.a  -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)
			make fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re