# Program
NAME = philo

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

# Directories
SRC_DIR = src/
OBJ_DIR = objs/

# Find all .c files
SRCS = $(shell find $(SRC_DIR) -type f -name "*.c")

OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

# Libraries
LIBS = -lpthread

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LIBS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) ./$(NAME)

re: fclean all

.PHONY: all clean fclean re