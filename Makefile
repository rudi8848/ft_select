NAME = ft_select
SRCS = select.c
LIB = libft/libft.a
OBJ = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror
#HDRS = minishell.h libft/includes/ft_printf.h libft/includes/get_next_line.h libft/includes/libft.h
all:	$(NAME)

$(NAME): $(OBJ) $(LIB) $(HDRS)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L. $(LIB)

$(OBJ):	$(SRCS) $(LIB)
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