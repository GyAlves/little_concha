NAME = libft.a

CC = cc
FLAGS = -Wall -Werror -Wextra -I
INCLUDE = ../minishell.h
OBJ_DIR = obj/
LIBFT = libft/ft_strncmp.c libft/ft_strlen.c libft/ft_calloc.c libft/ft_substr.c libft/ft_split.c libft/ft_strchr.c libft/ft_memcpy.c libft/ft_strjoin.c libft/ft_strdup.c libft/ft_strlcpy.c libft/free_matrix.c

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