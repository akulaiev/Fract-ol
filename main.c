/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 20:40:38 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/08 20:40:40 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	menu_content(t_data *win)
{
	mlx_string_put(win->mlx_p, win->mlx_nw, 155, 15, 0x1041a5, "Menu");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15, 35, 0x1041a5, "'esc' - quit");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	75, 0x1041a5, "'+'/mouse wheel - zoom in");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	95, 0x1041a5, "'-'/mouse wheel - zoom out");
	mlx_string_put(win->mlx_p, win->mlx_nw,
	15, 135, 0x1041a5, "arrows - move fract");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	155, 0x1041a5, "'c' - center and redraw fract");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	195, 0x1041a5, "'q' - enable changing Julia");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	215, 0x1041a5, "params with mouse");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	235, 0x1041a5, "'e' - disable changing Julia");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	255, 0x1041a5, "params with mouse");
	mlx_string_put(win->mlx_p, win->mlx_nw, 15,
	295, 0x1041a5, "'a' - change colours");
}

void	menu_frame(t_data *win)
{
	t_scale	menu;

	menu.x = -1;
	while (++menu.x < 350)
	{
		menu.y = -1;
		while (++menu.y < 950)
		{
			if (menu.x <= 10 || menu.y <= 10 || menu.x >= 340 || menu.y >= 940)
				menu.col = 0x001d59;
			else
				menu.col = 0x75a2ff;
			img_pixel_put(win, menu);
		}
	}
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	menu_content(win);
}

void	check_input(t_data *win, char *n, int i)
{
	if ((!ft_strcmp("Julia", n) || !ft_strcmp("1", n)) && (win->fn[i] = 1))
		win->f_name[i] = ft_strdup("Julia");
	if ((!ft_strcmp("Mandelbrot", n) || !ft_strcmp("2", n)) && (win->fn[i] = 2))
		win->f_name[i] = ft_strdup("Mandelbrot");
	if ((!ft_strcmp("Newton", n) || !ft_strcmp("3", n)) && (win->fn[i] = 3))
		win->f_name[i] = ft_strdup("Newton");
	if ((!ft_strcmp("Biomorph", n) || !ft_strcmp("4", n)) && (win->fn[i] = 4))
		win->f_name[i] = ft_strdup("Biomorph");
	if ((!ft_strcmp("Lambda", n) || !ft_strcmp("5", n)) && (win->fn[i] = 5))
		win->f_name[i] = ft_strdup("Lambda");
	if ((!ft_strcmp("Spider", n) || !ft_strcmp("6", n)) && (win->fn[i] = 6))
		win->f_name[i] = ft_strdup("Spider");
	if ((!ft_strcmp("Burning_ship", n) || !ft_strcmp("7", n))
	&& (win->fn[i] = 7))
		win->f_name[i] = ft_strdup("Burning_ship");
	if ((!ft_strcmp("Unknown", n) || !ft_strcmp("8", n)) && (win->fn[i] = 8))
		win->f_name[i] = ft_strdup("Unknown");
}

void	print_menu(t_data *win, char *inp1, char *inp2)
{
	if (inp1 && !inp2)
		check_input(win, inp1, 0);
	else if (inp1 && inp2)
	{
		check_input(win, inp1, 0);
		check_input(win, inp2, 1);
	}
	if (!inp1 || !win->f_name[0])
	{
		write(2, "usage: ./fractol [fract name]\navailable fractals:\n", 51);
		write(1, "-> 1. Julia\n", 12);
		write(1, "-> 2. Mandelbrot\n-> 3. Newton\n", 31);
		write(1, "-> 4. Biomorph\n-> 5. Lambda\n", 29);
		write(1, "-> 6. Spider\n-> 7. Burning_ship\n", 33);
		write(1, "-> 8. Unknown\n", 14);
		exit(0);
	}
	open_window(win);
}

int		main(int argc, char **argv)
{
	t_data	win;

	win.f_name[0] = NULL;
	win.f_name[1] = NULL;
	if (argc < 2 || argc > 3)
		print_menu(&win, NULL, NULL);
	else if (argc == 2)
		print_menu(&win, argv[1], NULL);
	else if (argc == 3)
		print_menu(&win, argv[1], argv[2]);
	return (0);
}
