# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:21:33 by joonasmykka       #+#    #+#              #
#    Updated: 2023/08/21 13:59:09 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

LIBFT = src/libft/libft.a
LIBFT_DIR = src/libft/

MLX42 = src/MLX42/build/libmlx42.a
MLX42_DIR = src/MLX42/build/

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/main.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I ./inc
LIBS = -L$(LIBFT_DIR) -lft -L$(MLX42_DIR) -lmlx42 -I ./src/mlx42/include -ldl -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
# LIBS = -L$(LIBFT_DIR) -lft -L$(MLX42_DIR) -lmlx42 -I ./src/mlx42/include -ldl -lglfw -L"/Users/djames/.brew/Cellar/glfw/3.3.8/lib/"

CFLAGS = $(INCLUDES)
LDFLAGS = $(LIBS)

.PHONY: all
all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT) $(MLX42)
	@cc $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	@echo "Creating dependency libft"
	@make -C $(LIBFT_DIR)

$(MLX42):
	@echo "Creating dependency libmlx42"
	@make -C $(MLX42_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@cc $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@make clean -C $(LIBFT_DIR) 
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_DIR) 
	@make clean -C $(MLX42_DIR)
	@rm -f $(NAME)

.PHONY: re
re: fclean all
