/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:39:01 by mshagga           #+#    #+#             */
/*   Updated: 2019/11/27 16:39:01 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int     mouse_press(int button, int x, int y, void *param)
{
	t_fctl	*fctl;
	t_view	*v;
	double	old;

	fctl = (t_fctl*)param;
	v = fctl->img->view;
	old = v->radius;
	if (button == LEFT_BUTTON)
	{
		v->click[0] = x;
		v->click[1] = y;
	}
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
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
	{
		v->click[0] = -1;
		v->click[1] = -1;
	}
	(void)x;
	(void)y;
	return (1);
}

int     mouse_move(int x, int y, void *param)
{
	t_view	*v;

	v = ((t_fctl*)param)->img->view;
	if (v->pressed == -1 && (v->click[0] >= 0 || v->click[1] >= 0))
	{
		v->center[0] -= (double)(x - v->click[0]) / WIDTH * v->radius * M_SPEED;
		v->center[1] += (double)(y - v->click[1]) / HEIGHT* v->radius * M_SPEED;
		v->click[0] = x;
		v->click[1] = y;
	}
	if (v->pressed == CTRL_KEY)
	{
		v->constant[0] = -3 * sqrt((WIDTH / 2 - x) * (WIDTH / 2 - x)) / (WIDTH / 2);
		v->constant[0] += 3 * sqrt((HEIGHT / 2 - y) * (HEIGHT / 2 - y)) / (HEIGHT / 2);
		v->constant[1] = 3 * sqrt((WIDTH / 2 - x) * (WIDTH / 2 - x) + (HEIGHT / 2 - y) * (HEIGHT / 2 - y)) / (WIDTH / 2);
		v->constant[1] += 3 * 3 * sqrt((WIDTH / 2 - x) * (WIDTH / 2 - x) + (HEIGHT / 2 - y) * (HEIGHT / 2 - y)) / (HEIGHT / 2);
	}
	render((t_fctl*)param);
	return (1);
}