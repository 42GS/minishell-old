/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 12:27:10 by yoshin            #+#    #+#             */
/*   Updated: 2025/07/16 21:50:32 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

#include "tokenizer.h"

static t_status	is_delim(char *cur);
static char		*find_next_delim(char *cur);

t_token	*tokenize_input(char *line)
{
	t_token	*token_lst;
	t_token	*new_token;
	char	*cursor;

	token_lst = create_token_lst();
	cursor = line;
	while (*cursor)
	{
		new_token = create_token(cursor);
		if (!new_token)
			cursor++;
		else
		{
			insert_token_to_lst(token_lst, new_token);
			if (new_token->type == TK_WORD_WITH_SQUOTE
				|| new_token->type == TK_WORD_WITH_DQUOTE)
				cursor += (ft_strlen(new_token->value) + 2);
			else
				cursor += (ft_strlen(new_token->value));
		}
	}
	return (token_lst);
}
