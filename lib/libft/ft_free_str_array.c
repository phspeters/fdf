/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 20:59:29 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_str_array(char **str_array)
{
	int	i;

	if (str_array == NULL)
		return (NULL);
	i = 0;
	while (str_array[i] != NULL)
		free(str_array[i++]);
	free(str_array);
	return (NULL);
}
