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

int		key_react(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 8)
	{
		params_init(param);
		open_fract(param);
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
	if (keycode == 0)
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
		p->c_re = (float)x / p->ww;
		p->c_im = (float)y / p->wl;
		open_fract(p);
	}
	return (0);
}

float	interpolate(float start, float end, float ip)
{
	float res;

	res = start + ((end - start) * ip);
	return (res);
}

int		mouse_react(int button, int x, int y, void *param)
{
	t_data	*p;
	float	ip;
	float	mre;
	float	mim;

	p = (t_data*)param;
	if ((button == 4 || button == 5) && (x >= 350))
	{
		x -= 350;
		mre = (float)x / (p->ww / (p->max_re - p->min_re)) + p->min_re;
		mim = (float)y / (p->wl / (p->max_im - p->min_im)) + p->min_im;
		mlx_clear_window(p->mlx_p, p->mlx_nw);
		if (button == 4)
			ip = 1.03;
		if (button == 5)
			ip = 1 / 1.03;
		p->min_re = interpolate(mre, p->min_re, ip);
		p->min_im = interpolate(mim, p->min_im, ip);
		p->max_re = interpolate(mre, p->max_re, ip);
		p->max_im = interpolate(mim, p->max_im, ip);
		open_fract(p);
	}
	return (0);
}
