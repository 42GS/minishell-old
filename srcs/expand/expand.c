/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 20:26:39 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/17 01:35:50 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

#include "flag.h"

#include "tokenizer.h"
#include "expand.h"
#include "utils.h"

#include "debug.h"

static t_token		*ambigous_token(t_token *token, char *value);
static t_boolean	is_ambigous_redirection(t_token *token, char *value);

t_token	*expand_token(t_token *token)
{
	t_token	*new_token;
	char	*tk_value;
	char	*value;
	char	*temp;

	if (!token || token->type != TK_WORD)
		return (token);
	debug("trying to expand value : %s", (char *)token->value);
	tk_value = expand_tilde(token->value);
	debug("expand_tilde completed! - tk_value : %s", tk_value);
	temp = tk_value;
	value = expand_envp(temp);
	debug("expand_envp completed! - value : %s", value);
	free(temp);
	if (is_ambigous_redirection(token, value))
		return (ambigous_token(token, value));
	free(token->value);
	token->value = value;
	debug("trying to split field : %s", (char *)token->value);
	new_token = split_field(token);
	if (token == new_token)
		new_token->value = unquote_value(new_token->value);
	return (new_token);
}

static t_boolean	is_ambigous_redirection(t_token *token, char *value)
{
	char	*delim;

	delim = find_next_delim(
			value,
			is_ifs,
			C_BACKSLASH | C_SQUOTE | C_DQUOTE);
	debug("ambi delim : %s", delim);
	if (is_io_token(token->prev)
		&& *delim != '\0')
	{
		debug("ambigous redirection !!! - %s", value);
		return (TRUE);
	}
	return (FALSE);
}

static t_token	*ambigous_token(t_token *token, char *value)
{
	ft_putstr_fd(token->value, STDERR_FILENO);
	ft_putendl_fd(": ambigous redirect", STDERR_FILENO);
	if (token->prev)
		token->prev->next = NULL;
	free(token->value);
	free(token);
	free(value);
	return (NULL);
}
