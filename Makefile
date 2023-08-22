# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:21:33 by joonasmykka       #+#    #+#              #
#    Updated: 2023/08/22 12:50:54 by joonasmykka      ###   ########.fr        #
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
	$(SRCDIR)/main.c \
	$(SRCDIR)/init.c \
	$(SRCDIR)/parse.c 

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I ./inc
LIBS = -L$(LIBFT_DIR) -lft $(LIBMLX_LIB) -I ./src/mlx42/include -ldl -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
# LIBS = -L$(LIBFT_DIR) -lft -L$(MLX42_DIR) -lmlx42 -I ./src/mlx42/include -ldl -lglfw -L"/Users/djames/.brew/Cellar/glfw/3.3.8/lib/"

CFLAGS = $(INCLUDES)
LDFLAGS = $(LIBS)

.PHONY: all
all: $(NAME) 

$(NAME): $(LIBMLX_LIB) $(LIBFT) $(OBJS)
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
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_DIR) 
	@rm -rf $(LIBMLX_DIR)/build
	@rm -f $(NAME)

.PHONY: re
re: fclean all
