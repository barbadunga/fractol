/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:25:18 by mshagga           #+#    #+#             */
/*   Updated: 2019/09/18 18:25:52 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int main(int argc, char **argv)
{
	t_fctl	*fctl;

	if (argc != 2)
		terminate(USAGE, NULL);
	if (!(fctl = (t_fctl*)malloc(sizeof(t_fctl))))
		terminate("error: malloc failure", NULL);
	if (!init_fractol(&fctl, argv[1]))
		terminate("error: init failure", &fctl);
	if (new_kernel(fctl))
		terminate("error: OpenCL failure", &fctl);
	event_handler(fctl);
	mlx_loop(fctl->mlx);
	return (1);
}
