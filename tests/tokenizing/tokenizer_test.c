/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:25:33 by yoshin            #+#    #+#             */
/*   Updated: 2025/07/16 21:54:17 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

#include "tokenizer.h"

t_status	simple_test1(void)
{
	char	*simple_str = "cmd1 -option1 | cmd2 -option2 | cat < infile | cmd4 > outfile";

	t_token	*tk_lst = tokenize_input(simple_str);
	t_token *cur;
	int		cnt;

	cur = tk_lst;
	cnt = 0;
	while (cur)
	{
		printf("[%02d] Token : %s\n", cnt++, cur->value);
		cur = cur->next;
	}
}

int	main(void)
{
	simple_test1();
}
