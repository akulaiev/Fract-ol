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

MLX = ./minilibx_macos/libmlx.a
MLX_PATH = ./minilibx_macos/

SOURCE = main.c event_handle.c julia.c manipulate_fracts.c event_helper.c \
mandelbrot.c newton.c biomorph.c lambda.c spider.c burning_ship.c two_wind.c
O_FILES = $(SOURCE:.c=.o)
# O_FILES = main.o event_handle.o julia.o manipulate_fracts.o event_helper.o \
# mandelbrot.o newton.o unknown.o

HEADER = -I ./fractol.h

all: LIBS $(NAME) 

$(NAME): $(O_FILES)
	$(CC) -lpthread $(MLX) -framework OpenGL -framework AppKit $(CFLAGS) -o $(NAME) $(O_FILES) $(LIBFT) # -lmlx

LIBS:
	make -C $(MLX_PATH)
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
