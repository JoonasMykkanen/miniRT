NAME = libft.a

SRC_DIR = src/
OBJ_DIR = obj/

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memcpy.c ft_memmove.c ft_memset.c\
ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strncmp.c\
ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c\
ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_memchr.c ft_memcmp.c\
ft_strtrim.c ft_strnstr.c ft_calloc.c ft_strmapi.c ft_striteri.c ft_split.c\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstadd_back.c ft_lstlast.c\
ft_puthex_lower_fd.c ft_puthex_upper_fd.c ft_memrcpy.c ft_hexlen.c\
get_next_line.c get_next_line_utils.c ft_printf.c convert_c.c\
convert_d_i.c convert_p.c convert_s.c convert_u.c convert_x.c\
convert_precentage.c dir_check.c ft_strcmp.c ft_isnum.c ft_free.c\
vec_append.c vec_copy.c vec_filter.c vec_free.c vec_from.c vec_get.c\
vec_insert.c vec_iter.c vec_map.c vec_new.c vec_pop.c vec_prepend.c\
vec_push.c vec_remove.c vec_resize.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

INCLUDES = -I./inc
FLAGS = -Wall -Werror -Wextra $(INCLUDES)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Creating archive $(NAME)..."
	ar rc $(NAME) $(OBJS)
	@echo "Archive $(NAME) created."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS)
	@mkdir -p $(OBJ_DIR)
	cc -c $(FLAGS) $< -o $@

clean:
	@echo "Cleaning object files..."
	rm -f $(OBJS)
	@echo "Object files cleaned."

fclean: clean
	@echo "Cleaning library..."
	rm -f $(NAME)
	@echo "Library cleaned."

re: fclean all
