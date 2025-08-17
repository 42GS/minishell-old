/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:25:06 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/18 01:50:15 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

#include "def.h"

#include "utils.h"
#include "shell_data.h"
#include "eval.h"
#include "sig.h"

#include "execute.h"

static t_status	execute_absolute_path(t_cmd_form *cmd_form);
static t_status	execute_cmd(t_cmd_form *cmd_form);

/**
 * @brief 단일(simple) 명령을 구성하고 실행한다.
 *
 * suffix에서 인자 벡터를 확보하고, word를 argv[0]로 설정한다.
 * prefix/suffix의 I/O 리다이렉션을 적용한 뒤, 빌트인 실행을 우선 시도하고
 * 실패 시 외부 프로그램 실행을 시도한다.
 *
 * @param cmd 파싱된 단일 명령 정보(선행 prefix/후행 suffix 포함)
 * @return t_status SUCCESS(0) 또는 ERROR(비0)
 *
 * @note
 * - execute_builtin()이 성공하면 외부 실행은 시도하지 않는다.
 * - 외부 실행은 execute_cmd()에서 처리하며, 해당 함수는 성공 시 execve로 교체되어
 *   복귀하지 않고, 실패 시 에러 메시지 출력 후 exit(EXIT_FAILURE)로 종료한다.
 * - eval_prefix_io()/eval_suffix_io() 중 하나라도 ERROR를 반환하면 ERROR를 즉시 반환한다.
 */
t_status	execute_simple_cmd(t_command *cmd)
{
	t_cmd_form	cmd_form;

	cmd_form.cmd = NULL;
	cmd_form.args = NULL;
	cmd_form.envp = NULL;
	cmd_form.args = get_args_from_suffix(cmd->suffix);
	cmd_form.cmd = ft_strdup(cmd->word);
	(cmd_form.args)[0] = ft_strdup((char *)(cmd->word));
	cmd_form.envp = lst_from_hashmap(&(get_shell_data()->envp_map));
	if (set_io_from_prefix(cmd->prefix) == ERROR
		|| set_io_from_suffix(cmd->suffix) == ERROR)
	{
		release_cmd_form(&cmd_form);
		return (ERROR);
	}
	if (execute_builtin(&cmd_form) == FAILURE)
		execute_cmd(&cmd_form);
	release_cmd_form(&cmd_form);
	return (SUCCESS);
}

/**
 * @brief 외부 프로그램을 execve로 실행한다(성공 시 반환하지 않음).
 *
 * - cmd_form.cmd가 실행 가능(X_OK)이면 해당 경로로 execve().
 * - 아니면 PATH 탐색(find_path)로 실행 경로를 찾아 execve().
 * - 모든 경로가 실패하면 "command not found"를 stderr로 출력하고
 *   표준입출력을 닫은 뒤 exit(EXIT_FAILURE).
 *
 * @param cmd_form 실행할 명령의 경로/인자/환경(소유권은 호출자에게 있음)
 * @return t_status 이 함수는 정상 경로에서 반환하지 않으며, 실패 시 exit()한다.
 *
 * @note
 * - 성공 시 프로세스 이미지가 교체되어 제어가 돌아오지 않는다.
 * - 실패 루트에서만 오류 메시지 출력 후 프로세스를 종료한다.
 * - argv[0]은 실제 실행 경로로 갱신된다.
 */
static t_status	execute_cmd(t_cmd_form *cmd_form)
{
	char		*cmd;

	cmd = cmd_form->cmd;
	if (*cmd == '.' && *(cmd + 1) == '/')
	{
		if (access(cmd, R_OK) != 0)
		{
			perror(cmd);
			exit(COMMAND_NOT_FOUND_CODE);
		}
		if (access(cmd, X_OK) != 0)
		{
			perror(cmd);
			exit(PERMISSION_DENIED_CODE);
		}
		restore_signals();
		execve(cmd, cmd_form->args, cmd_form->envp);
	}
	return (execute_absolute_path(cmd_form));
}

static t_status	execute_absolute_path(t_cmd_form *cmd_form)
{
	char	*path;

	path = find_path(cmd_form->cmd, cmd_form->envp);
	if (path)
	{
		free(cmd_form->cmd);
		cmd_form->cmd = (char *)path;
		free(cmd_form->args[0]);
		cmd_form->args[0] = (char *)path;
		restore_signals();
		execve(path, cmd_form->args, cmd_form->envp);
	}
	exit(COMMAND_NOT_FOUND_CODE);
}

/**
 * @brief 명령 앞(prefix)에 붙은 I/O 리다이렉션 체인을 적용한다.
 *
 * NODE_CMD_PREFIX로 연결된 이진 트리를 좌측부터 순회하며
 * 각 노드의 I/O 리다이렉션을 eval_io_redir()로 적용한다.
 *
 * @param prefix 명령의 prefix 노드(또는 단일 I/O 노드)
 * @return t_status SUCCESS(0) 또는 ERROR(비0)
 *
 * @note
 * - prefix가 체인이면 left를 먼저 적용하고 right로 진행한다.
 * - 어느 한 단계라도 오류가 발생하면 즉시 해당 status를 반환한다.
 */
t_status	set_io_from_prefix(t_syntax_node *prefix)
{
	t_syntax_node	*cur_node;
	t_status		status;

	cur_node = prefix;
	while (cur_node && cur_node->type == NODE_CMD_PREFIX)
	{
		status = eval_io_redir(cur_node->value.b_node.left);
		if (status)
			return (status);
		cur_node = cur_node->value.b_node.right;
	}
	status = eval_io_redir(cur_node);
	return (status);
}

/**
 * @brief 명령 뒤(suffix)에 붙은 I/O 리다이렉션/인자 체인을 적용한다.
 *
 * NODE_CMD_SUFFIX로 연결된 이진 트리를 좌측부터 순회하며
 * 각 노드의 I/O 리다이렉션을 eval_io_redir()로 적용한다.
 * (인자 수집은 별도 경로에서 수행되며, 여기서는 I/O만 처리한다고 가정)
 *
 * @param suffix 명령의 suffix 노드(또는 단일 I/O 노드)
 * @return t_status SUCCESS(0) 또는 ERROR(비0)
 *
 * @note
 * - suffix가 체인이면 left를 먼저 적용하고 right로 진행한다.
 * - 어느 한 단계라도 오류가 발생하면 즉시 해당 status를 반환한다.
 */
t_status	set_io_from_suffix(t_syntax_node *suffix)
{
	t_syntax_node	*cur_node;
	t_status		status;

	cur_node = suffix;
	while (cur_node && cur_node->type == NODE_CMD_SUFFIX)
	{
		status = eval_io_redir(cur_node->value.b_node.left);
		if (status)
			return (status);
		cur_node = cur_node->value.b_node.right;
	}
	status = eval_io_redir(cur_node);
	return (status);
}
