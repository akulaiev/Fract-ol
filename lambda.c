/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambda.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:34:36 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/26 16:34:37 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	check_point_la(t_scale *s, t_data *w)
{
	while ((++s->iter < s->num_iter &&
	(s->new_re * s->new_re + s->new_im * s->new_im < 4)))
	{
		s->old_re = s->new_re - (s->new_re * s->new_re) +
		(s->new_im * s->new_im);
		s->old_im = s->new_im - (2 * s->new_re * s->new_im);
		s->new_re = w->c_re * s->old_re - w->c_im * s->old_im;
		s->new_im = w->c_re * s->old_im + w->c_im * s->old_re;
	}
}

void	*set_lambda(void *win)
{
	t_scale			s;
	t_data			w;

	w = *((t_fract*)win)->window;
	s.y = ((t_fract*)win)->current_y;
	s.i = -1;
	while (++s.y < w.wl && ++s.i < w.lines_per_th)
	{
		s.x = -1;
		while (++s.x < w.ww)
		{
			s.iter = -1;
			s.num_iter = 150;
			w.c_re = (double)(s.x / (w.ww /
			(w.max_re - w.min_re)) + w.min_re) * (w.enl / 0.5) + w.mr + 1.99;
			w.c_im = (double)(s.y / (w.wl /
			(w.max_im - w.min_im)) + w.min_im) * (w.enl / 0.5) + w.md - 0.3;
			s.new_re = 0.5;
			s.new_im = 0;
			check_point_la(&s, &w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), &w);
			img_pixel_put(&w, s);
		}
	}
	pthread_exit(NULL);
}
