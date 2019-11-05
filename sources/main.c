/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:25:18 by mshagga           #+#    #+#             */
/*   Updated: 2019/09/18 18:25:52 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

// If fail allocation free all memory
t_mlx	*init()
{
	t_mlx	*mlx;
	t_img	*img;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	if (!(mlx->mlx = mlx_init()))
		return (NULL);
	if (!(mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "fract'ol")))
		return (NULL);
	if (!(img->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT)))
		return (NULL);
	mlx->data = mlx_get_data_addr(img->img, &img->bpp, &img->size_line, &img->end);
	mlx->img = img;
	return (mlx);
}

typedef struct s_complex
{
	double	re;
	double	im;
}				t_complex;

t_complex init_complex(double r, double i)
{
	t_complex	c;

	c.re = r;
	c.im = i;
	return (c);
}

int		V(double n)
{
	int color;

	color = n * 0xFFFFFF / 50;
	return (color);
}

//void	draw(void *data)
//{
//	t_complex	min = {-2.0, -1.0},
//				max = {1.0, 1.0},
//				scale, c, z;
//	int			max_iter = 100;
//	double		r2;
//	int			color;
//
//	scale.re = (max.re - min.re) / (WIDTH - 1);
//	scale.im = (max.im - min.im) / (HEIGHT - 1);
//	for (int pixel = 0; pixel < HEIGHT * WIDTH; pixel++)
//	{
//		c.re = min.re + pixel % WIDTH * scale.re;
//		c.im = max.im - pixel / HEIGHT * scale.im;
//		z = init_complex(0, 0);
//		int i = -1;
//		color = 0;
//		while (++i < max_iter)
//		{
//			r2 = z.re * z.re + z.im * z.im;
//			if (r2 > 4)
//			{
////				color = V(log(r2));
//				color = V(i);
//				break;
//			}
//			z = init_complex(z.re * z.re - z.im * z.im + c.re, 2 * z.im * z.re + c.im);
//		}
//		((int*)data)[pixel] = color;
//	}
//}

int		main(void)
{
	t_mlx	*mlx;

	if (!(mlx = init()))
		exit(1);
	event_handler(mlx);
	draw(mlx->data);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img->img, 0, 0);
	mlx_loop(mlx->mlx);
	return (0);
}
