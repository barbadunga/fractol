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
	if (!(sub = (int*)malloc(sizeof(int) * 9)))
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

int		*filter(int *data)
{
	int	i;
	int	end;
	int	*sub;
	int	*new;

	i = WIDTH + 2;
	end = HEIGHT * (WIDTH - 2);
	if (!(new = (int*)malloc(sizeof(int) * HEIGHT * WIDTH)))
		return (NULL);
	while (i < end)
	{
		if (i % WIDTH == WIDTH - 1)
			i += 2;
		sub = sub_array(data, i, 3);
		sub = ft_insort(sub, 9);
		new[i] = sub[4];
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
		data = filter((int*)f->img->data);
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
