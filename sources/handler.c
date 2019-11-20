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
	t_mngr	*mngr;

	mngr = param;
	terminate("", mngr);
	return (1);
}

void    move(int key, t_param *p)
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
	t_param	*p;

	p = ((t_mngr*)param)->img->params;
	if (key == ESC)
		close_window((t_mngr *)param);
	if (key == LEFT || key == UP || key == DOWN || key == RIGHT)
	    move(key, p);
	if (key == D_KEY)
	    set_default_view(p);
	if (key == PLUS_KEY)
	    p->max_iter++;
	if (key == MINUS_KEY)
		p->max_iter -= p->max_iter > 1 ? 1 : 0;
    render(param);
	return (1);
}

int     mouse_press(int button, int x, int y, void *param)
{
    t_mngr       *mngr;
    t_param     *p;

    mngr = (t_mngr*)param;
    p = mngr->img->params;
    if (button == LEFT_BUTTON)
    {
        p->is_click = 1;
        p->click_pos[0] = x;
        p->click_pos[1] = y;
    }
    if (button == SCROLL_UP || button == SCROLL_DOWN)
    {
    	double	old = p->radius;
        if (button == SCROLL_UP)
			p->radius *= pow(2.0, -0.1);
		if (button == SCROLL_DOWN)
			p->radius *= pow(2.0, 0.1);
		p->center[0] = p->center[0] + (x - WIDTH / 2) / (HEIGHT / 2.0) * (old - p->radius);
		p->center[1] = p->center[1] - (y - HEIGHT / 2) / (HEIGHT / 2.0) * (old - p->radius);
	}
    render(mngr);
    return (1);
}

int     mouse_release(int button, int x, int y, void *param)
{
    t_mngr   *mngr;
    t_param *p;

    mngr = (t_mngr*)param;
    p = mngr->img->params;
    if (button == LEFT_BUTTON)
        p->is_click = 0;
    x -= y;
    return (1);
}

int     mouse_move(int x, int y, void *param)
{
    t_mngr           *mngr;
    t_param         *p;
    const double   speed = 1.5;

    mngr = (t_mngr*)param;
    p = mngr->img->params;
    if (p->is_click)
    {
        p->center[0] -= (double)(x - p->click_pos[0]) / WIDTH * p->radius * speed;
        p->center[1] += (double)(y - p->click_pos[1]) / HEIGHT * p->radius * speed;
        p->click_pos[0] = x;
        p->click_pos[1] = y;
    }
    render(mngr);
    return (1);
}

void	event_handler(t_mngr *mngr)
{
	mlx_hook(mngr->win, RED_BUTTON, 1LU << (unsigned)17, close_window, mngr);
	mlx_hook(mngr->win, 2, 0, keyboard_event, mngr);
	mlx_hook(mngr->win, 4, 0, mouse_press, mngr);
	mlx_hook(mngr->win, 5, 0, mouse_release, mngr);
	mlx_hook(mngr->win, 6, 0, mouse_move, mngr);
}