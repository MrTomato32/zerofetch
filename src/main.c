#include <stdio.h>
#include <string.h>
#include "info.h"
#include "logo.h"

int main(int argc, char **argv) {
    const char *forced = NULL;
    if (argc >= 2 && strcmp(argv[1], "-l") == 0) {
        if (argc < 3) { list_logos(); return 0; }
        forced = argv[2];
    }
    char info[INFO_LINES][INFO_LEN];
    int n = get_sysinfo(info, INFO_LINES);
    get_logo(info, n, forced);
    return 0;
}
