/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_wind.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akulaiev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:12:40 by akulaiev          #+#    #+#             */
/*   Updated: 2018/06/25 16:12:42 by akulaiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	two_wind(char *i1, char *i2, t_data *win)
{
	int id;
	int st;
	int	i;

	i = 0;
	if ((id = fork()) > 0)
	{
		i++;
		print_menu(win, i1);
		if (i == 2)
		{
			wait(&st);
			i--;
			if (i == 0)
				exit(0);
		}
	}
	else if (id == 0)
		print_menu(win, i2);
	else
	{
		write(2, "An error with fork occured\n", 27);
		exit(0);
	}
}

