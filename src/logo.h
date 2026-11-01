#ifndef LOGO_H
#define LOGO_H

#include "info.h"

/* Print the distro logo with the info lines next to it */
void get_logo(char info[][INFO_LEN], int n, const char *forced);
void list_logos(void);

#endif
