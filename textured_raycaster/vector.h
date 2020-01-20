/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 14:44:00 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/10 15:48:56 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct	vector_s
{
	double		x;
	double		y;
}				vector_t;

vector_t	vector_add(vector_t a, vector_t b);
vector_t	vector_sub(vector_t a, vector_t b);
vector_t	vector_scale(vector_t a, double scalar);

#endif
