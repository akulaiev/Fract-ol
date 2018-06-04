/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:47:12 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/30 13:47:13 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	pic_scale(int keycode, void *param)
{
	mlx_clear_window(((t_data*)param)->mlx_p, ((t_data*)param)->mlx_nw);
	if (keycode == 69 || keycode == 24 || keycode == 5)
		((t_data*)param)->enlarge += 0.1;
	if ((keycode == 78 || keycode == 27 || keycode == 4) && ((t_data*)param)->enlarge >= 0.2)
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
