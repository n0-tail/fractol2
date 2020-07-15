/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:42:30 by anikkane          #+#    #+#             */
/*   Updated: 2020/07/15 14:29:43 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			end(char *reason)
{
	ft_putendl(reason);
	return (1);
}

t_color		get_color(int iteration, t_fractal *f_data)
{
	t_color		color;
	double		t;

	t = (double)iteration / f_data->max_iteration;
	color.channel[0] = 0;
	color.channel[1] = (int8_t)(10 * (1 - t) * (1 - t) * t * 170);
	color.channel[2] = (int8_t)(9 * (1 - t) * t * t * 150);
	color.channel[3] = (int8_t)(15 * (1 - t) * t * t * 110);
	return (color);
}

void		set_data(t_fractal *f_data)
{
	f_data->size_line = 1000;
	f_data->endian = 0;
	f_data->max_iteration = 50;
	f_data->min = init_complex(-2.0, -2.0);
	f_data->max = init_complex(2.0, 2.0);
	f_data->k = init_complex(-0.4, 0.6);
}

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}
