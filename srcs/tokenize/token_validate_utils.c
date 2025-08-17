/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 21:02:50 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/17 20:19:38 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

#include "tokenizer.h"

t_boolean	is_valid_sequence(t_token *token_lst)
{
	if (!token_lst)
		return (FALSE);
	if (token_lst->type == TK_EOF
		|| token_lst->type == TK_AND_IF || token_lst->type == TK_OR_IF
		|| token_lst->type == TK_PIPE || token_lst->type == TK_PIPE_ERR
		|| token_lst->type == TK_AMPERSAND)
		return (FALSE);
	while (token_lst)
	{
		if (is_io_token(token_lst)
			&& (is_op_token(token_lst->next)
				|| is_io_token(token_lst->next)
				|| token_lst->next->type == TK_EOF))
			return (FALSE);
		// if (is_op_token(token_lst)
		// 	&& (is_op_token(token_lst->next)
		// 		|| is_io_token(token_lst->next)
		// 		|| token_lst->next->type == TK_EOF))
		// 	return (FALSE);
		token_lst = token_lst->next;
	}
	return (TRUE);
}

t_boolean	is_io_token(t_token *token)
{
	if (!token)
		return (FALSE);
	return (token->type == TK_REDIR_IN
		|| token->type == TK_REDIR_OUT
		|| token->type == TK_REDIR_APPEND
		|| token->type == TK_REDIR_HEREDOC);
}

t_boolean	is_op_token(t_token *token)
{
	if (!token)
		return (FALSE);
	return (token->type == TK_AND_IF
		|| token->type == TK_OR_IF
		|| token->type == TK_SEMICOLON
		|| token->type == TK_AMPERSAND
		|| token->type == TK_PIPE
		|| token->type == TK_PIPE_ERR
		|| token->type == TK_OR_IF);
}
