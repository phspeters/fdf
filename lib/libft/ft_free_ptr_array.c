/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@42sp.com.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/27 16:03:50 by pehenri2         ###   ########.fr       */
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
