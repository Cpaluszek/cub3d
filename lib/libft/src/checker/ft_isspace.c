/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 11:52:53 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/26 11:54:43 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace(const int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' \
			|| c == '\v' || c == '\f');
}
