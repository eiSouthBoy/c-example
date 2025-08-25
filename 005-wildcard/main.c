/*
 * @Description:
 * @Author: eiSouthBoy
 * @version:
 * @Date: 2025-05-28 20:38:52
 * @LastEditors: eiSouthBoy
 * @LastEditTime: 2025-05-28 20:56:14
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_path_with_regex(const char *pattern, const char *str)
{
	if (!pattern || !str)
	{
		return -1;
	}

	while (*pattern || *str)
	{
		if (*pattern == '+')
		{
			pattern++;
			if (*str == '/' || *str == '\0')
			{
				return 0; // '+' 必须匹配至少一个字符
			}

			// 跳过当前路径段（直到'/'或结尾）
			while (*str != '/' && *str != '\0')
			{
				str++;
			}
			continue;
		}

		if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
		{
			return 0;
		}
	}

	return (*pattern == '\0' && *str == '\0') ? 1 : 0;
}

int match_path_with_wildcard(const char *pattern, const char *str)
{
	/* check input parameters */
	if (pattern == NULL || str == NULL)
	{
		return -1;
	}

	/* If both reach the end, the match is successful */
	if (*pattern == '\0' && *str == '\0')
	{
		return 1;
	}

	/* If only one of them reaches the end, the match fails. */
	if (*pattern == '\0' || *str == '\0')
	{
		return 0;
	}

	/* handle wildcard '+' */
	if (*pattern == '+')
	{
		/* skip wildcard '+' */
		pattern++;

		/* find the last character '/' */
		const char *next_slash_pattern = strchr(pattern, '/');
		const char *next_slash_str = strchr(str, '/');

		/* If the rest of the pattern does not start with '/',
		   the entire rest needs to match */
		if (!next_slash_pattern)
		{
			return (strcmp(pattern, str) == 0);
		}

		size_t rest_pattern = (size_t)(next_slash_pattern - pattern);
		size_t rest_str = (size_t)(next_slash_str - str);
		size_t len_pattern = next_slash_pattern ? rest_pattern : strlen(pattern);
		size_t len_str = next_slash_str ? rest_str : strlen(str);

		/* start at the next '/' character */
		if (len_str > 0)
		{
			str += len_str;
		}
		if (len_pattern > 0)
		{
			pattern += len_pattern;
		}
		return match_path_with_wildcard(pattern, str);
	}

	/* handle other characters */
	if (*pattern == *str)
	{
		return match_path_with_wildcard(pattern + 1, str + 1);
	}

	/* match fails */
	return 0;
}

int main(int argc, const char *argv[])
{
	int rc = 0;
	const char *pattern = "home/+/light1";
	const char *str = "home/bedroom/light1";

	/* solution 1 */
	rc = match_path_with_wildcard(pattern, str);
	if (rc > 0)
	{
		printf("match_path_with_wildcard(): match success\n");
	}
	else
	{
		printf("match_path_with_wildcard(): match failure\n");
	}

	/* solution 2 */
	rc = match_path_with_regex(pattern, str);
	if (rc > 0)
	{
		printf("match_path_with_regex(): match success\n");
	}
	else
	{
		printf("match_path_with_regex(): match failure\n");
	}

	return 0;
}