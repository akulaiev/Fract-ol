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
	win->min_re = -2.0;
	win->max_re = 1.0;
	win->min_im = -1.2;
	win->max_im = win->min_im + (win->max_re - win->min_re) *
	win->wl / win->ww;
	win->re_f = (win->max_re - win->min_re) / (win->ww - 1);
 	win->im_f = (win->max_im - win->min_im) / (win->wl - 1);
	if (win->fn == 8)
	{
		win->c_r = 15;
		win->c_g = 15;
		win->c_b = 15;
	}
	win->col = 0xf441f1;
}

void	*set_julia(void *win)
{
	t_scale			s;
	t_data			w;
	int				i;

	w = *((t_fract*)win)->window;
	s.y = ((t_fract*)win)->current_y;
	i = -1;
	while (++s.y < w.wl && ++i < w.lines_per_th)
	{
		s.x = -1;
		
		while (++s.x < w.ww)
		{
			s.iter = -1;
			s.num_iter = 150;
			s.new_re = (double)(s.x / (w.ww /
			(w.max_re - w.min_re)) + w.min_re) * w.enl + w.mr + 0.5;
			s.new_im = (double)(s.y / (w.wl /
			(w.max_im - w.min_im)) + w.min_im) * w.enl + w.md - 0.3;
			check_point(&s, &w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
