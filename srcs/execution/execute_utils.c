/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:04:02 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/18 02:43:31 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "execute.h"

void	release_cmd_form(t_cmd_form *cmd_form)
{
	char	**strs;

	if (cmd_form->cmd)
		free(cmd_form->cmd);
	strs = NULL;
	strs = cmd_form->args;
	if (strs)
	{
		while (*strs)
			free(*strs++);
	}
	free(cmd_form->args);
	cmd_form->args = NULL;
	strs = NULL;
	strs = cmd_form->envp;
	if (strs)
	{
		while (*strs)
			free(*strs++);
	}
	free(cmd_form->envp);
	cmd_form->envp = NULL;
}
