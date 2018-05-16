/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   c_reated: 2018/05/07 11:46:53 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/07 11:46:55 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	params_init(t_data *win)
{
	win->win_width = 950;
	win->win_length = 950;
	win->enlarge = 1;
	win->move_down = 0;
	win->move_right = 0;
	win->c_r = 9;
	win->c_g = 9;
	win->c_b = 9;
}

int		check_input(t_data *win, char *input)
{
	if (!ft_strcmp("Julia", input) || !ft_strcmp("1", input))
	{
		win->fract_num = 1;
		open_window(win, "Julia");
	}
	if (!ft_strcmp("exit", input))
		exit(0);
	else
		return (1);
	return (0);
}

int		print_menu(t_data *win, char *input, int err)
{
	char	*name;

	name = NULL;
	if (input)
		err = check_input(win, input);
	if (err == 1)
		write(2, "usage: ./fractol [fract name]\n", 30);
	write(1, "available fractals:\n", 20);
	write(1, "-> 1. Julia\n", 12);
	write(1, "-> 2. Mandelbrot\n", 17);
	write(1, "type 'exit' to 'exit properly'\n", 31);
	while (get_next_line(0, &name))
	{
		if (!(check_input(win, name)))
			return (0);
		else
			print_menu(win, name, 1);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_data	win;

	if (argc != 2)
		print_menu(&win, NULL, 1);
	else
		print_menu(&win, argv[1], 0);
	return (0);
}
