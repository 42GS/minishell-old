/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:26:48 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/18 01:46:10 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "def.h"
# include "ast.h"

typedef struct s_cmd_form
{
	char	*cmd;
	char	**args;
	char	**envp;
}	t_cmd_form;

typedef t_status	(*t_builtin)(char **);

typedef struct s_builtin_entry
{
	char			*cmd_str;
	t_builtin		cmd;
}	t_builtin_entry;

/* --- execute_builtin.c --- */

t_status	execute_builtin(t_cmd_form *cmd_form);
t_boolean	is_builtin(char *cmd);

/* --- execute_command.c --- */

t_status	execute_simple_cmd(t_command *cmd);
t_status	set_io_from_prefix(t_syntax_node *prefix);
t_status	set_io_from_suffix(t_syntax_node *suffix);

/* --- execute_command_utils.c --- */

char		**get_args_from_suffix(t_syntax_node *cmd_suffix);

/* --- execute_utils.c --- */

void		release_cmd_form(t_cmd_form *cmd_form);

#endif
