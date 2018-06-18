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

void	deal_with_threads_h(t_data *win, int i, pthread_t *th_id)
{
	if (win->fn == 5)
		pthread_create(&th_id[i], NULL, set_lambda, (void*)win);
	if (win->fn == 6)
		pthread_create(&th_id[i], NULL, set_spider, (void*)win);
}

void	deal_with_threads(t_data *win)
{
	int			num;
	int			i;
	pthread_t	th_id[NUM_TH];

	win->lines_per_th = win->wl / NUM_TH;
	win->current_y = -1;
	i = 0;
	while (i < NUM_TH)
	{
		if (win->fn == 1)
			pthread_create(&th_id[i], NULL, set_julia, (void*)win);
		if (win->fn == 2)
			pthread_create(&th_id[i], NULL, set_mandelbrot, (void*)win);
		if (win->fn == 3)
			pthread_create(&th_id[i], NULL, set_newton, (void*)win);
		if (win->fn == 4)
			pthread_create(&th_id[i], NULL, set_biomorph, (void*)win);
		else
			deal_with_threads_h(win, i, th_id);
		num = i + 1;
		while (num--)
			pthread_join(th_id[num], NULL);
		win->current_y += win->lines_per_th;
		i++;
	}
}

void	img_pixel_put(t_data *win, t_scale scl)
{
	if (scl.x < win->ww && scl.y < win->wl &&
	scl.x >= 0 && scl.y >= 0)
		*(int*)(win->img_ptr + (scl.x * win->bits_per_pixel / 8 +
		scl.y * win->size_line)) = scl.col;
}

void	open_window(t_data *win, char *fract_name)
{
	int		w;
	int		l;

	params_init(win);
	win->mlx_p = mlx_init();
	w = win->ww + 350;
	l = win->wl;
	win->mlx_nw = mlx_new_window(win->mlx_p, w, l, fract_name);
	win->mlx_img = mlx_new_image(win->mlx_p, win->ww, win->wl);
	win->img_ptr = mlx_get_data_addr(win->mlx_img,
	&win->bits_per_pixel, &win->size_line, &win->endian);
	open_fract(win);
}

void	open_fract(t_data *win)
{
	menu_frame(win);
	mlx_mouse_hook(win->mlx_nw, mouse_react, (void*)win);
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
	deal_with_threads(win);
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 350, 0);
	mlx_loop(win->mlx_p);
}
