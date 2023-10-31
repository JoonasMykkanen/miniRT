# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 15:36:10 by djames            #+#    #+#              #
#    Updated: 2023/10/31 15:13:32 by jmykkane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

NAME_BONUS = miniRT_bonus

LIBFT_DIR = src/libft
LIBFT = $(LIBFT_DIR)/libft.a

LIBMLX_DIR = src/mlx42
LIBMLX_LIB = $(LIBMLX_DIR)/build/libmlx42.a

SRCDIR = src
OBJDIR = obj
BONUS_SRCDIR = $(SRC)/bonus
BONUS_OBJDIR = obj/bonus

SRCS := \
	$(SRCDIR)/parser_cylinder.c \
	$(SRCDIR)/parser_helpers.c \
	$(SRCDIR)/parser_ambient.c \
	$(SRCDIR)/filename_check.c \
	$(SRCDIR)/light_helpers.c \
	$(SRCDIR)/parser_camera.c \
	$(SRCDIR)/parser_sphere.c \
	$(SRCDIR)/parser_checks.c \
	$(SRCDIR)/check_object.c \
	$(SRCDIR)/parser_plane.c \
	$(SRCDIR)/parser_light.c \
	$(SRCDIR)/vec_helpers.c \
	$(SRCDIR)/parser_line.c \
	$(SRCDIR)/hit_object.c \
	$(SRCDIR)/light_cyl.c \
	$(SRCDIR)/vec_math.c \
	$(SRCDIR)/utility.c \
	$(SRCDIR)/ft_atof.c \
	$(SRCDIR)/parser.c \
	$(SRCDIR)/render.c \
	$(SRCDIR)/shadow.c \
	$(SRCDIR)/light.c \
	$(SRCDIR)/init.c \
	$(SRCDIR)/hook.c \
	$(SRCDIR)/ray.c \
	$(SRCDIR)/cyl.c \
	$(SRCDIR)/main.c

SRCS_BONUS := \
	$(BONUSDIR)/parser_cylinder_bonus.c \
	$(BONUSDIR)/parser_helpers_bonus.c \
	$(BONUSDIR)/filename_check_bonus.c \
	$(BONUSDIR)/parser_ambient_bonus.c \
	$(BONUSDIR)/light_helpers_bonus.c \
	$(BONUSDIR)/parser_camera_bonus.c \
	$(BONUSDIR)/parser_sphere_bonus.c \
	$(BONUSDIR)/parser_checks_bonus.c \
	$(BONUSDIR)/check_object_bonus.c \
	$(BONUSDIR)/parser_plane_bonus.c \
	$(BONUSDIR)/parser_light_bonus.c \
	$(BONUSDIR)/vec_helpers_bonus.c \
	$(BONUSDIR)/parser_line_bonus.c \
	$(BONUSDIR)/hit_object_bonus.c \
	$(BONUSDIR)/clean_exit_bonus.c \
	$(BONUSDIR)/reflection_bonus.c \
	$(BONUSDIR)/light_cyl_bonus.c \
	$(BONUSDIR)/vec_math_bonus.c \
	$(BONUSDIR)/utility_bonus.c \
	$(BONUSDIR)/ft_atof_bonus.c \
	$(BONUSDIR)/routine_bonus.c \
	$(BONUSDIR)/parser_bonus.c \
	$(BONUSDIR)/render_bonus.c \
	$(BONUSDIR)/shadow_bonus.c \
	$(BONUSDIR)/worker_bonus.c \
	$(BONUSDIR)/light_bonus.c \
	$(BONUSDIR)/jobs_bonus.c \
	$(BONUSDIR)/list_bonus.c \
	$(BONUSDIR)/init_bonus.c \
	$(BONUSDIR)/hook_bonus.c \
	$(BONUSDIR)/ray_bonus.c \
	$(BONUSDIR)/cyl_bonus.c \
	$(BONUSDIR)/main_bonus.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

BONUS_OBJS = $(SRCS_BONUS:$(BONUSDIR)/%.c=$(BONUS_OBJDIR)/%.o)

HEADERS = ./inc/minirt.h ./inc/parser.h
BONUS_HEADERS = ./inc/bonus/minirt_bonus.h ./inc/bonus/parser_bonus.h

# LIBS = -L$(LIBFT_DIR) -lft $(LIBMLX_LIB) -I ./src/mlx42/include -ldl -lglfw -L"/Users/$${USER}/.brew/Cellar/glfw/3.3.8/lib/"
LIBS = -L$(LIBFT_DIR) -lft $(LIBMLX_LIB) -I ./src/mlx42/include -ldl -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"

CFLAGS = -Wall -Werror -Wextra -I./inc
LDFLAGS = $(LIBS)

.PHONY: all
all: $(NAME) 

.PHONY: bonus
bonus: $(NAME_BONUS)

$(NAME): $(LIBMLX_LIB) $(LIBFT) $(OBJS) $(HEADERS)
	@echo "Compiling miniRT"
	@cc $(LDFLAGS) $(OBJS) -o $(NAME)

$(NAME_BONUS): $(LIBMLX_LIB) $(LIBFT) $(BONUS_OBJS) $(BONUS_HEADERS)
	@echo "Compiling miniRT_BONUS"
	@cc $(LDFLAGS) $(BONUS_OBJS) -o $(NAME_BONUS)

$(LIBFT):
	@echo "Creating dependency libft"
	@make -C $(LIBFT_DIR)

$(LIBMLX_LIB):
	@cd src/mlx42 && cmake -B build && make -C build -j4
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(OBJDIR)
	@cc $(CFLAGS) -c $< -o $@

$(BONUS_OBJDIR)/%.o: $(BONUS_SRCDIR)/%.c $(BONUS_HEADERS)
	@mkdir -p $(BONUS_OBJDIR)
	@cc $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@echo "Cleaning"
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@rm -f $(BONUS_OBJS)

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_DIR) 
	@rm -rf $(LIBMLX_DIR)/build
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	

.PHONY: re
re: fclean all
