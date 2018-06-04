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

void	deal_with_threads(t_data *win)
{
	int			num;
	int			i;
	pthread_t	th_id[NUM_TH];

	win->lines_per_th = win->win_length / NUM_TH;
	win->current_y = -1;
	i = 0;
	while (i < NUM_TH)
	{
		if (win->fract_num == 1)
			pthread_create(&th_id[i], NULL, set_julia, (void*)win);
		num = i + 1;
		while (num--)
			pthread_join(th_id[num], NULL);
		win->current_y += win->lines_per_th;
		i++;
	}
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	// mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 250, 0); for menu bar
}

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

void	img_pixel_put(t_data *win, t_scale scl)
{
	if (scl.x < win->win_width && scl.y < win->win_length && scl.x >= 0 && scl.y >= 0)
		*(int*)(win->img_ptr + (scl.x * win->bits_per_pixel / 8 + scl.y * win->size_line)) = scl.col;
}

void	open_window(t_data *win, char *fract_name)
{
	// int		all_win_w;
	// int		all_win_l;

	params_init(win);
	win->mlx_p = mlx_init();
	win->mlx_nw = mlx_new_window(win->mlx_p, win->win_width, win->win_length, fract_name);
	win->mlx_img = mlx_new_image(win->mlx_p, win->win_width, win->win_length);
	// all_win_w = win->win_width + 250;
	// all_win_l = win->win_length;
	// win->mlx_nw = mlx_new_window(win->mlx_p, all_win_w, all_win_l, fract_name);
	// win->mlx_img = mlx_new_image(win->mlx_p, all_win_w, all_win_l); menu
	win->img_ptr = mlx_get_data_addr(win->mlx_img, &win->bits_per_pixel, &win->size_line, &win->endian);
	open_fract(win);
}

void	open_fract(t_data *win)
{
	mlx_mouse_hook(win->mlx_nw, mouse_react, (void*)win);
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
	deal_with_threads(win);
	// mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 0, 0);
	mlx_loop(win->mlx_p);
}
