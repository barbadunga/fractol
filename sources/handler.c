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

int		close_window(void *param)
{
	t_fctl	*fctl;

	fctl = param;
	terminate(NULL, &fctl);
	return (1);
}

void    move(int key, t_view *p)
{
    if (key == LEFT)
        p->center[0] -= 0.1 * p->radius;
    if (key == RIGHT)
        p->center[0] += 0.1 * p->radius;
    if (key == UP)
        p->center[1] += 0.1 * p->radius;
    if (key == DOWN)
        p->center[1] -= 0.1 * p->radius;
}

int		keyboard_event(int key, void *param)
{
	t_view	*v;

	v = ((t_fctl*)param)->img->view;
	if (key == ESC)
		close_window((t_fctl *)param);
	if (key == LEFT || key == UP || key == DOWN || key == RIGHT)
	    move(key, v);
	if (key == D_KEY)
	    set_default_view(v, 'a');
	if (key == PLUS_KEY)
	    v->max_iter++;
	if (key == MINUS_KEY)
		v->max_iter -= v->max_iter > 1 ? 1 : 0;
    render(param);
	return (1);
}

int     mouse_press(int button, int x, int y, void *param)
{
    t_fctl	*fctl;
    t_view	*v;

    fctl = (t_fctl*)param;
    v = fctl->img->view;
    if (button == LEFT_BUTTON)
    {
        v->is_click = 1;
        v->click[0] = x;
        v->click[1] = y;
    }
    if (button == SCROLL_UP || button == SCROLL_DOWN)
    {
    	double	old = v->radius;
        if (button == SCROLL_UP)
			v->radius *= pow(2.0, -0.1);
		if (button == SCROLL_DOWN)
			v->radius *= pow(2.0, 0.1);
		v->center[0] = v->center[0] + (x - WIDTH / 2) / (HEIGHT / 2.0) * (old - v->radius);
		v->center[1] = v->center[1] - (y - HEIGHT / 2) / (HEIGHT / 2.0) * (old - v->radius);
	}
    render(fctl);
    return (1);
}

int     mouse_release(int button, int x, int y, void *param)
{
    t_fctl	*fctl;
    t_view	*v;

    fctl = (t_fctl*)param;
    v = fctl->img->view;
    if (button == LEFT_BUTTON)
        v->is_click = 0;
    x -= y; // lol
    return (1);
}

int     mouse_move(int x, int y, void *param)
{
    t_fctl			*fctl;
    t_view			*v;
    const double   speed = 1.5;

    fctl = (t_fctl*)param;
    v = fctl->img->view;
    if (v->is_click)
    {
        v->center[0] -= (double)(x - v->click[0]) / WIDTH * v->radius * speed;
        v->center[1] += (double)(y - v->click[1]) / HEIGHT * v->radius * speed;
        v->click[0] = x;
        v->click[1] = y;
    }
    render(fctl);
    return (1);
}

void	event_handler(t_fctl *fctl)
{
	mlx_hook(fctl->win, RED_BUTTON, 1LU << (unsigned)17, close_window, fctl);
	mlx_hook(fctl->win, 2, 0, keyboard_event, fctl);
	mlx_hook(fctl->win, 4, 0, mouse_press, fctl);
	mlx_hook(fctl->win, 5, 0, mouse_release, fctl);
	mlx_hook(fctl->win, 6, 0, mouse_move, fctl);
}