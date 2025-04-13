NAME          := minishell
BONUS_NAME    := minishell_bonus

SRC_DIR       := src
INC_DIR       := include
LFT_DIR       := libft
OBJ_DIR       := obj
OBJ_DIR_BONUS := obj_bonus

ALL_SRCS      := $(shell find $(SRC_DIR) -type f -name "*.c")
NORM_SRCS     := $(filter-out %_bonus.c, $(ALL_SRCS))

bonus_file = $(basename $1)_bonus.c

BONUS_NORM_SRCS := $(foreach s,$(NORM_SRCS),$(if $(wildcard $(call bonus_file,$(s))),,$(s)))
BONUS_FILES   := $(shell find $(SRC_DIR) -type f -name "*_bonus.c")
BONUS_SRCS    := $(BONUS_NORM_SRCS) $(BONUS_FILES)

OBJS          := $(NORM_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS    := $(BONUS_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR_BONUS)/%.o)

CC            := gcc
CFLAGS        := -Wall -Wextra -Werror -I$(INC_DIR) -I$(LFT_DIR)
LDLIBS        := -lreadline

all: $(NAME)

$(NAME): libft $(OBJS)
	@printf "\033[1;33m[BUILD] Linking $(NAME)...\033[0m\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT_DIR)/libft.a $(LDLIBS)
	@printf "\033[1;32m[OK] ✅ Compilation of $(NAME) completed.\033[0m\n"

bonus: $(BONUS_NAME)

$(BONUS_NAME): libft $(OBJS_BONUS)
	@printf "\033[1;33m[BUILD] Linking $(BONUS_NAME)...\033[0m\n"
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_BONUS) $(LFT_DIR)/libft.a $(LDLIBS)
	@printf "\033[1;32m[OK] ✅ Compilation of $(BONUS_NAME) completed.\033[0m\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[1;33m[BUILD] Compiling object: $<\033[0m\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[1;33m[BUILD] Compiling bonus object: $<\033[0m\n"
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	@printf "\033[1;33m[BUILD] Building libft...\033[0m\n"
	$(MAKE) complete -C $(LFT_DIR)

clean:
	@printf "\033[1;31m[CLEAN] Deleting object files...\033[0m\n"
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LFT_DIR) clean
	@printf "\033[1;32m[OK] ✅ Cleaning completed.\033[0m\n"

fclean: clean
	@printf "\033[1;31m[CLEAN] Deleting executables...\033[0m\n"
	rm -f $(NAME) $(BONUS_NAME) $(LFT_DIR)/libft.a
	@printf "\033[1;32m[OK] ✅ Deletion completed.\033[0m\n"

re: fclean all

.PHONY: all bonus libft clean fclean re
