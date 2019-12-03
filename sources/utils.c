/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:53:53 by mshagga           #+#    #+#             */
/*   Updated: 2019/11/21 15:53:53 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	terminate(char *err, t_fctl **fractol)
{
	if (err)
		ft_putendl(err);
	if (fractol)
	{
		if ((*fractol)->win)
			mlx_destroy_window((*fractol)->mlx, (*fractol)->win);
		if ((*fractol)->view)
			free((*fractol)->view);
		if ((*fractol)->img)
		{
			free((*fractol)->img);
			if ((*fractol)->img->img_ptr)
				mlx_destroy_image((*fractol)->mlx, (*fractol)->img->img_ptr);
		}
		if ((*fractol)->kernel)
		{
			destroy_kernel((*fractol)->kernel);
			free((*fractol)->kernel);
		}
		free(*fractol);
		*fractol = NULL;
	}
	exit(err ? EXIT_FAILURE : EXIT_SUCCESS);
}

void	destroy_kernel(t_kernel *kernel)
{
	if (kernel->core)
		clReleaseKernel(kernel->core);
	if (kernel->buffer)
		clReleaseMemObject(kernel->buffer);
	if (kernel->ctx)
		clReleaseContext(kernel->ctx);
	if (kernel->queue)
		clReleaseCommandQueue(kernel->queue);
	if (kernel->prog)
		clReleaseProgram(kernel->prog);
}

char	*read_kernel(char *filename)
{
	int		fd;
	char	*kernel;
	t_vec	*vec;
	char	buf[1];

	fd = open(filename, O_RDONLY);
	if (!(vec = ft_vec_init(1, sizeof(char))))
		return (NULL);
	if (fd < 0 && read(fd, NULL, 0) < 0)
		return (NULL);
	while ((read(fd, buf, 1)) > 0)
		if (!ft_vec_add(&vec, buf))
			return (NULL);
	ft_vec_add(&vec, "\0");
	if (!(kernel = (char*)malloc(vec->total)))
	{
		ft_vec_del(&vec);
		return (NULL);
	}
	ft_strncpy(kernel, vec->data, vec->total + 1);
	ft_vec_del(&vec);
	if (close(fd) < 0)
		return (NULL);
	return (kernel);
}
