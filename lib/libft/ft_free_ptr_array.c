/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:17:02 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/24 15:22:32 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_ptr_array(void **split, size_t size)
{
	size_t	i;

	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		free(split[i++]);
	free(split);
	return (NULL);
}

// void	*ft_free_ptr_array(char **split)
//{
//	int	i;

//	if (split == NULL)
//		return (NULL);
//	i = 0;
//	while (split[i] != NULL)
//		free(split[i++]);
//	free(split);
//	return (NULL);
//}
