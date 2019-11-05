/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshagga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:26:32 by mshagga           #+#    #+#             */
/*   Updated: 2019/09/18 18:27:39 by mshagga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL _H

# include "libft.h"
# include "mlx.h"
# include <OpenCL/opencl.h>
# include <math.h>

# define WIDTH 900
# define HEIGHT 600

# define RED_BUTTON	17
# define ESC		53

typedef struct	s_img
{
//	char	*data;
	void 	*img;
	int		bpp;
	int		size_line;
	int		end;
}				t_img;

typedef struct s_mlx
{
	void	*win;
	void	*mlx;
	t_img	*img;
	char	*data;
}				t_mlx;

typedef struct	s_kernel
{
	cl_kernel			core;
	cl_command_queue	queue;
	void				*data;
	
	cl_mem		*data_mem;

}				t_kernel;

void	*ptr = clCreateBuffer()
void	event_handler(t_mlx *mlx);
void	terminate(const char *err_mes);
int		run_kernel(t_mlx *mlx);

#endif
