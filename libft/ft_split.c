/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:02:39 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/15 18:06:59 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		count_segs(char const *s, char c)
{
	int		i;
	size_t	segs;
	int		next_seg;

	next_seg = 1;
	segs = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			next_seg = 1;
		else
		{
			if (next_seg)
			{
				segs++;
				next_seg = 0;
			}
		}
		i++;
	}
	return (segs);
}

static	void	free_array(char **array, int i)
{
	while (i >= 0)
	{
		if (array[i])
			free(array[i--]);
	}
	free(array);
}

static	char	*split_seg(char const *s, char c)
{
	char	*seg;
	int		j;

	j = 0;
	while (*(s + j) != c && *(s + j))
		j++;
	if (!(seg = ft_substr(s, 0, j)))
		return (NULL);
	return (seg);
}

char			**ft_split(char const *s, char c)
{
	char	**output;
	int		i;
	int		segs;

	segs = count_segs(s, c);
	if (!(output = malloc(sizeof(char *) * (segs + 1))))
		return (NULL);
	i = 0;
	while (i < segs)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(output[i++] = split_seg(s, c)))
			{
				free_array(output, i);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
	}
	output[i] = NULL;
	return (output);
}
