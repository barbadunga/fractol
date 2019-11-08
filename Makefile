# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mshagga <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/25 16:54:34 by mshagga           #+#    #+#              #
#    Updated: 2019/11/03 16:41:04 by mshagga          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = ./minilibx_macos/
LIBFT_DIR = ./Libft/
OBJ_DIR = ./objects/
SRC_DIR = ./sources/
INC_DIR = ./includes/
INC_LST = fractol.h \

LIBFT = $(LIBFT_DIR)libft.a
INC = $(addprefix $(INC_DIR), $(INC_LST))
MLX = $(MLX_DIR)libmlx.a

SRC_LST =	main.c \
		    handler.c \
		    tools.c \
		    draw.c \
		    # debug.c \
            # set_kernel.c
OBJ_LST = $(patsubst %.c, %.o, $(SRC_LST))

IFLAGS = -I $(INC_DIR) -I $(MLX_DIR) -I $(LIBFT_DIR)
LFLAGS = -L $(MLX_DIR) -lmlx -L $(LIBFT_DIR) -lft -framework OpenGL -framework Appkit -framework OpenCL

SRC = $(addprefix $(SRC_DIR), $(SRC_LST))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LST))

all: $(BIN)

$(BIN): $(LIBFT) $(INC) $(MLX) $(OBJ_DIR) $(OBJ)
	@$(CC) $(SOURCES) $(CFLAGS) $(LFLAGS) $(IFLAGS) -o $(BIN) $(OBJ)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@$(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MLX):
	@make -sC $(MLX_DIR)

clean:
	@make clean -sC $(LIBFT_DIR)
	@make clean -sC $(MLX_DIR)
	@rm -rf $(OBJ_DIR)

fclean:
	@make fclean -sC $(LIBFT_DIR)
	@rm -f $(MLX)
	@rm -f $(BIN)

re: fclean all

