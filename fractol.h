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
# include "./libft/libft.h"
# include <string.h>
# include <pthread.h>

typedef struct	s_data
{
	void	*mlx_p;
	void	*mlx_nw;
	void	*mlx_img;
	int		win_width;
	int		win_length;
	char	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	int		col;
	double	move_right;
	double	move_down;
	double	enlarge;
	int		c_r;
	int		c_g;
	int		c_b;
	int		fract_num;
	double	max_re;
	double	max_im;
	double	min_re;
	double	min_im;
	double	c_re;
	double	c_im;
	int		mh;
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
	int		col;
}				t_scale;

typedef struct	s_mouse
{
	int		mid_x;
	int		mid_y;
	double	mid_re;
	double	mid_im;
	double	cf;
	double	re;
	double	im;
}				t_mouse; 

int		print_menu(t_data *win, char *input, int err);
void	set_julia(t_data *win);
void	params_init(t_data *win);
int		key_react(int keycode, void *param);
int		mouse_react(int button, int x, int y, void *param);
int		mouse_move(int x, int y, void *param);
void	pic_scale(int keycode, void *param);
void	pic_move(int keycode, void *param);
void	change_col_channels(int keycode, void *param);
int		colour_fract(double i, t_data *win);
void	open_fract(t_data *win);
void	open_window(t_data *win, char *fract_name);
void	img_pixel_put(t_data *win, t_scale scl);

#endif