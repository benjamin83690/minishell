CC		= gcc
CFLAGS	= -Wall -Wextra -Werror 
HEADER	= include
SRCS	= srcs/minishell.c
LIB		= libft.a
RM		= rm -f
NAME	= minishell
READ	= -lreadline ./include/libreadline.a -lcurses -o 
OBJS 	= $(SRCS:.c=.o)

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
