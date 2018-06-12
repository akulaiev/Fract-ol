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

float	funct_re(t_scale *s)
{
	return ((s->old_re * s->old_re * s->old_re) - (3 * s->old_im * s->old_im * s->old_re) - 1);
}

float	funct_im(t_scale *s)
{
	return ((3 * s->old_re * s->old_re * s->old_im) - (s->old_im * s->old_im * s->old_im));
}

float	depr_re(t_scale *s)
{
	return (3 * (s->old_re * s->old_re - s->old_im * s->old_im));
}

float	depr_im(t_scale *s)
{
	return (6 * s->old_re * s->old_im);
}

void	*set_newton(void *win)
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
			float d_x = s.new_re;
			float d_y = s.new_im;
			while ((++s.iter < s.num_iter && (s.new_re * s.new_re + s.new_im * s.new_im < 4)
			&& (d_x * d_x + d_y * d_y > 0.000001)))
			{
				s.old_re = s.new_re;
				s.old_im = s.new_im;
				s.new_re = funct_re(&s) / depr_re(&s);;
				s.new_im = funct_im(&s) / depr_im(&s);;
				d_x = fabs(s.old_re - s.new_re);
				d_y = fabs(s.old_im - s.new_im);
			}
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), win);
			// s.col = colour_fract((16 - (s.iter % 16)), win);
			img_pixel_put(win, s);
		}
	}
	pthread_exit(NULL);
}
