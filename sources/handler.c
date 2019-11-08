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
#include <stdio.h>

int		close_mlx(void *param)
{
	t_mlx	*mlx;

	mlx = param;
	mlx_destroy_window(mlx->mlx, mlx->win);
	exit(1);
}

void    move(int key, t_param *p)
{
    if (key == LEFT)
        p->center[0] -= 0.1;
    if (key == RIGHT)
        p->center[0] += 0.1;
    if (key == UP)
        p->center[1] -= 0.1;
    if (key == DOWN)
        p->center[1] += 0.1;
}

void    show()
{

}

int		keyboard_event(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	if (key == ESC)
		close_mlx((t_mlx*)param);
	if (key == LEFT || key == UP || key == DOWN || key == RIGHT)
	    move(key, mlx->img->params);
	if (key == D_KEY)
	    set_default_view(mlx->img->params);
	if (key == S_KEY)
	    show();
	if (key == PLUS_KEY)
	    max_iter++;
	if (key == MINUS_KEY)
	    max_iter--;
    render(mlx);
	return (1);
}

int     mouse_press(int button, int x, int y, void *param)
{
    t_mlx       *mlx;
    t_param     *p;

    mlx = (t_mlx*)param;
    p = mlx->img->params;
    if (button == LEFT_BUTTON)
    {
        p->is_click = 1;
        p->click_pos[0] = x;
        p->click_pos[1] = y;
    }
    if (button == SCROLL_UP || button == SCROLL_DOWN)
    {
        if (button == SCROLL_UP)
            p->zoom++;
        if (button == SCROLL_DOWN)
            p->zoom--;
        p->radius *= pow(2.0, -p->zoom);
    }
    render(mlx);
    return (1);
}

int     mouse_release(int button, int x, int y, void *param)
{
    t_mlx   *mlx;
    t_param *p;

    mlx = (t_mlx*)param;
    p = mlx->img->params;
    if (button == LEFT_BUTTON)
    {
        p->is_click = 0;
        printf("click:\n\t%d\t%d\n", x - p->click_pos[0], y - p->click_pos[1]);
    }
    return (1);
}

int     mouse_move(int x, int y, void *param)
{
    t_mlx           *mlx;
    t_param         *p;
    const double   speed = 1.5; //

    mlx = (t_mlx*)param;
    p = mlx->img->params;
    if (p->is_click)
    {
        p->center[0] -= (double)(x - p->click_pos[0]) / WIDTH * p->radius * speed;
        p->center[1] -= (double)(y - p->click_pos[1]) / HEIGHT * p->radius * speed;
        p->click_pos[0] = x;
        p->click_pos[1] = y;
    }
    render(mlx);
    return (1);
}

void	event_handler(t_mlx *mlx)
{
	mlx_hook(mlx->win, RED_BUTTON, 1LU << (unsigned)17, close_mlx, mlx);
	mlx_hook(mlx->win, 2, 0, keyboard_event, mlx);
	mlx_hook(mlx->win, 4, 0, mouse_press, mlx);
	mlx_hook(mlx->win, 5, 0, mouse_release, mlx);
	mlx_hook(mlx->win, 6, 0, mouse_move, mlx);
}