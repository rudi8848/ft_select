NAME = ft_select
SRCS = list.c keys.c signals.c exit.c termcap.c
LIB = libft/libft.a
OBJ = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -ltermcap
HDRS = ft_select.h

all:	$(NAME)

$(NAME): $(OBJ) $(LIB) $(HDRS)
	gcc -o $(NAME) $(CFLAGS) $(OBJ) -L. $(LIB)

$(OBJ):	$(SRCS) $(LIB) $(HDRS)
	gcc -c $(SRCS) -g3

$(LIB):
	make -C libft

clean:
	/bin/rm -f $(OBJ)
	make clean -C libft

fclean: clean
	@/bin/rm -f $(NAME)
	make fclean -C libft

re: fclean all