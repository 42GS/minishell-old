/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 21:22:27 by yoshin            #+#    #+#             */
/*   Updated: 2025/07/16 21:55:06 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "def.h"
#include "tokenizer.h"

t_token	*create_token_lst(void)
{
	t_token	*token_lst;

	token_lst = (t_token *) malloc(sizeof(t_token));
	if (errno == ENOMEM)
	{
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (token_lst);
}

t_status	delete_token_lst(t_token **lst)
{

}

t_status	insert_token_to_lst(t_token *lst, t_token *token)
{
}

t_status	remove_token_from_lst(t_token *lst, t_token *target)
{
	t_token	*cur;

	cur = lst;
	while (cur)
	{
		if (cur == target)
			cur = cur->next;
		else

	}
	return (SUCCESS);
}
