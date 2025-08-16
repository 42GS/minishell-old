/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyoo < jyoo@student.42gyeongsan.kr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 23:46:41 by yoshin            #+#    #+#             */
/*   Updated: 2025/08/16 14:32:22 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

#include "def.h"
#include "utils.h"

static void			fill_dp(
						t_boolean **dp,
						int idxes[2],
						const char *s,
						const char *p);
static t_boolean	**create_dp_arr(int n, int m);
static t_boolean	set_return(t_boolean **dp, int i, int j);

/**
 * @brief 와일드카드 패턴과 문자열이 일치하는지 검사한다.
 *
 * '*' 는 0개 이상의 임의 문자와 매칭되고,
 * '?' 는 정확히 1개의 임의 문자와 매칭된다.
 *
 * @param s 검사 대상 문자열
 * @param p 와일드카드 패턴 문자열
 * @return TRUE(일치), FALSE(불일치)
 *
 * @note
 * - DP 테이블 dp[i][j]는 s의 처음 i글자와 p의 처음 j글자가 일치하는지 여부를 저장한다.
 * - 초기화:
 *   - dp[0][0] = TRUE (빈 문자열과 빈 패턴은 매칭됨)
 *   - p의 시작 부분이 '*'일 경우, 이전 값(dp[0][j-1])을 이어받아 dp[0][j] 설정
 * - 점화식:
 *   - p[j-1] == '*' → dp[i][j] = dp[i][j-1] || dp[i-1][j]
 *     (패턴의 '*'가 0글자를 소비하거나, 문자열의 한 글자를 소비한 경우)
 *   - p[j-1] == '?' 또는 p[j-1] == s[i-1] → dp[i][j] = dp[i-1][j-1]
 *   - 그 외 → dp[i][j] = FALSE
 *
 * @warning
 * - create_dp_arr()에서 malloc으로 할당된 2차원 배열은 호출자가 직접 free해야 함.
 * - 현재 구현에서는 free를 하지 않고 반환하므로, match_files_in_dir() 등 사용 후 반드시 해제 필요.
 *
 * @example
 * wildcard_match("hello.c", "*.c");      // TRUE
 * wildcard_match("main.c", "m?in.*");    // TRUE
 * wildcard_match("test.txt", "*.cpp");   // FALSE
 */
t_boolean	wildcard_match(const char *s, const char *p)
{
	int			slen;
	int			plen;
	t_boolean	**dp;
	int			idxes[2];

	slen = ft_strlen(s);
	plen = ft_strlen(p);
	dp = create_dp_arr(slen, plen);
	dp[0][0] = TRUE;
	idxes[P_IDX] = 0;
	while (++idxes[P_IDX] <= plen)
		if (p[idxes[P_IDX] - 1] == '*')
			dp[0][idxes[P_IDX]] = dp[0][idxes[P_IDX] - 1];
	idxes[S_IDX] = 0;
	while (++idxes[S_IDX] <= slen)
	{
		idxes[P_IDX] = 0;
		while (++idxes[P_IDX] <= plen)
			fill_dp(dp, idxes, s, p);
	}
	return (set_return(dp, slen, plen));
}

/**
 * @brief DP 테이블을 채우는 서브 함수
 * @param dp    DP 테이블
 * @param idxes [s_idx, p_idx] 인덱스 쌍
 * @param s     검사할 문자열
 * @param p     패턴 문자열
 */
static void	fill_dp(
				t_boolean **dp,
				int idxes[2],
				const char *s,
				const char *p)
{
	int	s_idx;
	int	p_idx;

	s_idx = idxes[S_IDX];
	p_idx = idxes[P_IDX];
	if (p[p_idx - 1] == '*')
		dp[s_idx][p_idx] = (dp[s_idx][p_idx - 1] || dp[s_idx - 1][p_idx]);
	else if (p[p_idx - 1] == '?' || p[p_idx - 1] == s[s_idx - 1])
		dp[s_idx][p_idx] = dp[s_idx -1][p_idx -1];
	else
		dp[s_idx][p_idx] = FALSE;
}

/**
 * @brief n+1 × m+1 크기의 DP 배열을 FALSE로 초기화하여 생성
 */
static t_boolean	**create_dp_arr(int n, int m)
{
	t_boolean	**dp;
	int			r;
	int			c;

	dp = (t_boolean **) malloc(sizeof(t_boolean *) * (n + 1));
	r = -1;
	while (++r <= n)
	{
		dp[r] = (t_boolean *) malloc(sizeof(t_boolean) * (m + 1));
		c = -1;
		while (++c <= m)
			dp[r][c] = FALSE;
	}
	return (dp);
}

static t_boolean	set_return(t_boolean **dp, int i, int j)
{
	t_boolean	return_value;
	int			r;

	return_value = dp[i][j];
	r = -1;
	while (++r <= i)
		free(dp[r]);
	free(dp);
	return (return_value);
}
