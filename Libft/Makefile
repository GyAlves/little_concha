NAME = libft.a

CC = cc
FLAGS = -Wall -Werror -Wextra -I
INCLUDE = ../minishell.h
OBJ_DIR = obj/
LIBFT = libft/ft_strncmp.c

SRC = $(LIBFT)
OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(INCLUDE) -c $^ -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONE: all clean fclean re