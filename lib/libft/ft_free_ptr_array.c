/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peters <peters@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 20:59:01 by peters           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_ptr_array(void **ptr_array, size_t size)
{
	size_t	i;

	if (ptr_array == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		free(ptr_array[i++]);
	free(ptr_array);
	return (NULL);
}
