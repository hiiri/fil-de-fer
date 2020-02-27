/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:26:07 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/27 20:14:36 by alcohen          ###   ########.fr       */
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

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define ZOOM 5
# define X_OFFSET 100
# define Y_OFFSET 0
# define OFFSET_AMOUNT 5
# define PITCH_CHANGE_AMOUNT 0.01
# define DEFAULT_COLOR 0xFFFFFF
# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define Q 12
# define W 13
# define CHANGE_PROJECTION 35
# define ERROR_ARGS 1
# define ERROR_MALLOC 2
# define ERROR_READING_FILE 3
# define ERROR_INVALID_MAP 4

/*
**	Keys:
**	P = Change projection
*/

typedef struct	s_map
{
	int		**map;
	int		rows;
	int		cols;
}				t_map;

/*
**	xyxy[0] = x0, xyxy[1] = y0, xyxy[2] = x1,
**	xyxy[3] = y1, xyxy[4] = z1, xyxy[5] = z2
*/

typedef struct	s_line
{
	double		xyxy[6];
	int			color;
}				t_line;

typedef struct	s_mlx
{
	int		height;
	int		width;
	void	*init;
	void	*window;
	int		zoom;
	int		x_offset;
	int		y_offset;
	int		smallest_z;
	int		biggest_z;
	int		color;
	int		projection;
	int		mouse_x;
	int		mouse_y;
	int		mouse_pressed;
	double	pitch;
	t_map	*s_map;
	t_line	*s_line;
}				t_mlx;

t_mlx			*initialize_mlx_struct(void);
t_line			*init_line(void);
int				deal_key(int key, void *param);
int				mouse_event(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);
void			make_map(char *filename, t_map *s_map);
void			vert_line(t_mlx *mlx, t_map *s_map, int xy[4], t_line *line);
void			horiz_line(t_mlx *mlx, t_map *s_map, int xy[4], t_line *line);
void			plot_line(t_mlx *mlx);
void			handle_color(t_mlx *mlx, int z1, int z2);
void			draw_map(t_mlx *mlx, t_map *s_map);
void			make_line(t_mlx *mlx, int coords[4]);
void			transform_to_isometric(t_line *line, int coords[4]);
void			handle_error(int error);
void			store_number_to_map_if_int(long n, t_map *s_map, int column);
int				is_minus_symbol(char c);

#endif
