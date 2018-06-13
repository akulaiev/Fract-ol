/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:49:52 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/11 14:49:54 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	check_new(t_scale *s, float tmp)
{
	while (tmp > 0.000001 && ++s->iter < s->num_iter)
	{
		s->old_re = s->new_re;
		s->old_im = s->new_im;
		tmp = (s->new_re * s->new_re + s->new_im * s->new_im) * (s->new_re * s->new_re + s->new_im * s->new_im);
		s->new_re = (2 * s->new_re * tmp + s->new_re * s->new_re - s->new_im * s->new_im) / (3 * tmp);
		s->new_im = (2 * s->new_im * (tmp - s->old_re)) / (3 * tmp);
		tmp = (s->new_re - s->old_re) * (s->new_re - s->old_re) + (s->new_im - s->old_im) * (s->new_im - s->old_im);
	}
}

void	*set_newton(void *win)
{
	t_scale			s;
	t_data			*w;
	int				i;
	float			tmp;

	w = (t_data*)win;
	s.y = w->current_y;
	i = -1;
	while (++s.y < w->wl && ++i < w->lines_per_th)
	{
		s.x = -1;
		while (++s.x < w->ww)
		{
			tmp = 1;
			s.iter = -1;
			s.num_iter = 150;
			s.new_re = 1.5 * (s.x - w->ww / 2) / (0.5 * w->enl * w->ww) + w->mr;
			s.new_im = (s.y - w->wl / 2) / (0.5 * w->enl * w->wl) + w->md;
			check_new(&s, tmp);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), win);
			img_pixel_put(win, s);
		}
	}
	pthread_exit(NULL);
}
