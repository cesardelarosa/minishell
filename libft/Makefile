NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_strarray_dup.c ft_strcmp.c ft_atof.c ft_handle_errors.c \
		ft_strcspn.c ft_ftoa.c ft_strjoin_free.c ft_iswhitespace.c \
		ft_realloc.c
BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
		ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstget.c
GNL_SRC = get_next_line.c
PRINTF_SRC = ft_printf.c ft_putargs.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
GNL_OBJ = $(GNL_SRC:.c=.o)
PRINTF_OBJ = $(PRINTF_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(BONUS_OBJ)
	touch .bonus
	ar rcs $(NAME) $(BONUS_OBJ)

gnl: $(GNL_OBJ)
	touch .gnl
	ar rcs $(NAME) $(GNL_OBJ)

printf: $(PRINTF_OBJ)
	touch .printf
	ar rcs $(NAME) $(PRINTF_OBJ)

complete: all bonus gnl printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f .gnl
	rm -f .bonus
	rm -f .printf
	rm -f $(OBJ) $(BONUS_OBJ) $(GNL_OBJ) $(PRINTF_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re gnl printf 
