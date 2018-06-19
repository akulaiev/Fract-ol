#include "fractol.h"
#include <stdio.h>

void	check_point_ship(t_scale *s, t_data *w)
{
	float	tmp;

	while ((++s->iter < s->num_iter &&
	(s->new_re * s->new_re + s->new_im * s->new_im < 4)))
	{
		tmp = s->new_im;
		s->new_im = fabs(s->new_re * s->new_im + s->new_re * s->new_im) + w->c_im;
		s->new_re = fabs(s->new_re * s->new_re) - (tmp * tmp) + w->c_re;
	}
}

void	*set_burning_ship(void *win)
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
			w->c_re = 2 * (s.x - w->ww / 1.7) / (0.5 * w->enl * w->ww) + w->mr;
			w->c_im = 2 * (s.y - w->wl / 2) / (0.5 * w->enl * w->wl) + w->md;
			s.new_re = w->c_re;
			s.new_im = w->c_im;
			check_point_ship(&s, w);
			s.col = colour_fract(((double)s.iter / (double)s.num_iter), win);
			img_pixel_put(win, s);
		}
	}
	pthread_exit(NULL);
}