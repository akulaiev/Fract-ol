/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_fracts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:22:02 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/15 15:22:04 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		colour_fract(double i, t_data *win)
{
	int		r;
	int		g;
	int		b;

	r = (int)(win->c_r * (1 - i) * i * i * i * 255);
	g = (int)(win->c_g * (1 - i) * (1 - i) * i * i * 255);
	b = (int)(win->c_b * (1 - i) * (1 - i) * (1 - i) * i * 255);
	return ((r << 16) + (g << 8) + b);
}

void	open_window(t_data *win, char *fract_name)
{
	// void	*mlx_mw;

	params_init(win);
	win->mlx_p = mlx_init();
	// mlx_mw = mlx_new_window(win->mlx_p, 350, 350, "Menu:");
	win->mlx_nw = mlx_new_window(win->mlx_p, win->win_width, win->win_length, fract_name);
	win->mlx_img = mlx_new_image(win->mlx_p, win->win_width, win->win_length);
	win->img_ptr = mlx_get_data_addr(win->mlx_img, &win->bits_per_pixel, &win->size_line, &win->endian);
	open_fract(win);
}

void	open_fract(t_data *win)
{
	mlx_mouse_hook(win->mlx_nw, mouse_react, (void*)win);
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
	mlx_hook(win->mlx_nw, 6, (1L << 13), &mouse_move, (void*)win);
	if (win->fract_num == 1)
		set_julia(win);
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	mlx_loop(win->mlx_p);
}
