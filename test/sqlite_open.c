#include <stdio.h>

#include "sqlite3.h"

int main(int argc, const char *argv[])
{
	int ret;
	sqlite3 *ppDb ;

	ret = sqlite3_open("./config.db", &ppDb);
	if(ret != SQLITE_OK){
		printf("open config.db failed\n");
		return -1;
	}

	printf("open config.db ok\n");

	sqlite3_close(ppDb);

	return 0;
}