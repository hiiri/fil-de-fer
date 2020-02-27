/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:36:04 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/27 20:03:03 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			handle_color(t_mlx *mlx, int z1, int z2)
{
	double	z1_scaled;
	double	z2_scaled;
	double	diff;
	double	slope;

	slope = 1.0 * (1 - 0) / (mlx->biggest_z - mlx->smallest_z);
	z1_scaled = 0 + slope * (z1 - mlx->smallest_z);
	z2_scaled = 0 + slope * (z2 - mlx->smallest_z);
	if (z1_scaled <= z2_scaled)
	{
		diff = z2_scaled - z1_scaled;
	}
	else
	{
		diff = z1_scaled - z2_scaled;
	}
	if (z1_scaled < 0.6 || z2_scaled < 0.6)
		mlx->color = 0x3399ff;
	else if (z1_scaled < 0.7 || z2_scaled < 0.7)
		mlx->color = 0x00cc66;
	else if (z1_scaled < 0.8 || z2_scaled < 0.8)
		mlx->color = 0x009900;
	else
		mlx->color = 0x336600;
}

void			vert_line(t_mlx *mlx, t_map *s_map, int xy[4], t_line *line)
{
	handle_color(mlx, s_map->map[xy[1]][xy[0]], s_map->map[xy[3]][xy[2]]);
	line->xyxy[5] = s_map->map[xy[1]][xy[2]] * mlx->zoom * mlx->pitch;
	make_line(mlx, (int[4]){xy[0], xy[1], xy[2], xy[3]});
	plot_line(mlx);
}

void			horiz_line(t_mlx *mlx, t_map *s_map, int xy[4], t_line *line)
{
	handle_color(mlx, s_map->map[xy[1]][xy[0]], s_map->map[xy[3]][xy[2]]);
	line->xyxy[5] = s_map->map[xy[3]][xy[0]] * mlx->zoom * mlx->pitch;
	make_line(mlx, (int[4]){xy[0], xy[1], xy[2], xy[3]});
	plot_line(mlx);
}

void			make_line(t_mlx *mlx, int coords[4])
{
	coords[0] = coords[0] * mlx->zoom;
	coords[1] = coords[1] * mlx->zoom;
	coords[2] = coords[2] * mlx->zoom;
	coords[3] = coords[3] * mlx->zoom;
	if (mlx->projection == 1)
	{
		transform_to_isometric(mlx->s_line, coords);
	}
	mlx->s_line->xyxy[0] = coords[0] + mlx->x_offset;
	mlx->s_line->xyxy[1] = coords[1] + mlx->y_offset;
	mlx->s_line->xyxy[2] = coords[2] + mlx->x_offset;
	mlx->s_line->xyxy[3] = coords[3] + mlx->y_offset;
}

t_line			*init_line(void)
{
	t_line	*line;

	if (!(line = (t_line*)malloc(sizeof(*line))))
		handle_error(ERROR_MALLOC);
	line->xyxy[0] = 0;
	line->xyxy[1] = 0;
	line->xyxy[2] = 0;
	line->xyxy[3] = 0;
	line->color = DEFAULT_COLOR;
	return (line);
}
