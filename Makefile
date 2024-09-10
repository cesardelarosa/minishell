NAME = minishell
BONUS_NAME = minishell_bonus

INCLUDE_DIR = include
SRC_DIR = src
BONUS_DIR = bonus
OBJ_DIR = obj
LIBFT_DIR = libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./$(INCLUDE_DIR) -I./$(LIBFT_DIR)
LDFLAGS = -lreadline -L$(LIBFT_DIR) -lft
SANITIZE = -fsanitize=address -g

LIBFT = $(LIBFT_DIR)/libft.a

COMMON_SRC = builtin.c main.c parse.c prompt.c prompt_utils.c signals.c
NO_BONUS_SRC = exec.c
BONUS_SRC = exec_bonus.c wildcards_bonus.c

SRC_FILES = $(COMMON_SRC) $(NO_BONUS_SRC)
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

BONUS_FILES = $(COMMON_SRC) $(BONUS_SRC)
BONUS_OBJ_FILES = $(BONUS_FILES:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJ_FILES) $(LDFLAGS) -o $(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ_FILES) $(LIBFT)
	$(CC) $(CFLAGS) $(SANITIZE) $(BONUS_OBJ_FILES) $(LDFLAGS) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	rm -f $(LIBFT)

re: fclean all

double: all bonus

.PHONY: all bonus clean fclean re double
