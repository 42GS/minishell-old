/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_field.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 19:16:58 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/17 01:18:46 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "flag.h"
#include "utils.h"

#include "tokenizer.h"

#include "debug.h"

static int	count_fields(char *value);
static char	**split_value(char *value);

t_token	*split_field(t_token *token)
{
	t_token	*cur_token;
	t_token	*temp_token;
	t_token	*next;
	char	**values;
	char	**cur_val;

	debug("[split_field] called");
	if (count_fields(token->value) == 1)
		return (token);
	next = token->next;
	values = split_value(token->value);
	cur_val = values;
	free(token->value);
	token->value = *cur_val++;
	cur_token = token;
	while (*cur_val)
	{
		debug("cur_val : %s", *cur_val);
		temp_token = create_empty_token();
		temp_token->type = TK_WORD;
		temp_token->value = *cur_val++;
		cur_token->next = temp_token;
		cur_token = temp_token;
	}
	cur_token->next = next;
	free(values);
	return (token);
}

static char	**split_value(char *value)
{
	char	**values;
	char	**cursor;
	char	*str;
	char	*delim;

	debug("[split_value] called");
	values = (char **) malloc(sizeof(char *) * count_fields(value) + 1);
	cursor = values;
	str = value;
	while (*str)
	{
		delim = find_next_delim(str, is_ifs, C_BACKSLASH | C_SQUOTE | C_DQUOTE);
		if (str != delim)
		{
			*cursor++ = ft_substr(str, 0, delim - str);
			debug("cursor : %s", *(cursor - 1));
			str = delim + 1;
		}
		else
			str = delim;
	}
	*cursor = NULL;
	return (values);
}

static int	count_fields(char *value)
{
	int		count;
	char	*cur;

	debug("[count_fields] called - value : \'%s\'", value);
	count = 0;
	cur = find_next_delim(value, is_ifs, C_BACKSLASH | C_SQUOTE | C_DQUOTE);
	debug("[after find_next_delim called : %s", cur);
	while (*cur)
	{
		debug("[count_fields] count - %d, cur : %s", count, cur);
		count++;
		cur = find_next_delim(cur + 1, is_ifs, C_BACKSLASH | C_SQUOTE | C_DQUOTE);
	}
	count++;
	debug("[count_fields] last_count : %d", count);
	return (count);
}
