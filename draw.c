/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:22:20 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/11 21:37:46 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	line_x(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	int	dir_x;
	int	dir_y;
	int	yi;
	int	d;
	int	y;
	int	pixel_x;
	int	pixel_y;

	y = 0;
	dir_x = x1 - x0;
	dir_y = y1 - y0;
	yi = 1;
	if (dir_y < 0)
	{
		yi = -1;
		dir_y *= -1;
	}
	d = 2 * dir_y - dir_x;
	pixel_y = y0;
	pixel_x = x0;
	while (pixel_x <= x1)
	{
		mlx_pixel_put(mlx->init, mlx->window, pixel_x, pixel_y, mlx->color);
		if (d > 0)
		{
			y += yi;
			d -= 2 * dir_x;
		}
		d += 2 * dir_y;
		pixel_x++;
	}
}

static void	line_y(t_mlx *mlx, int x0, int y0, int x1, int y1)
{
	int	dir_x;
	int	dir_y;
	int	xi;
	int	d;
	int	x;
	int	pixel_x;
	int	pixel_y;

	x = 0;
	dir_x = x1 - x0;
	dir_y = y1 - y0;
	xi = 1;
	if (dir_x < 0)
	{
		xi = -1;
		dir_x *= -1;
	}
	d = 2 * dir_x - dir_y;
	pixel_y = y0;
	pixel_x = x0;
	while (pixel_y <= y1)
	{
		mlx_pixel_put(mlx->init, mlx->window, pixel_x, pixel_y, mlx->color);
		if (d > 0)
		{
			x += xi;
			d -= 2 * dir_y;
		}
		d += 2 * dir_x;
		pixel_y++;
	}
}

static void	plot_line(t_mlx *mlx)
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
			line_x(mlx, x1, y1, x0, y0);
		else
			line_x(mlx, x0, y0, x1, y1);
	}
	else
	{
		if (y0 > y1)
			line_y(mlx, x1, y1, x0, y0);
		else
			line_y(mlx, x0, y0, x1, y1);
	}
}

t_line		*init_line(void)
{
	//move to other file
	t_line	*line;

	if (!(line = (t_line*)malloc(sizeof(*line))))
		return (NULL);
	line->xyxy[0] = 0;
	line->xyxy[1] = 0;
	line->xyxy[2] = 0;
	line->xyxy[3] = 0;
	line->color = DEFAULT_COLOR;
	return (line);
}

void		make_line(t_mlx *mlx, int coords[4])
{
	if (mlx->projection == 1)
	{
		//transform_to_isometric(mlx->s_line);
		transform_to_isometric(mlx->s_line, coords);
	}
	mlx->s_line->xyxy[0] = coords[0] * mlx->zoom + mlx->x_offset;
	mlx->s_line->xyxy[1] = coords[1] * mlx->zoom + mlx->y_offset;
	mlx->s_line->xyxy[2] = coords[2] * mlx->zoom + mlx->x_offset;
	mlx->s_line->xyxy[3] = coords[3] * mlx->zoom + mlx->y_offset;
}

void		draw_map(t_mlx *mlx, t_map *s_map)
{
	int		x;
	int		y;
	t_line	*line;

	y = 0;
	line = mlx->s_line;
	while (y < s_map->rows) // maybe add y-1 or y+1 if too many/too few rows
	{
		x = 0;
		//line->xyxy[0] = x * mlx->zoom + mlx->x_offset;
		//line->xyxy[1] = y * mlx->zoom + mlx->y_offset;
		//line->xyxy[2] = (x + 1) * mlx->zoom + mlx->x_offset;
		//line->xyxy[3] = y * mlx->zoom + mlx->y_offset;
		//plot_line(mlx);
		//line->xyxy[0] = x * mlx->zoom + mlx->x_offset;		//are these four needed?
		//line->xyxy[1] = y * mlx->zoom + mlx->y_offset;		//are these four needed?
		//line->xyxy[2] = x * mlx->zoom + mlx->x_offset; 			//are these four needed?
		//line->xyxy[3] = (y + 1) * mlx->zoom + mlx->y_offset; 	//are these four needed?
		//plot_line(mlx);
		while (x < s_map->cols) // maybe add x-1 or x+1 if too many/too few cols
		{
			if (x < s_map->cols && y < s_map->rows)
			{
				if (s_map->map[y][x])
					mlx->color = 0xFF0000;
				else
					mlx->color = DEFAULT_COLOR;
			}
			line->xyxy[4] = s_map->map[y][x];
			//if (mlx->projection == 1)
			//		transform_to_isometric(line, );
			if (x + 1 < s_map->cols)
			{
				make_line(mlx, (int [4]){x, y, x + 1, y});
				//line->xyxy[0] = x * mlx->zoom + mlx->x_offset;
				//line->xyxy[1] = y * mlx->zoom + mlx->y_offset;
				//line->xyxy[2] = (x + 1) * mlx->zoom + mlx->x_offset;
				//line->xyxy[3] = y * mlx->zoom + mlx->y_offset;

				plot_line(mlx);
			}
			if (y + 1 < s_map->rows)
			{
				make_line(mlx, (int [4]){x, y, x, y + 1});
				//line->xyxy[0] = x * mlx->zoom + mlx->x_offset;	//are these needed?
				//line->xyxy[1] = y * mlx->zoom + mlx->y_offset;	//are these needed?
				//line->xyxy[2] = x * mlx->zoom + mlx->x_offset;
				//line->xyxy[3] = (y + 1) * mlx->zoom + mlx->y_offset;

				plot_line(mlx);
			}
			x++;
		}
		y++;
	}
}

void		transform_to_isometric(t_line *line, int coords[4])
{
	int	previous_x;
	int	previous_y;
	previous_x = coords[0];
	previous_y = coords[1];
	printf("%d, %d, %d\n", previous_x, previous_y, line->xyxy[4]);
	coords[0] = (previous_x - previous_y) * cos(0.523599);
	coords[1] = -line->xyxy[4] + (previous_x + previous_y) * sin(0.523599);
	previous_x = coords[2];
	previous_y = coords[3];
	coords[2] = (previous_x - previous_y) * cos(0.523599);
	coords[3] = -line->xyxy[4] + (previous_x + previous_y) * sin(0.523599);
	//if (line->xyxy[0] && line->xyxy[1] && line->xyxy[2] && line->xyxy[3])
	//{
	/*previous_x = line->xyxy[0];
	previous_y = line->xyxy[1];
	printf("%d, %d, %d\n", previous_x, previous_y, line->xyxy[4]);
	line->xyxy[0] = (previous_x - previous_y) * cos(0.523599);
	line->xyxy[1] = -line->xyxy[4] + (previous_x + previous_y) * sin(0.523599);
	previous_x = line->xyxy[2];
	previous_y = line->xyxy[3];
	line->xyxy[2] = (previous_x - previous_y) * cos(0.523599);
	line->xyxy[3] = -line->xyxy[4] + (previous_x + previous_y) * sin(0.523599);
	*/
	//}
}
