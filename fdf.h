/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:26:07 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/07 19:09:48 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include <stdlib.h>
#include "mlx.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h> //remove this

int     draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color);
typedef struct s_mlx
{
    int     height;
    int     width;
    void    *init;
    void    *window;
    int     x1;
    int     y1;
    int     x2;
    int     y2;
    int     color; // separate rgb variables for clarity here?
}               t_mlx;

typedef struct s_map
{
    int     **map;
    int     rows;
    int     cols;
}               t_map;
t_mlx   *initialize_mlx_struct(void);
void    make_map(char *filename, t_map *s_map);
void    draw_map(t_mlx *mlx, t_map *s_map);
#endif
