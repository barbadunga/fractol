/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: AlexandrSergeev <marvin@42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 21:32:00 by AlexandrSergeev   #+#    #+#             */
/*   Updated: 2019/11/04 21:32:00 by AlexandrSergeev  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	terminate(const char *err_mes)
{
	ft_putstr(err_mes);
	exit(1);
}