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

/*
 * Keyboard keys MacOs
 */
# define LEFT_BUTTON    1
# define SCROLL_UP      4
# define SCROLL_DOWN    5
# define LEFT           123
# define UP             126
# define RIGHT          124
# define DOWN           125
# define RED_BUTTON     17
# define ESC            53
# define D_KEY          2
# define C_KEY          8
# define S_KEY          1
# define PLUS_KEY       24
# define MINUS_KEY      27

# define HEIGHT			900
# define WIDTH			900
# define USAGE			"usage: ./fractol [name]\n\nAvailable fractals:\n --> Mandelbrot\n --> Julia"

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

typedef	struct	s_view
{
	double			center[2];
	int				click[2];
	double			radius;
	unsigned int	max_iter;
	char			is_click;
}				t_view;

typedef struct	s_img
{
	t_view	*view;
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		end;

}				t_img;

typedef struct s_fctl
{
	void 		*mlx;
	void		*win;
	t_img		*img;
	t_kernel	*kernel;
	char		*name;
}				t_fctl;

/*
 * Init funcs
 */
int		init_fractol(t_fctl *fctl, char	*name);
void	set_default_view(t_view *view, char name);
int		new_kernel(t_fctl *fctl);

/*
 * Util funcs
 */
void	terminate(char *err, t_fctl **fractol);
void	destroy_kernel(t_kernel *kernel);
char	*read_kernel(char *filename);

/*
 * Event handler
 */
void	event_handler(t_fctl *fctl);

/*
 * Main funcs
 */
void	render(t_fctl *f);

/*
 * OpenCL functions
 */
int		run_kernel(t_fctl *fctl);


void	single_thread(void *data, t_view *v);
#endif
