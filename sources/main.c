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

int	main(int argc, char **argv)
{
	t_fctl		*fctl;
	char		*name;

	if (argc != 2)
		terminate(USAGE, NULL);
	if (!(fctl = (t_fctl*)malloc(sizeof(t_fctl))))
		terminate("error: malloc failure", NULL);
	name = ft_tolowercase(argv[1]);
	if (!init_fractol(&fctl, name))
		terminate("error: init failure", &fctl);
	if (new_kernel(fctl, CL_DEVICE_TYPE_GPU))
		terminate("error: OpenCL failure", &fctl);
	event_handler(fctl);
	mlx_loop(fctl->mlx);
	return (1);
}
