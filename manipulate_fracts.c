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

static void	deal_with_threads_h(t_fract *w, int i, pthread_t *th_id, int fn)
{
	if (fn == 2)
		pthread_create(&th_id[i], NULL, set_mandelbrot, w + i);
	else if (fn == 3)
		pthread_create(&th_id[i], NULL, set_newton, w + i);
	else if (fn == 4)
		pthread_create(&th_id[i], NULL, set_biomorph, w + i);
	else if (fn == 5)
		pthread_create(&th_id[i], NULL, set_lambda, w + i);
	else if (fn == 6)
		pthread_create(&th_id[i], NULL, set_spider, w + i);
	else if (fn == 7)
		pthread_create(&th_id[i], NULL, set_burning_ship, w + i);
	else if (fn == 8)
		pthread_create(&th_id[i], NULL, set_unknown, w + i);
}

void		deal_with_threads(t_data *win)
{
	int			j;
	int			iter;
	t_fract		w[NUM_TH];
	pthread_t	th_id[NUM_TH];

	win->lines_per_th = win->wl / NUM_TH;
	iter = -1;
	j = -1;
	while (++iter < NUM_TH)
	{
		w[iter].current_y = j;
		w[iter].window = win;
		j += win->lines_per_th;
	}
	iter = -1;
	while (++iter < NUM_TH)
	{
		if (win->f_n == 1)
			pthread_create(&th_id[iter], NULL, set_julia, w + iter);
		else
			deal_with_threads_h(w, iter, th_id, win->f_n);
	}
	iter = -1;
	while (++iter < NUM_TH)
		pthread_join(th_id[iter], NULL);
}

void		img_pixel_put(t_data *win, t_scale scl)
{
	if (scl.x < win->ww && scl.y < win->wl &&
	scl.x >= 0 && scl.y >= 0)
		*(int*)(win->img_ptr + (scl.x * win->bits_per_pixel / 8 +
		scl.y * win->size_line)) = scl.col;
}

void		open_window(t_data *win)
{
	int		w;
	t_data	win2;

	win->f_n = win->fn[0];
	params_init(win);
	win->mlx_p = mlx_init();
	w = win->ww + 350;
	win->mlx_nw = mlx_new_window(win->mlx_p, w, win->wl, win->f_name[0]);
	win->mlx_img = mlx_new_image(win->mlx_p, win->ww, win->wl);
	win->img_ptr = mlx_get_data_addr(win->mlx_img,
	&win->bits_per_pixel, &win->size_line, &win->endian);
	open_fract(win);
	if (win->f_name[1])
	{
		params_init(&win2);
		win2.mlx_p = mlx_init();
		win2.f_n = win->fn[1];
		win2.mlx_nw = mlx_new_window(win->mlx_p, w, win->wl, win->f_name[1]);
		win2.mlx_img = mlx_new_image(win->mlx_p, win2.ww, win2.wl);
		win2.img_ptr = mlx_get_data_addr(win2.mlx_img,
		&win2.bits_per_pixel, &win2.size_line, &win2.endian);
		open_fract(&win2);
	}
	mlx_loop(win->mlx_p);
}

void		open_fract(t_data *win)
{
	menu_frame(win);
	mlx_mouse_hook(win->mlx_nw, mouse_react, (void*)win);
	mlx_hook(win->mlx_nw, 2, 5, key_react, (void*)win);
	deal_with_threads(win);
	mlx_put_image_to_window(win->mlx_p, win->mlx_nw, win->mlx_img, 350, 0);
}
