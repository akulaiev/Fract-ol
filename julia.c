/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:53:01 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/31 12:53:06 by akulaiev         ###   ########.fr       */
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

void	check_point(t_scale *s, t_data *w)
{
	while ((++s->iter < s->num_iter &&
	(s->new_re * s->new_re + s->new_im * s->new_im < 4)))
	{
		s->old_re = s->new_re;
		s->old_im = s->new_im;
		s->new_re = (s->old_re * s->old_re) - (s->old_im * s->old_im) + w->c_re;
		s->new_im = (2 * s->old_re * s->old_im) + w->c_im;
	}
}

void	params_init(t_data *win)
{
	win->ww = 950;
	win->wl = 950;
	win->enl = 1;
	win->md = 0;
	win->mr = 0;
	win->c_r = 9;
	win->c_g = 9;
	win->c_b = 9;
	win->c_re = -0.7;
	win->c_im = 0.27015;
	win->col = 0xf441f1;
}

void	*set_julia(void *win)
{
	t_scale			s;
	t_data			*w;
	int				i;

	w = (t_data*)win;
	s.y = w->current_y;
	i = -1;
	while (++s.y < w->wl && ++i < w->lines_per_th)
	{
		s.x = -1;
		while (++s.x < w->ww)
		{
			s.iter = -1;
			s.num_iter = 150;
			s.new_re = 1.5 * (s.x - w->ww / 2) / (0.5 * w->enl * w->ww) + w->mr;
			s.new_im = (s.y - w->wl / 2) / (0.5 * w->enl * w->wl) + w->md;
			check_point(&s, w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), win);
			img_pixel_put(win, s);
		}
	}
	pthread_exit(NULL);
}
