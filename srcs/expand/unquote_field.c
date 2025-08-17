/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_field.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:47:57 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/16 21:52:55 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "expand.h"

char	*unquote_value(char *value)
{
	char	*new_value;
	char	*last;

	last = value;
	while (*last)
		last++;
	last--;
	if (value == last)
		return (value);
	if ((*value == '\'' && *last == '\'')
		|| (*value == '\"' && *last == '\"'))
	{
		new_value = ft_substr(value, 1, last - value);
		free(value);
		return (new_value);
	}
	return (value);
}
