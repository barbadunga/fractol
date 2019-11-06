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

# define WIDTH 1920
# define HEIGHT 1080

# define RED_BUTTON	17
# define ESC		53

typedef struct	s_img
{
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
	cl_device_id        device;
	cl_platform_id      platform;
	cl_command_queue	queue;
	cl_program          prog;
	cl_context          ctx;
	cl_mem              buffer;
}				t_kernel;

void	event_handler(t_mlx *mlx);

/*
 * OpenCL kernel setup functions
 */
t_kernel    *init_kernel();
int		    run_kernel(void *data);

/*
 * Additional tools
 */
char    *read_kernel(char *filename);
void	terminate(const char *err_mes);

/*
 * Delete it
 */
void    single_thread(void *data);

/*
 * Debug info
 */
void    get_platform_info(cl_platform_id id);
cl_device_id    get_device_info(cl_platform_id id, cl_device_info value_name);
void    print_device_info(cl_device_id id);
void    get_context_info(cl_context ctx);
void    get_build_log(cl_program prog, cl_device_id id, cl_int errno);

#endif
