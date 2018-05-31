/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 12:40:02 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/07 12:40:03 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int		key_react(int keycode, void *param)
{
	if (keycode == 53)
	{
		// system("leaks fractol");
		exit(0);
	}
	if (keycode == 12 && (((t_data*)param)->mh = 1))
		mlx_hook(((t_data*)param)->mlx_nw, 6, (1L << 13), &mouse_move, param);
	if (keycode == 14)
	{
		((t_data*)param)->mh = 0;
		mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
		((t_data*)param)->c_re = -0.7;
		((t_data*)param)->c_im = 0.27015;
		open_fract(((t_data*)param));
	}
	if (keycode == 69 || keycode == 24 || keycode == 78 || keycode == 27)
		pic_scale(keycode, param);
	if (keycode <= 126 && keycode >= 123)
		pic_move(keycode, param);
	if (keycode == 15 || keycode == 5 || keycode == 11 || keycode == 0)
		change_col_channels(keycode, param);
	return (0);
}

int		mouse_move(int x, int y, void *param)
{
	t_data	*p;

	if (((t_data*)param)->mh == 1)
	{
		p = (t_data*)param;
		mlx_clear_window(p->mlx_p, p->mlx_nw);
		p = (t_data*)param;
		p->c_re = (float)x / p->win_width;
		p->c_im = (float)y / p->win_length;
		open_fract(p);
	}
	return (0);
}

int		mouse_react(int button, int x, int y, void *param)
{
	t_data	*p;
	t_mouse	m;

	p = (t_data*)param;
	m.mid_x = p->win_width / 2;
	m.mid_y = p->win_length / 2;
	m.cf = ((p->max_re - p->min_re) / p->win_width) *
	((p->max_im - p->min_im) / p->win_length);
	m.mid_re = m.mid_x * m.cf;
	m.mid_im = m.mid_y * m.cf;
	m.re = x / (p->win_width / (p->max_re - p->min_re)) + p->min_re;
	m.im = y / (p->win_length / (p->max_im - p->min_im)) + p->min_im;
	p->move_right = -(m.mid_re - m.re);
	p->move_down = -(m.mid_im - m.im);
	pic_scale(button, p);
	return (0);
}
