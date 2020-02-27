/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:43:21 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/27 16:52:57 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	store_number_to_map_if_int(long n, t_map *s_map, int column)
{
	int	max_int = 2147483647;
	int	min_int = -2147483648;
		if (n > max_int || n < min_int)
			handle_error(ERROR_INVALID_MAP);
	s_map->map[s_map->rows][column] = (int)n;
}
