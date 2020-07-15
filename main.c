/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:39:28 by anikkane          #+#    #+#             */
/*   Updated: 2020/07/15 14:20:14 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	void		*mlx_ptr;
	t_fractal	*f_data;

	if (argc != 2)
	{
		end("too few arguments, usage: ./fractol fractalname");
		end("possible names: mandelbrot, mandelbar, julia");
		exit(0);
	}
	f_data = NULL;
	mlx_ptr = mlx_init();
	f_data = init(mlx_ptr, argv[1]);
	pthread(f_data);
	mlx_loop(mlx_ptr);
	return (0);
}

void	draw_fractal_part(t_fractal *f_data)
{
	int			y;
	int			x;
	t_color		color;

	y = f_data->start_line;
	while (y < f_data->finish_line)
	{
		f_data->c.im = f_data->max.im - y * f_data->factor.im;
		x = 0;
		while (x < WIDTH)
		{
			f_data->c.re = f_data->min.re + x * f_data->factor.re;
			if (ft_strcmp(f_data->name, "mandelbrot") == 0)
				color = get_color(iterate_mandelbrot(f_data), f_data);
			if (ft_strcmp(f_data->name, "julia") == 0)
				color = get_color(iterate_julia(f_data), f_data);
			if (ft_strcmp(f_data->name, "mandelbar") == 0)
				color = get_color(iterate_mandelbar(f_data), f_data);
			put_pixel(f_data, x, y, color);
			x++;
		}
		y++;
	}
}

void	pthread(t_fractal *f_data)
{
	t_fractal	tab[THREAD_NUMBER];
	pthread_t	t[THREAD_NUMBER];
	int			i;

	i = 0;
	f_data->factor = init_complex(
			(f_data->max.re - f_data->min.re) / (WIDTH - 1),
			(f_data->max.im - f_data->min.im) / (HEIGHT - 1));
	while (i < THREAD_NUMBER)
	{
		ft_memcpy((void*)&tab[i], (void*)f_data, sizeof(t_fractal));
		tab[i].start_line = THREAD_WIDTH * i;
		tab[i].finish_line = THREAD_WIDTH * (i + 1);
		if (pthread_create(&t[i], NULL,
					(void *(*)(void *))draw_fractal_part, (void *)&tab[i]))
			exit(1);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(f_data->mlx, f_data->win, f_data->image, 0, 0);
}

void	put_pixel(t_fractal *f_data, int x, int y, t_color color)
{
	int i;

	i = (x * f_data->bits_per_pixel / 8) + (y * f_data->size_line);
	f_data->data_addr[i] = color.channel[3];
	f_data->data_addr[++i] = color.channel[2];
	f_data->data_addr[++i] = color.channel[1];
	f_data->data_addr[++i] = color.channel[0];
}
