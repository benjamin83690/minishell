CC		=	gcc
CFLAGS	=	-Wall -Wextra 
HEADER	=	include
SRCS	= 	srcs/minishell.c \
			srcs/arg.c \
			srcs/env.c \
			srcs/path_dir.c \
			srcs/print_init.c \
			srcs/redirection.c \
			srcs/struct_parse.c \
			srcs/utils1.c \
			srcs/utils2.c \
			srcs/utils3.c \
			srcs/utils4.c
LIB		=	libft.a
RM		=	rm -f
NAME	=	minishell
READ	=	-lreadline ./include/libreadline.a -lcurses -o 
OBJS 	=	$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			make -C libft
			make bonus -C libft
			mv libft/$(LIB) .
			$(CC) -o $@ $^ $(CFLAGS) $(LIB) -I$(HEADER) $(READ) $(NAME)

clean:
			$(RM) $(LIB) srcs/*.o lbft/*.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY : all clean fclean re
