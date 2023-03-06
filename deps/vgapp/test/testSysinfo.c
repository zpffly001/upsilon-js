#include <stdio.h>
#include "sysinfo.h"

// gcc -o testSysinfo testSysinfo.c -I ../ ../sysinfo.c

int main()
{

    vbar_sysinfo_get_uptime();

    vbar_sysinfo_get_totaldisk("/usr/local");

    char buf[16];
    vbar_sysinfo_get_uuid(buf, 16);

    vbar_sysinfo_get_freecpu();
    return 1;
}