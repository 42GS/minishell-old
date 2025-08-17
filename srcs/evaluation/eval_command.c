/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo <jyoo@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:34:00 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/18 02:46:29 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#include "def.h"

#include "shell_data.h"
#include "execute.h"

#include "eval.h"

#include "debug.h"

/**
 * @brief (파이프 여부에 따라) 명령 노드를 실행한다.
 *
 * - 파이프 내부(get_shell_data()->in_pipe == TRUE)라면 현재 프로세스에서
 *   즉시 하위 노드를 eval/execute_simple_cmd로 실행하고 exit()로 종료한다.
 * - 파이프 외부라면 fork() 후 자식에서 실행하고, 부모는 waitpid()로 대기한다.
 *
 * @param cmd_node 실행할 명령 노드 (NODE_SIMPLE_COMMAND 또는 NODE_COMPOUND_COMMAND)
 * @return t_status waitpid()로 수집한 자식의 상태 값(원시 status)
 *
 * @note
 * - 반환값은 WEXITSTATUS가 아닌 waitpid의 원시 status이다.
 *   호출 측에서 WIFEXITED/WEXITSTATUS로 해석이 필요할 수 있다.
 * - 자식에서는 restore_terminal_settings()를 호출한 뒤 실행한다.
 */
t_status	eval_command(t_syntax_node *cmd_node)
{
	int		status;
	pid_t	pid;

	if ((get_shell_data())->in_pipe)
	{
		if (cmd_node->type == NODE_SIMPLE_COMMAND)
			execute_simple_cmd(&(cmd_node->value.command));
		else
			eval(cmd_node->value.child);
		exit(get_shell_data()->last_status);
	}
	if (cmd_node->type == NODE_SIMPLE_COMMAND
		&& is_builtin(cmd_node->value.command.word))
		return (execute_simple_cmd(&(cmd_node->value.command)));
	pid = fork();
	if (pid == 0)
	{
		if (cmd_node->type == NODE_SIMPLE_COMMAND)
			execute_simple_cmd(&(cmd_node->value.command));
		else
			eval(cmd_node->value.child);
		exit(get_shell_data()->last_status);
	}
	return (wait_child(pid, &status, 0));
}

t_status	wait_child(pid_t child_pid, int *status, int options)
{
	int	sig;
	waitpid(child_pid, status, options);
	if (WIFEXITED(*status))
		(get_shell_data())->last_status = WEXITSTATUS(*status);
	if (WIFSIGNALED(*status))
	{
		sig = WTERMSIG(*status);
		debug("[wait_child] child (%d) killed by signal %d (%s)\n", getpid(), sig, strsignal(sig));
		(get_shell_data())->last_status = 128 + WTERMSIG(*status);
	}
	debug("[wait_child] pid : %d, child_pid : %d", getpid(), child_pid);
	return (*status);
}
