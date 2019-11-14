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

	destroy_kernel(&(mlx->kernel));
	terminate("", &mlx);
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
	t_param	*p;

	p = ((t_mlx*)param)->img->params;
	if (key == ESC)
		close_mlx((t_mlx*)param);
	if (key == LEFT || key == UP || key == DOWN || key == RIGHT)
	    move(key, p);
	if (key == D_KEY)
	    set_default_view(p);
	if (key == S_KEY)
	    show();
	if (key == PLUS_KEY)
	    p->max_iter++;
	if (key == MINUS_KEY)
		p->max_iter -= p->max_iter > 1 ? 1 : 0;
    render(param);
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
        	p->radius *= pow(2.0, -0.1);
        if (button == SCROLL_DOWN)
            p->radius *= pow(2.0, 0.1);
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
        p->is_click = 0;
    x -= y;
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