/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:26:07 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/10 18:34:23 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h> //remove this

# define WINDOW_WIDTH 640
# define WINDOW_HEIGHT 480
# define ZOOM 5
# define X_OFFSET 100
# define Y_OFFSET 100
# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124

typedef struct	s_map
{
	int		**map;
	int		rows;
	int		cols;
}				t_map;

typedef struct	s_mlx
{
	int		height;
	int		width;
	void	*init;
	void	*window;
	int		color; // separate rgb variables for clarity here?
	int		zoom;
	int		x_offset;
	int		y_offset;
	t_map	*s_map;
}				t_mlx;

t_mlx			*initialize_mlx_struct(void);
int				deal_key(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);
void			make_map(char *filename, t_map *s_map);
void			draw_map(t_mlx *mlx, t_map *s_map);
#endif
