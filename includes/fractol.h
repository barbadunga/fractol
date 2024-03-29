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

# define LEFT_BUTTON    1
# define RIGHT_BUTTON	2
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
# define R_KEY			15
# define G_KEY			5
# define B_KEY			11
# define L_SHIFT		43
# define R_SHIFT		47
# define H_KEY			4
# define CTRL_KEY		256
# define PLUS_KEY       24
# define MINUS_KEY      27

# define BLACK			0x0
# define RED			0x0000FF
# define GREEN			0x00FF
# define BLUE			0xFF
# define WHITE			0xFFFFFF
# define SILVER			0xC0C0C0

# define HEIGHT			900
# define WIDTH			900
# define M_SPEED		1.5

typedef struct	s_kernel
{
	cl_kernel			core;
	cl_device_id		device;
	cl_platform_id		platform;
	cl_command_queue	queue;
	cl_program			prog;
	cl_context			ctx;
	cl_mem				buffer;
}				t_kernel;

typedef	struct	s_view
{
	double			center[2];
	double			constant[2];
	double			rgb[3];
	int				click[2];
	double			radius;
	unsigned int	max_iter;
	int				pressed;
	int				help;
}				t_view;

typedef struct	s_img
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		end;

}				t_img;

typedef struct	s_fctl
{
	void		*mlx;
	void		*win;
	t_img		*img;
	t_kernel	*kernel;
	char		*name;
	t_view		*view;
}				t_fctl;

int				init_fractol(t_fctl **fctl, char *name);
void			set_default_view(t_view *view, char *name);
int				new_kernel(t_fctl *fctl, int device_type);
char			*get_name(char	*input);

void			terminate(char *err, t_fctl **fractol);
void			destroy_kernel(t_kernel *kernel);
char			*read_kernel(char *filename);

int				render(t_fctl *f);
void			event_handler(t_fctl *fctl);
int				run_kernel(t_fctl *fctl);

void			get_build_log(cl_program prog, cl_device_id id, cl_int errno);
void			print_device_info(cl_device_id id);
void			get_platform_info(cl_platform_id id);
cl_device_id	get_device_info(cl_platform_id id, cl_device_info value_name);

int				keyboard_event(int key, void *param);
int				keyboard_release(int key, void *param);
int				mouse_press(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
int				close_window(void *param);
void			move(int key, t_view *p);

#endif
