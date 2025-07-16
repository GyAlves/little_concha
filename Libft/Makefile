NAME = libft.a

CC = cc
FLAGS = -Wall -Werror -Wextra -I../includes
INCLUDE = ../minishell.h
OBJ_DIR = obj/
LIBFT = libft/ft_strncmp.c libft/ft_strlen.c libft/ft_calloc.c libft/ft_substr.c  \
		libft/ft_split.c libft/ft_strchr.c libft/ft_memcpy.c libft/ft_strjoin.c   \
		libft/ft_strdup.c libft/ft_strlcpy.c libft/ft_atoi.c libft/ft_putstr_fd.c \
		libft/ft_arrlen.c libft/ft_check_args.c libft/ft_isalpha.c libft/ft_isalnum.c \
		libft/ft_strndup.c libft/ft_strcmp.c libft/ft_itoa.c

SRC = $(LIBFT)
OBJ = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)%.o: %.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) -c $^ -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONE: all clean fclean re