/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_to_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:27:39 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/10 18:39:59 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	count_ints(char *s)
{
	size_t	i;
	size_t	count;
	int		flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i])
	{
		if (flag && s[i] == ' ')
			flag = 0;
		if (!flag && s[i] != ' ')
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static void		split_line_to_map(char *line, t_map *s_map)
{
	size_t	count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	count = count_ints(line);
	if (!(s_map->map[s_map->rows] = (int *)malloc(sizeof(int) * count)))
		exit(0);
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		s_map->map[s_map->rows][j++] = ft_atoi(&line[i]);
		while (line[i] != ' ' && line[i])
			i++;
	}
	s_map->rows++;
	s_map->cols = j;
}

static void		malloc_row(t_map *s_map)
{
	int		**temp;
	int		i;

	temp = (int **)malloc(sizeof(int *) * s_map->rows);
	ft_memcpy(temp, s_map->map, sizeof(int **) * s_map->rows);
	if (s_map->rows)
		free(s_map->map);
	s_map->map = (int **)malloc(sizeof(int *) * s_map->rows + 1);
	i = 0;
	while (i < s_map->rows)
	{
		s_map->map[i] = temp[i];
		i++;
	}
}

void			make_map(char *filename, t_map *s_map)
{
	int		fd;
	char	*line;

	s_map->rows = 0;
	s_map->cols = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		malloc_row(s_map);
		split_line_to_map(line, s_map);
		free(line);
	}
	close(fd);
}
