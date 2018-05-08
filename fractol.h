/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 11:33:33 by akulaiev          #+#    #+#             */
/*   Updated: 2018/05/07 11:33:35 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "./minilibx_macos/mlx.h"
// # include <mlx.h>
# include "./libft/libft.h"
# include <string.h>

typedef struct	s_data
{
	void	*mlx_p;
	void	*mlx_nw;
	int		win_width;
	int		win_length;
	int		x;
	int		y;
	int		col;
}				t_data;

typedef struct	s_scale
{
	int		x;
	int		y;
	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;
	int		iter;
	int		num_iter;
	double	c_re;
	double	c_im;
	double	min_scale_width;
	double	max_scale_width;
	double	min_scale_len;
	double	max_scale_len;
	double	x_scale;
	double	y_scale;
	int		max_col;
}				t_scale;

int		my_err(int errn);
void	open_window(t_data *win, char *fract_name);
int		key_react(int keycode, void *param);

#endif