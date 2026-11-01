#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include "info.h"

#define BOLD  "\033[1m"
#define RESET "\033[0m"

/* PRETTY_NAME from /etc/os-release */
static void get_os_name(char *out, size_t size) {
    snprintf(out, size, "Linux");
    FILE *f = fopen("/etc/os-release", "r");
    if (!f) return;

    char line[256];
    while (fgets(line, sizeof line, f)) {
        if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
            char *v = line + 12;
            v[strcspn(v, "\n")] = '\0';
            size_t len = strlen(v);
            if (len >= 2 && v[0] == '"' && v[len - 1] == '"') {
                v[len - 1] = '\0';
                v++;
            }
            snprintf(out, size, "%.90s", v);
            break;
        }
    }
    fclose(f);
}

/* First "model name" line of /proc/cpuinfo */
static void get_cpu_name(char *out, size_t size) {
    snprintf(out, size, "unknown");
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (!f) return;

    char line[256];
    while (fgets(line, sizeof line, f)) {
        if (strncmp(line, "model name", 10) == 0) {
            char *colon = strchr(line, ':');
            if (!colon) break;
            colon += 2;                       /* skip ": " */
            colon[strcspn(colon, "\n")] = '\0';
            snprintf(out, size, "%.90s", colon);
            break;
        }
    }
    fclose(f);
}

/* MemTotal and MemAvailable, in kB */
static void get_ram(double *used_gib, double *total_gib) {
    long total = 0, avail = 0;
    *used_gib = *total_gib = 0;
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) return;

    char line[128];
    while (fgets(line, sizeof line, f)) {
        sscanf(line, "MemTotal: %ld kB", &total);
        sscanf(line, "MemAvailable: %ld kB", &avail);
    }
    fclose(f);

    *total_gib = total / 1048576.0;
    *used_gib  = (total - avail) / 1048576.0;
}

/* Used and total size of the root filesystem, in GiB */
static void get_disk(double *used_gib, double *total_gib) {
    struct statvfs s;
    *used_gib = *total_gib = 0;
    if (statvfs("/", &s) != 0) return;

    double bs = (double)s.f_frsize;
    *total_gib = s.f_blocks * bs / 1073741824.0;
    *used_gib  = (s.f_blocks - s.f_bfree) * bs / 1073741824.0;
}

/* Read a hex value like "0x10de" from a sysfs file */
static int read_hex(const char *path, unsigned *out) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    char buf[32];
    int ok = fgets(buf, sizeof buf, f) != NULL;
    fclose(f);
    if (!ok) return -1;
    *out = (unsigned)strtoul(buf, NULL, 16);   /* handles the 0x prefix */
    return 0;
}

/* Look up vendor and device names in pci.ids. Returns 0 if vendor found */
static int lookup_pci(unsigned vendor, unsigned device,
                      char *vname, size_t vsize, char *dname, size_t dsize) {
    const char *paths[] = {
        "/usr/share/hwdata/pci.ids",   /* Fedora, Arch */
        "/usr/share/misc/pci.ids",     /* Debian, Ubuntu */
        "/usr/share/pci.ids",
    };
    FILE *f = NULL;
    for (size_t i = 0; i < 3 && !f; i++)
        f = fopen(paths[i], "r");
    if (!f) return -1;

    char vkey[8], dkey[8], line[256];
    snprintf(vkey, sizeof vkey, "%04x", vendor);
    snprintf(dkey, sizeof dkey, "%04x", device);
    vname[0] = dname[0] = '\0';

    int in_vendor = 0;
    while (fgets(line, sizeof line, f)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        line[strcspn(line, "\n")] = '\0';

        if (line[0] != '\t') {                 /* vendor (or class) line */
            if (in_vendor) break;              /* we passed our vendor */
            if (strncmp(line, vkey, 4) == 0 && line[4] == ' ') {
                const char *p = line + 4;
                while (*p == ' ') p++;
                snprintf(vname, vsize, "%.100s", p);
                in_vendor = 1;
            }
        } else if (in_vendor && line[1] != '\t') {   /* device line */
            if (strncmp(line + 1, dkey, 4) == 0) {
                const char *p = line + 5;
                while (*p == ' ') p++;
                snprintf(dname, dsize, "%.100s", p);
                break;
            }
        }
    }
    fclose(f);
    return vname[0] ? 0 : -1;
}

/* Fill out with one string per GPU, return how many */
static int get_gpus(char out[][96], int max) {
    int n = 0;
    for (int i = 0; i < 8 && n < max; i++) {
        char path[96];
        unsigned cls, vendor, device;

        snprintf(path, sizeof path, "/sys/class/drm/card%d/device/class", i);
        if (read_hex(path, &cls) != 0) continue;
        if ((cls >> 16) != 0x03) continue;       /* 0x03 = display controller */

        snprintf(path, sizeof path, "/sys/class/drm/card%d/device/vendor", i);
        if (read_hex(path, &vendor) != 0) continue;
        snprintf(path, sizeof path, "/sys/class/drm/card%d/device/device", i);
        if (read_hex(path, &device) != 0) continue;

        char vname[128], dname[128];
        if (lookup_pci(vendor, device, vname, sizeof vname,
                       dname, sizeof dname) != 0) {
            snprintf(out[n++], 96, "%04x:%04x", vendor, device);
            continue;
        }

        const char *vshort = vname;
        if (vendor == 0x10de) vshort = "NVIDIA";
        else if (vendor == 0x1002) vshort = "AMD";
        else if (vendor == 0x8086) vshort = "Intel";

        /* "GA106 [GeForce RTX 3060]" -> "GeForce RTX 3060" */
        char *name = dname;
        char *lb = strchr(dname, '[');
        char *rb = lb ? strchr(lb, ']') : NULL;
        if (lb && rb) { *rb = '\0'; name = lb + 1; }

        snprintf(out[n++], 96, "%.20s %.60s", vshort, name);
    }
    return n;
}

int get_sysinfo(char lines[][INFO_LEN], int max) {
    int n = 0;
    char buf[96];

    if (n < max) {
        get_os_name(buf, sizeof buf);
        snprintf(lines[n++], INFO_LEN, BOLD "OS" RESET "     %.90s", buf);
    }

    struct utsname u;
    if (n < max && uname(&u) == 0)
        snprintf(lines[n++], INFO_LEN, BOLD "Kernel" RESET " %.90s", u.release);

    struct sysinfo si;
    if (n < max && sysinfo(&si) == 0) {
        long up = si.uptime;
        snprintf(lines[n++], INFO_LEN, BOLD "Uptime" RESET " %ldd %ldh %ldm",
                 up / 86400, (up % 86400) / 3600, (up % 3600) / 60);
    }

    if (n < max) {
        const char *sh = getenv("SHELL");
        snprintf(lines[n++], INFO_LEN, BOLD "Shell" RESET "  %.90s", sh ? sh : "unknown");
    }

    if (n < max) {
        get_cpu_name(buf, sizeof buf);
        snprintf(lines[n++], INFO_LEN, BOLD "CPU" RESET "    %.90s", buf);
    }

    char gpus[3][96];
    int ng = get_gpus(gpus, 3);
    for (int i = 0; i < ng && n < max; i++)
        snprintf(lines[n++], INFO_LEN, BOLD "GPU" RESET "    %.90s", gpus[i]);

    if (n < max) {
        double used, total;
        get_ram(&used, &total);
        snprintf(lines[n++], INFO_LEN, BOLD "RAM" RESET "    %.1f / %.1f GiB", used, total);
    }

    if (n < max) {
        double used, total;
        get_disk(&used, &total);
        snprintf(lines[n++], INFO_LEN, BOLD "Disk" RESET "   %.1f / %.1f GiB", used, total);
    }

    return n;
}
