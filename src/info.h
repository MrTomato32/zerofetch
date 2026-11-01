#ifndef INFO_H
#define INFO_H

#define INFO_LINES 12
#define INFO_LEN   128

/* Fill lines with "Label: value" strings, return how many */
int get_sysinfo(char lines[][INFO_LEN], int max);

#endif
