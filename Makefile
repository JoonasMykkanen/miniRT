# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 11:21:33 by joonasmykka       #+#    #+#              #
#    Updated: 2023/08/21 13:34:46 by joonasmykka      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
LIBFT = src/libft/libft.a
LIBFT_DIR = src/libft/

SRCDIR = src
OBJDIR = obj

SRCS = $(SRCDIR)/main.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I ./inc

FLAGS = $(INCLUDES)

.PHONY: all
all: $(NAME) 

$(NAME): $(OBJS) $(LIBFT)
	@cc $(FLAGS) $(OBJS) -o $(NAME)

$(LIBFT):
	@echo "Creating dependency libft"
	@make -C ./src/libft

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@cc $(FLAGS) -c $< -o $@

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
