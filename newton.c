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

// z^3 - 1
// 	s->new_re = (s->old_re * s->old_re * s->old_re) - (3 * s->old_im * s->old_im * s->old_re) - 1;
// 	s->new_im = (3 * s->old_re * s->old_re * s->old_im) - (s->old_im * s->old_im * s->old_im);
// z^2 * 3
// 	s->new_re = 3 * (s->old_re * s->old_re - s->old_im * s->old_im);
// 	s->new_im = 6 * (s->old_re * s->old_im);

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

typedef struct	s_roots
{
	float	r_re;
	float	r_im;
}				t_roots;

void	check_point_new(t_scale *s)
{
	int		cols[3] = {0xff0000, 0x00ff00, 0x0000ff};
	t_roots	rs[3] = {{1, 0}, {-0.5, sqrt(3)/2}, {-0.5, -sqrt(3)/2}};
	float	tolerance = 0.000001;
	int		i;
	float	diff_re;
	float	diff_im;

	while (++s->iter < s->num_iter)
	{
		s->old_re = s->new_re;
		s->old_im = s->new_im;
		s->new_re -= funct_re(s) / depr_re(s);
		s->new_im -= funct_re(s) / depr_re(s);
		i = -1;
		while (++i < 3)
		{
			diff_re = s->new_re - rs[i].r_re;
			diff_im = s->new_im - rs[i].r_im;
			if (fabs(diff_re) < tolerance && fabs(diff_im) < tolerance)
				s->col = cols[i];
		}
		s->col = 0x0;
	}
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
			check_point_new(&s);
			img_pixel_put(win, s);
		}
	}
	pthread_exit(NULL);
}