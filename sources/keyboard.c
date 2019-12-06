/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:38:52 by mshagga           #+#    #+#             */
/*   Updated: 2019/11/27 16:38:52 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

#define BYTE(val, n)	(val) >> (n * 8) & 0xFF

int		*sub_array(int *data, int index, int size)
{
	int			*sub;
	int			i;
	int			j;

	i = 0;
	j = -1;
	if (!(sub = (int*)malloc(sizeof(int) * size * size)))
		return (NULL);
	while (i < size)
	{
		sub[i] = data[index - WIDTH + j];
		sub[size + i] = data[index + j];
		sub[size * 2 + i] = data[index + WIDTH + j];
		i++;
		j++;
	}
	return (sub);
}

//int		blerp(int *arr, int size)
//{
//	int	res;
//	int	i;
//
//	i = 0;
//	while (i < size * size)
//	{
//
//	}
//	return (res);
//}

double	*create_kernel(size_t size)
{
	double	*kernel;
	int		i;
	int		x;
	int		y;

	if (!(kernel = (double*)malloc(sizeof(double) * size * size)))
		return (NULL);
	i = 0;
	while ((size_t)i < size * size)
	{
		x = i % size - size / 2;
		y = i / size - size / 2;
		x += x == 0 ? 1 : 0;
		y += y == 0 ? 1 : 0;
		printf("%d %d\n", x, y);
		kernel[i] = (sin(x) / x) * (sin(y) / y);
		i++;
	}
	i = 0;
	while ((size_t)i < size * size)
	{
		if (i % 5 == 0)
			printf("\n");
		printf("%f ", kernel[i]);
		i++;
	}
	return (kernel);
}

int		lanczos(int	*sub, size_t size)
{
	int				i;
	int				color[3];
//	static double	*kernel;
	const double	kernel[25] = {0.20670545, 0.3825737, 1., 0.3825737, 0.20670545,
	0.3825737, 0.70807342, 1., 0.70807342, 0.3825737,
	1., 1., 1., 1., 1., 0.3825737 , 0.70807342, 1., 0.70807342, 0.3825737 , 0.20670545, 0.3825737 , 1., 0.3825737 , 0.20670545};
	i = 0;
//	if (!kernel)
//		kernel = create_kernel(5);
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	while ((size_t)i < size * size)
	{
		color[0] += (int)((sub[i] >> 16 & 0xFF) * kernel[i]);
		color[1] += (int)((sub[i] >> 8 & 0xFF) * kernel[i]);
		color[2] += (int)((sub[i] & 0xFF) * kernel[i]);
		i++;
	}
	return ((color[0] / 9) << 16 | (color[1] / 9) << 8 | color[0]);
}

int		*filter(int *data, size_t size)
{
	int	i;
	int	end;
	int	*sub;
	int	*new;

	i = WIDTH + size / 2;
	end = HEIGHT * (WIDTH - size / 2);
	if (!(new = (int*)malloc(sizeof(int) * HEIGHT * WIDTH)))
		return (NULL);
	while (i < end)
	{
		if (i % WIDTH == WIDTH - size / 2 + 1)
			i += 2;
		sub = sub_array(data, i, size);
//		sub = ft_insort(sub, size * size);
		new[i] = lanczos(sub, size);
		new[i] = sub[(size * size) / 2];
		free(sub);
		i++;
	}
	return (new);
}

int		keyboard_event(int key, void *param)
{
	t_view	*v;
	t_fctl	*f;

	f = (t_fctl*)param;
	v = f->view;
	if (key == ESC)
		close_window((t_fctl *)param);
	if (key == LEFT || key == UP || key == DOWN || key == RIGHT)
		move(key, v);
	if (key == D_KEY)
		set_default_view(v, ((t_fctl *)param)->name);
	if (key == PLUS_KEY)
		v->max_iter++;
	if (key == MINUS_KEY)
		v->max_iter -= v->max_iter > 1 ? 1 : 0;
	if (key == CTRL_KEY)
		v->pressed = CTRL_KEY;
	if (key == H_KEY)
		v->help = v->help ? 0 : 1;
	render(param);
	if (key == S_KEY)
	{
		int *data;
		mlx_clear_window(f->mlx, f->win);
		data = filter((int*)f->img->data, 3);
		ft_memcpy(f->img->data, data, sizeof(int) * HEIGHT * WIDTH);
//		free(data);
//		for (int i = 0; i < WIDTH * HEIGHT; i++)
//			mlx_pixel_put(f->mlx, f->win, i % WIDTH, i / WIDTH, data[i]);
//			printf("%d\n", ((int*)f->img->data)[i] - data[i]);
		mlx_put_image_to_window(f->mlx, f->win, f->img->img_ptr, 0, 0);
		free(data);
	}
	return (1);
}

int		keyboard_release(int key, void *param)
{
	t_view	*v;

	v = ((t_fctl*)param)->view;
	v->pressed = -1;
	if (key == CTRL_KEY)
	{
		v->click[0] = -1;
		v->click[1] = -1;
	}
	render((t_fctl*)param);
	return (1);
}
