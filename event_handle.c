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
		exit(0);
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
	double	coeff_x;
	double	coeff_y;

	if (((t_data*)param)->mh == 1)
	{
		p = (t_data*)param;
		mlx_clear_window(p->mlx_p, p->mlx_nw);
		p = (t_data*)param;
		coeff_x = (p->max_re - p->min_re) / p->win_width;
		coeff_y = (p->max_im - p->min_im) / p->win_length;
		p->c_re = x * coeff_x;
		p->c_im = y * coeff_y;
		open_fract(p);
	}
	return (0);
}

int		mouse_react(int button, int x, int y, void *param)
{
	t_data	*p;
	int		mid_x;
	int		mid_y;
	double	mid_re;
	double	mid_im;
	double	coeff;
	double	re;
	double	im;

	p = (t_data*)param;
	mid_x = p->win_width / 4;
	mid_y = p->win_length / 4;
	coeff = ((p->max_re - p->min_re) / p->win_width) * ((p->max_im - p->min_im) / p->win_length);
	mid_re = mid_x * coeff;
	mid_im = mid_y * coeff;
	re = x / (p->win_width / (p->max_re - p->min_re)) + p->min_re;
	im = y / (p->win_length / (p->max_im - p->min_im)) + p->min_im;
	p->move_right = -(mid_re - re) * 0.6;
	p->move_down = -(mid_im - im) * 0.6;
	pic_scale(button, p);
	return (0);
}

void	pic_scale(int keycode, void *param)
{
	int	diff;

	diff = ((t_data*)param)->enlarge;
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 1)
		open_fract(((t_data*)param));
	if (keycode == 69 || keycode == 24 || keycode == 5)
		((t_data*)param)->enlarge += 0.1;
	if ((keycode == 78 || keycode == 27 || keycode == 4) && ((t_data*)param)->enlarge > 0.1)
		((t_data*)param)->enlarge -= 0.1;
	open_fract(((t_data*)param));
}

void	pic_move(int keycode, void *param)
{
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 126)
		((t_data*)param)->move_down += 0.1;
	if (keycode == 125)
		((t_data*)param)->move_down -= 0.1;
	if (keycode == 124)
		((t_data*)param)->move_right -= 0.1;
	if (keycode == 123)
		((t_data*)param)->move_right += 0.1;
	open_fract(((t_data*)param));
}

void	change_col_channels(int keycode, void *param)
{
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 15)
		((t_data*)param)->c_r += 1;
	if (keycode == 5)
		((t_data*)param)->c_g += 1;
	if (keycode == 11)
		((t_data*)param)->c_b += 1;
	if (keycode == 0)
	{
		((t_data*)param)->c_r += 5;
		((t_data*)param)->c_g += 5;
		((t_data*)param)->c_b += 5;
	}
	open_fract(((t_data*)param));
}