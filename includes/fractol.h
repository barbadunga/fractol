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
# include <limits.h>

/*
 * Screen settings
 */
# define WIDTH          900
# define HEIGHT         900

/*
 * Control keys MacOs
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
# define H_KEY			4
# define S_KEY          1
# define PLUS_KEY       24
# define MINUS_KEY      27

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

typedef struct  s_param
{
	char	*name;
    double  center[2];
    int     click_pos[2];
    double  radius;
    int		max_iter;
    int     is_click;
}               t_param;

typedef struct	s_img
{
    t_param	*params;
	void	*img_ptr;
	int		bpp;
	int		size_line;
	int		end;
}				t_img;

typedef struct s_mngr
{
	void		*win;
	void		*mlx;
	t_img		*img;
	char		*data;
	t_kernel	*kernel;
}				t_mngr;

void	event_handler(t_mngr *mngr);
void    set_default_view(t_param *p);
/*
 * OpenCL kernel setup functions
 */
t_kernel    *init_kernel();
int		    new_kernel(t_mngr *mngr);
int			run_kernel(t_mngr * mngr);
void        destroy_kernel(t_kernel *kernel);

/*
 * Additional tools
 */
char    *read_kernel(char *filename);
void	terminate(const char *err_mes, t_mngr *mngr);
void    render(t_mngr *mngr);

/*
 * Debug info
 */
void    get_platform_info(cl_platform_id id);
cl_device_id    get_device_info(cl_platform_id id, cl_device_info value_name);
void    print_device_info(cl_device_id id);
void    get_context_info(cl_context ctx);
void    get_build_log(cl_program prog, cl_device_id id, cl_int errno);

#endif
