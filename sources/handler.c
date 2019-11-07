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

void    move(int key, t_param *p)
{
    if (key == 123)
        p->center[0] += 0.1;
    if (key == 124)
        p->center[0] -= 0.1;
    if (key == 126)
        p->center[1] += 0.1;
    if (key == 125)
        p->center[1] -= 0.1;
}

void    zoom(t_param *p)
{
    p->radius /= 2;
}

int		keyboard_event(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (key == ESC)
		close_mlx((t_mlx*)param);
	if (key == 123 || key == 126 || key == 125 || key == 124)
	    move(key, mlx->img->params);
	if (key == 24)
	    zoom(mlx->img->params);
	render(mlx);
	return (1);
}

int     mouse_event(int key, void *param)
{
    t_mlx   *mlx;

    mlx = (t_mlx*)param;
    if (key)
        return (0);
    return (1);
}

void	event_handler(t_mlx *mlx)
{
	mlx_hook(mlx->win, RED_BUTTON, 1LU << (unsigned)17, close_mlx, mlx);
	mlx_hook(mlx->win, 2, 0, keyboard_event, mlx);
	mlx_hook(mlx->win, 4, 0, mouse_event, mlx);
}