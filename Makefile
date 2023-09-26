# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:21:33 by joonasmykka       #+#    #+#              #
#    Updated: 2023/09/26 12:31:21 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

LIBFT_DIR = src/libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBMLX_DIR = src/mlx42
LIBMLX_LIB = $(LIBMLX_DIR)/build/libmlx42.a

SRCDIR = src
OBJDIR = obj

SRCS := \
	$(SRCDIR)/parser_cylinder.c \
	$(SRCDIR)/parser_helpers.c \
	$(SRCDIR)/parser_ambient.c \
	$(SRCDIR)/parser_camera.c \
	$(SRCDIR)/parser_sphere.c \
	$(SRCDIR)/parser_checks.c \
	$(SRCDIR)/parser_plane.c \
	$(SRCDIR)/parser_light.c \
	$(SRCDIR)/vec_helpers.c \
	$(SRCDIR)/vec_math.c \
	$(SRCDIR)/utility.c \
	$(SRCDIR)/ft_atof.c \
	$(SRCDIR)/parser.c \
	$(SRCDIR)/render.c \
	$(SRCDIR)/init.c \
	$(SRCDIR)/hook.c \
	$(SRCDIR)/ray.c \
	$(SRCDIR)/main.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I ./inc
LIBS = -L$(LIBFT_DIR) -lft $(LIBMLX_LIB) -I ./src/mlx42/include -ldl -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
# LIBS = -L$(LIBFT_DIR) -lft $(LIBMLX_LIB) -I ./src/mlx42/include -ldl -lglfw -L"/Users/$${USER}/.brew/Cellar/glfw/3.3.8/lib/"

CFLAGS = -g $(INCLUDES)
LDFLAGS = -g $(LIBS)

.PHONY: all
all: $(NAME) 

$(NAME): $(LIBMLX_LIB) $(LIBFT) $(OBJS)
	@echo "Compiling miniRT"
	@cc $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	@echo "Creating dependency libft"
	@make -C $(LIBFT_DIR)

$(LIBMLX_LIB):
	@cd src/mlx42 && cmake -B build && make -C build -j4
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@cc $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning"
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_DIR) 
	@rm -rf $(LIBMLX_DIR)/build
	@rm -f $(NAME)

.PHONY: re
re: fclean all

.PHONY: test
test: all
	./minirt test/test.rt