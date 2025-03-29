NAME     := minishell
SRC_DIR  := src
INC_DIR  := include
LFT_DIR  := libft
OBJ_DIR  := obj

SRCS     := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS     := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC       := gcc
CFLAGS   := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LFT_DIR)
LDLIBS   := -lreadline

all: $(NAME)

$(NAME): libft $(OBJS)
	@printf "\033[1;33m[BUILD] Linking $(NAME)...\033[0m\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT_DIR)/libft.a $(LDLIBS)
	@printf "\033[1;32m[OK] ✅ Compilation of $(NAME) completed.\033[0m\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[1;33m[BUILD] Compiling object: $<\033[0m\n"
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	@printf "\033[1;33m[BUILD] Building libft...\033[0m\n"
	$(MAKE) complete -C $(LFT_DIR)

clean:
	@printf "\033[1;31m[CLEAN] Deleting object files...\033[0m\n"
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LFT_DIR) clean
	@printf "\033[1;32m[OK] ✅ Cleaning completed.\033[0m\n"

fclean: clean
	@printf "\033[1;31m[CLEAN] Deleting executable...\033[0m\n"
	rm -f $(NAME) $(LFT_DIR)/libft.a
	@printf "\033[1;32m[OK] ✅ Deletion completed.\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libft
