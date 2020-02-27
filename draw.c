/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:22:20 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/27 20:02:52 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		line_x(t_mlx *mlx, int xy[4])
{
	int	dirs[3];
	int	d;
	int	pixels[2];

	dirs[0] = xy[2] - xy[0];
	dirs[1] = xy[3] - xy[1];
	dirs[2] = 1;
	if (dirs[1] < 0)
	{
		dirs[2] = -1;
		dirs[1] *= -1;
	}
	d = 2 * dirs[1] - dirs[0];
	pixels[1] = xy[1];
	pixels[0] = xy[0];
	while (++pixels[0] <= xy[2])
	{
		mlx_pixel_put(mlx->init, mlx->window, pixels[0], pixels[1], mlx->color);
		if (d > 0)
		{
			pixels[1] += dirs[2];
			d -= 2 * dirs[0];
		}
		d += 2 * dirs[1];
	}
}

static void		line_y(t_mlx *mlx, int xy[4])
{
	int	dirs[3];
	int	d;
	int	pixels[2];

	dirs[0] = xy[2] - xy[0];
	dirs[1] = xy[3] - xy[1];
	dirs[2] = 1;
	if (dirs[0] < 0)
	{
		dirs[2] = -1;
		dirs[0] *= -1;
	}
	d = 2 * dirs[0] - dirs[1];
	pixels[1] = xy[1];
	pixels[0] = xy[0];
	while (++pixels[1] <= xy[3])
	{
		mlx_pixel_put(mlx->init, mlx->window, pixels[0], pixels[1], mlx->color);
		if (d > 0)
		{
			pixels[0] += dirs[2];
			d -= 2 * dirs[1];
		}
		d += 2 * dirs[0];
	}
}

void			plot_line(t_mlx *mlx)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;

	x0 = mlx->s_line->xyxy[0];
	y0 = mlx->s_line->xyxy[1];
	x1 = mlx->s_line->xyxy[2];
	y1 = mlx->s_line->xyxy[3];
	if (abs(y1 - y0) < abs(x1 - x0))
	{
		if (x0 > x1)
			line_x(mlx, (int[4]){x1, y1, x0, y0});
		else
			line_x(mlx, (int[4]){x0, y0, x1, y1});
	}
	else
	{
		if (y0 > y1)
			line_y(mlx, (int[4]){x1, y1, x0, y0});
		else
			line_y(mlx, (int[4]){x0, y0, x1, y1});
	}
}

void			draw_map(t_mlx *mlx, t_map *s_map)
{
	int		x;
	int		y;
	t_line	*line;

	y = 0;
	line = mlx->s_line;
	while (y < s_map->rows)
	{
		x = 0;
		while (x < s_map->cols)
		{
			line->xyxy[4] = s_map->map[y][x] * mlx->zoom * mlx->pitch;
			if (x + 1 < s_map->cols)
			{
				vert_line(mlx, s_map, (int[4]){x, y, x + 1, y}, line);
			}
			if (y + 1 < s_map->rows)
			{
				horiz_line(mlx, s_map, (int[4]){x, y, x, y + 1}, line);
			}
			x++;
		}
		y++;
	}
}

void			transform_to_isometric(t_line *line, int coords[4])
{
	int	previous_x;
	int	previous_y;

	previous_x = coords[0];
	previous_y = coords[1];
	coords[0] = (previous_x - previous_y) * cos(0.523599);
	coords[1] = -line->xyxy[4] + (previous_x + previous_y) * sin(0.523599);
	previous_x = coords[2];
	previous_y = coords[3];
	coords[2] = (previous_x - previous_y) * cos(0.523599);
	coords[3] = -line->xyxy[5] + (previous_x + previous_y) * sin(0.523599);
}
