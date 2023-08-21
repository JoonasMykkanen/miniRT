# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:21:33 by joonasmykka       #+#    #+#              #
#    Updated: 2023/08/21 14:48:55 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

LIBFT = src/libft/libft.a
LIBFT_DIR = src/libft/

MLX42 = src/mlx42/build/libmlx42.a

SRCDIR = src
OBJDIR = obj

SRCS := \
	$(SRCDIR)/main.c
	$(SRCDIR)/parse.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I ./inc
LIBS = -L$(LIBFT_DIR) -lft $(MLX42) -I ./src/mlx42/include -ldl -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
# LIBS = -L$(LIBFT_DIR) -lft -L$(MLX42_DIR) -lmlx42 -I ./src/mlx42/include -ldl -lglfw -L"/Users/djames/.brew/Cellar/glfw/3.3.8/lib/"

CFLAGS = $(INCLUDES)
LDFLAGS = $(LIBS)

.PHONY: all
all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	@cc $(LDFLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	@echo "Creating dependency libft"
	@make -C $(LIBFT_DIR)

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
	@rm -f $(NAME)

.PHONY: re
re: fclean all
