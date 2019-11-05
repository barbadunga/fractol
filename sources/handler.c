/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:14:36 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/11/02 16:14:36 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		close_mlx(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(1);
}

int		keyboard_event(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (key == ESC)
		close_mlx(mlx);
	return (1);
}

void	event_handler(t_mlx *mlx)
{
	mlx_hook(mlx->win, RED_BUTTON, 1LU << (unsigned)17, close_mlx, mlx);
	mlx_hook(mlx->win, 2, 0, keyboard_event, mlx);
}