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

int		keyboard_event(int key, void *param)
{
	t_view	*v;

	v = ((t_fctl*)param)->img->view;
	if (key == ESC)
		close_window((t_fctl *)param);
	if (key == LEFT || key == UP || key == DOWN || key == RIGHT)
		move(key, v);
	if (key == D_KEY)
		set_default_view(v, ((t_fctl*)param)->name);
	if (key == PLUS_KEY)
		v->max_iter++;
	if (key == MINUS_KEY)
		v->max_iter -= v->max_iter > 1 ? 1 : 0;
	if (key == CTRL_KEY)
		v->pressed = CTRL_KEY;
	if (key == H_KEY)
		v->help = v->help ? 0 : 1;
	render((t_fctl*)param);
	return (1);
}

int		keyboard_release(int key, void *param)
{
	t_view	*v;

	v = ((t_fctl*)param)->img->view;
	v->pressed = -1;
	if (key == CTRL_KEY)
	{
		v->click[0] = -1;
		v->click[1] = -1;
	}
	render((t_fctl*)param);
	return (1);
}