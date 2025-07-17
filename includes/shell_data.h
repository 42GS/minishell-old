/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_data.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:21:55 by yoshin            #+#    #+#             */
/*   Updated: 2025/07/14 17:23:09 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_DATA_H
# define SHELL_DATA_H

typedef struct s_shell_data
{
	char	**envp;         // 환경 변수 복사본
	int		last_exit_code; // $? 값
	t_list	*env_list;      // 환경 변수를 리스트로 관리 (export, unset 용이)
    // 여기에 현재 작업 디렉토리, 히스토리 파일 경로 등 추가 가능
	char	*cur_working_dir;
	char	*history_file;
} t_shell_data;

#endif
