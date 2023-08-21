# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:21:33 by joonasmykka       #+#    #+#              #
#    Updated: 2023/08/21 15:45:09 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

LIBFT = src/libft/libft.a
LIBFT_DIR = src/libft/

LIBMLX = src/mlx42/

SRCDIR = src
OBJDIR = obj

SRCS := \
	$(SRCDIR)/main.c \
	$(SRCDIR)/parse.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I ./inc
LIBS = -L$(LIBFT_DIR) -lft $(LIBMLX)build/libmlx42.a -I ./src/mlx42/include -ldl -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
# LIBS = -L$(LIBFT_DIR) -lft -L$(MLX42_DIR) -lmlx42 -I ./src/mlx42/include -ldl -lglfw -L"/Users/djames/.brew/Cellar/glfw/3.3.8/lib/"

CFLAGS = $(INCLUDES)
LDFLAGS = $(LIBS)

.PHONY: all
all: $(NAME) 

$(NAME): $(LIBFT) $(LIBMLX )$(OBJS)
	@cc $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	@echo "Creating dependency libft"
	@make -C $(LIBFT_DIR)

$(LIBMLX):
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@cc $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(LIBMLX)/build
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_DIR) 
	@rm -f $(NAME)

.PHONY: re
re: fclean all
