/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:41:01 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/10 14:46:43 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

vector_t	vector_add(vector_t a, vector_t b)
{
	vector_t	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

vector_t	vector_sub(vector_t a, vector_t b)
{
	vector_t	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

vector_t	vector_scale(vector_t a, double scalar)
{
	vector_t	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	return (result);
}
