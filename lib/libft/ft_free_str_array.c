/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@42sp.com.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/27 16:03:46 by pehenri2         ###   ########.fr       */
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
