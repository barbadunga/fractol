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

void	zoom(t_view *v, int button, int x, int y)
{
	double	prev;

	prev = v->radius;
	if (button == SCROLL_UP)
		v->radius *= pow(2.0, -0.1);
	if (button == SCROLL_DOWN)
		v->radius *= pow(2.0, 0.1);
	v->center[0] = v->center[0] + (x - WIDTH / 2) / (HEIGHT / 2.0) *
			(prev - v->radius);
	v->center[1] = v->center[1] - (y - HEIGHT / 2) / (HEIGHT / 2.0) *
			(prev - v->radius);
}

void	shift_color(t_view *v, int key)
{
	static int	iter;
	char		color[3];

	if (key == SCROLL_DOWN)
		iter++;
	else if (key == SCROLL_UP)
		iter--;
	color[0] = (char)(sin(0.1 * iter) * 127 + 128);
	color[1] = (char)(sin(0.2 * iter + 2) * 127 + 128);
	color[2] = (char)(sin(0.3 * iter + 4) * 127 + 128);
	(void)key;
	v->rgb[0] += (double)color[0] / 255;
	v->rgb[1] += (double)color[1] / 255;
	v->rgb[2] += (double)color[2] / 255;
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_fctl	*fctl;
	t_view	*v;

	fctl = (t_fctl*)param;
	v = fctl->view;
	if (button == LEFT_BUTTON)
	{
		v->click[0] = x;
		v->click[1] = y;
	}
	if (button == SCROLL_UP || button == SCROLL_DOWN)
	{
		if (v->pressed == CTRL_KEY)
			shift_color(v, button);
		else
			zoom(v, button, x, y);
	}
	render(fctl);
	return (1);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_fctl	*fctl;
	t_view	*v;

	fctl = (t_fctl*)param;
	v = fctl->view;
	if (button == LEFT_BUTTON)
	{
		v->click[0] = -1;
		v->click[1] = -1;
	}
	(void)x;
	(void)y;
	return (1);
}

int		mouse_move(int x, int y, void *param)
{
	t_view	*v;

	v = ((t_fctl*)param)->view;
	if (v->pressed == -1 && (v->click[0] >= 0 && v->click[1] >= 0))
	{
		v->center[0] -= (double)(x - v->click[0]) / WIDTH * v->radius * M_SPEED;
		v->center[1] += (double)(y - v->click[1]) /
						HEIGHT * v->radius * M_SPEED;
		v->click[0] = x;
		v->click[1] = y;
		render((t_fctl*)param);
	}
	if (v->pressed == CTRL_KEY && (v->click[0] >= 0 && v->click[1]))
	{
		v->constant[0] += (double)(x - v->click[0]) / WIDTH * v->radius;
		v->constant[1] += (double)(y - v->click[1]) / WIDTH * v->radius;
		v->click[0] = x;
		v->click[1] = y;
		render((t_fctl*)param);
	}
	return (1);
}
