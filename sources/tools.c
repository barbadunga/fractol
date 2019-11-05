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
#include <stdio.h>

void	terminate(const char *err_mes)
{
	ft_putstr(err_mes);
	exit(1);
}

char *read_kernel(char *filename)
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
    if (!(ft_vec_resize(&vec)))
    {
        ft_vec_del(&vec);
        return (NULL);
    }
    kernel = vec->data;
    ft_vec_del(&vec);
    return (kernel);
}