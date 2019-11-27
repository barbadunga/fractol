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

void	event_handler(t_fctl *fctl)
{
	mlx_hook(fctl->win, RED_BUTTON, 1LU << (unsigned)17, close_window, fctl);
	mlx_hook(fctl->win, 2, 0, keyboard_event, fctl);
	mlx_hook(fctl->win, 3, 0, keyboard_release, fctl);
	mlx_hook(fctl->win, 4, 0, mouse_press, fctl);
	mlx_hook(fctl->win, 5, 0, mouse_release, fctl);
	mlx_hook(fctl->win, 6, 0, mouse_move, fctl);
	mlx_expose_hook(fctl->win, render, fctl);
}