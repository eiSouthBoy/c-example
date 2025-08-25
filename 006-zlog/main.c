#include <stdio.h>
#include <unistd.h>
#include "zlog.h"

int main(int argc, char **argv)
{
	int rc;
	zlog_category_t *zc;

	rc = zlog_init("zlog.conf");
	if (rc)
	{
		printf("init failed\n");
		return -1;
	}

	zc = zlog_get_category("my_cat");
	if (!zc)
	{
		printf("get cat fail\n");
		zlog_fini();
		return -2;
	}

	zlog_info(zc, "hello, zlog");
	zlog_debug(zc, "hello, zlog");
	zlog_warn(zc, "hello, zlog");
	zlog_error(zc, "hello, zlog");
	zlog_notice(zc, "hello, zlog");
	zlog_fatal(zc, "hello, zlog");

	zlog_fini();

	return 0;
}
