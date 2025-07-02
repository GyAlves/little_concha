# Program
NAME = minishell

# Compiler
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -Iincludes

# Directories
LIBFT = Libft/libft.a
SRC_DIR = src/
OBJ_DIR = objs/

# Find all .c files
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Libraries
LIBS = -lreadline

all: $(NAME)

v: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=suppfile.sup ./$(NAME)

$(LIBFT):
	make -C ./Libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LIBFT) $(LIBS)

clean:
	$(RM) -r $(OBJ_DIR)
	make clean -C ./Libft

fclean: clean
	$(RM) ./$(NAME)
	make fclean -C ./Libft

re: fclean all

.PHONY: all clean fclean re