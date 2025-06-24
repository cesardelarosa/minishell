NAME			:= minishell
BONUS_NAME		:= minishell_bonus

SRC_DIR			:= src
INC_DIR			:= include
LFT_DIR			:= libft
OBJ_DIR			:= obj
OBJ_DIR_BONUS	:= obj_bonus

LFT_NAME		:= $(LFT_DIR)/libft.a

COMMON_SRCS := \
	main.c \
	exec/exec.c \
	exec/exec_utils/exec_builtin_in_parent.c \
	exec/exec_utils/exec_command.c \
	exec/exec_utils/exec_error.c \
	exec/exec_utils/exec_pipeline.c \
	exec/ft_builtins/ft_cd.c \
	exec/ft_builtins/ft_echo.c \
	exec/ft_builtins/ft_env.c \
	exec/ft_builtins/ft_exit.c \
	exec/ft_builtins/ft_export.c \
	exec/ft_builtins/ft_pwd.c \
	exec/ft_builtins/ft_unset.c \
	exec/ft_builtins/get_builtin_ft.c \
	exec/handle_redirs/handle_heredoc.c \
	exec/handle_redirs/handle_redir_append.c \
	exec/handle_redirs/handle_redir_in.c \
	exec/handle_redirs/handle_redir_out.c \
	exec/handle_redirs/handle_redirs.c \
	expander/expand_variable/expand_value.c \
	lexer/lexer.c \
	lexer/process_token/process_double_quote.c \
	lexer/process_token/process_pipe.c \
	lexer/process_token/process_redirect_in.c \
	lexer/process_token/process_redirect_out.c \
	lexer/process_token/process_single_quote.c \
	lexer/process_token/process_token.c \
	lexer/process_token/process_word.c \
	parser/parser.c \
	parser/parse_token/parse_command.c \
	parser/parse_token/parse_error.c \
	parser/parse_token/parse_redirection.c \
	parser/parse_token/parse_word.c \
	parser/parse_token/parse_heredoc.c \
	read_prompt/read_prompt.c \
	signals/signals.c \
	structs_utils/command_utils.c \
	structs_utils/ctx_utils.c \
	structs_utils/env_utils/env_destroy.c \
	structs_utils/env_utils/env_expand.c \
	structs_utils/env_utils/env_get.c \
	structs_utils/env_utils/env_init.c \
	structs_utils/env_utils/env_is_valid_key.c \
	structs_utils/env_utils/env_print.c \
	structs_utils/env_utils/env_set.c \
	structs_utils/env_utils/env_setup.c \
	structs_utils/env_utils/env_to_array.c \
	structs_utils/env_utils/env_unset.c \
	structs_utils/env_utils/env_update_envp.c \
	structs_utils/pipeline_utils.c \
	structs_utils/redir_utils.c \
	structs_utils/token_utils.c

MANDATORY_ONLY_SRCS := \
	shell_loop.c \
	parser/parse_token/parse_token.c

BONUS_ONLY_SRCS := \
	shell_loop_bonus.c \
	exec/exec_ast_bonus.c \
	expander/globbing_bonus/globbing_bonus.c \
	expander/globbing_bonus/globbing_engine_bonus.c \
	expander/globbing_bonus/globbing_utils_bonus.c \
	expander/globbing_bonus/handle_pattern/handle_path_pattern_bonus.c \
	expander/globbing_bonus/handle_pattern/handle_simple_pattern_bonus.c \
	parser/ast_parser_bonus/ast_parser_bonus.c \
	parser/ast_parser_bonus/ast_parser_utils_bonus.c \
	parser/parse_token/parse_token_bonus.c \
	structs_utils/ast_utils_bonus.c

NORM_SRCS		:= $(addprefix $(SRC_DIR)/, $(COMMON_SRCS) $(MANDATORY_ONLY_SRCS))

COMMON_BONUS_SRCS := $(addprefix $(SRC_DIR)/, $(COMMON_SRCS))
BONUS_ONLY_SRCS_FULL_PATH := $(addprefix $(SRC_DIR)/, $(BONUS_ONLY_SRCS))

OBJS			:= $(NORM_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
COMMON_OBJS		:= $(COMMON_BONUS_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_ONLY_OBJS	:= $(BONUS_ONLY_SRCS_FULL_PATH:$(SRC_DIR)/%.c=$(OBJ_DIR_BONUS)/%.o)

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -I$(INC_DIR) -I$(LFT_DIR)
LDLIBS			:= -lreadline

all: $(NAME)

$(NAME): $(LFT_NAME) $(OBJS)
	@printf "\033[1;33m[BUILD] Linking $(NAME)...\033[0m\n"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFT_DIR)/libft.a $(LDLIBS)
	@printf "\033[1;32m[OK] ✅ Compilation of $(NAME) completed.\033[0m\n"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LFT_NAME) $(COMMON_OBJS) $(BONUS_ONLY_OBJS)
	@printf "\033[1;33m[BUILD] Linking $(BONUS_NAME)...\033[0m\n"
	$(CC) $(CFLAGS) -o $(BONUS_NAME) $(COMMON_OBJS) $(BONUS_ONLY_OBJS) $(LFT_DIR)/libft.a $(LDLIBS)
	@printf "\033[1;32m[OK] ✅ Compilation of $(BONUS_NAME) completed.\033[0m\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[1;33m[BUILD] Compiling object: $<\033[0m\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@printf "\033[1;33m[BUILD] Compiling bonus object: $<\033[0m\n"
	$(CC) $(CFLAGS) -c $< -o $@


$(LFT_NAME):
	@printf "\033[1;33m[BUILD] Building libft...\033[0m\n"
	$(MAKE) complete -C $(LFT_DIR)

clean:
	@printf "\033[1;31m[CLEAN] Deleting object files...\033[0m\n"
	rm -rf $(OBJ_DIR) $(OBJ_DIR_BONUS)
	$(MAKE) -sC $(LFT_DIR) clean
	@printf "\033[1;32m[OK] ✅ Cleaning completed.\033[0m\n"

fclean: clean
	@printf "\033[1;31m[CLEAN] Deleting executables...\033[0m\n"
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -sC $(LFT_DIR) fclean
	@printf "\033[1;32m[OK] ✅ Deletion completed.\033[0m\n"

re: fclean all

.PHONY: all bonus clean fclean re
