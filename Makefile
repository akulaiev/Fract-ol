# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/07 11:21:04 by akulaiev          #+#    #+#              #
#    Updated: 2018/05/07 11:21:06 by akulaiev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/libft.a
LIBFT_PATH = ./libft/

# MLX = ./minilibx_macos/libmlx.a
# MLX_PATH = ./minilibx_macos/

SOURCE = main.c event_handle.c
O_FILES = main.o event_handle.o

HEADER = -I ./fractol.h

all: LIBS $(NAME) 

$(NAME): $(O_FILES)
	$(CC) -lmlx -framework OpenGL -framework AppKit $(CFLAGS) -o $(NAME) $(O_FILES) $(LIBFT) # $(MLX)

LIBS:
	# make -C $(MLX_PATH)
	make -C $(LIBFT_PATH)

%.o: %.c
	$(CC) $(HEADER) $(CFLAGS) $(SOURCE) -c $<

exe:
	./$(NAME)

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(O_FILES)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	clear

norm:
	norminette $(SOURCE)

re: fclean all
