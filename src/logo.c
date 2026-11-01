#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "logo.h"
#define LOGO_WIDTH 52

// Tavolozze colori ufficiali (ANSI escape codes)
static const char* FEDORA_COLORS[] = { "\033[38;2;60;110;180m", "\033[1;37m", NULL };
static const char* LINUX_COLORS[]   = { "\033[1;33m", "\033[1;37m", NULL };

typedef struct {
    const char *id;
    const char **default_colors;
    const char *lines[64]; // RISOLTO: Array esplicito di puntatori a stringa. Niente più SIGSEGV.
} RealEquivalentLogo;

// IL VERO LOGO GEOMETRICO UFFICIALE DI CACHYOS


static const RealEquivalentLogo fedora_logo = {
    .id = "fedora",
    .default_colors = FEDORA_COLORS,
    .lines = {
        "${1}                                                  \033[0m",
        "${1}                  ____yyyyyy____                  \033[0m",
        "${1}              _ag@@@@@@@@@@@@@@@@gy_              \033[0m",
        "${1}           _g@@@@@@@@@@@@@@@@@@@@@@@@g_           \033[0m",
        "${1}         a@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@g         \033[0m",
        "${1}       y@@@@@@@@@@@@@@@@@@@PFF?4@@@@@@@@@@y       \033[0m",
        "${1}      g@@@@@@@@@@@@@@@@@F`       `~@@@@@@@@$      \033[0m",
        "${1}     $@@@@@@@@@@@@@@@@@    _gggy    9@@@@@@@@     \033[0m",
        "${1}    g@@@@@@@@@@@@@@@@@[   a@@@@@$    @@@@@@@@$    \033[0m",
        "${1}    @@@@@@@@@@@@@@@@@@[   $@@@@@@_ _a@@@@@@@@@L   \033[0m",
        "${1}   a@@@@@@@@@@@@@@@@@@[   $@@@@@@@@@@@@@@@@@@@$   \033[0m",
        "${1}   $@@@@@@@@@@P~~~~~~@[   \"~~~~@@@@@@@@@@@@@@@@   \033[0m",
        "${1}   $@@@@@@@@~        @[       _$@@@@@@@@@@@@@@$   \033[0m",
        "${1}   $@@@@@@F   _a@@@@@@[   $@@@@@@@@@@@@@@@@@@@F   \033[0m",
        "${1}   $@@@@@@    @@@@@@@@[   $@@@@@@@@@@@@@@@@@@@    \033[0m",
        "${1}   $@@@@@@    @@@@@@@@    $@@@@@@@@@@@@@@@@@@     \033[0m",
        "${1}   $@@@@@@L   `4@@@@P~   y@@@@@@@@@@@@@@@@@@      \033[0m",
        "${1}   $@@@@@@@$_          _a@@@@@@@@@@@@@@@@@F       \033[0m",
        "${1}   $@@@@@@@@@@gy____yg@@@@@@@@@@@@@@@@@@F`        \033[0m",
        "${1}   $@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P~           \033[0m",
        "${1}   `@@@@@@@@@@@@@@@@@@@@@@@@@@@@@PF~              \033[0m",
        "${1}     ~~~~~~~~~~~~~~~~~~~~~~~~~~`                  \033[0m",
        "${1}                                                  \033[0m",
        NULL
    }
};

static const RealEquivalentLogo fallback_logo = {
    .id = "linux",
    .default_colors = LINUX_COLORS,
    .lines = {
        "        ${1} _     _  ",
        "        ${1}(o)___(o) ",
        "        ${1} /     \\  ",
        "        ${1}|  _ _  | ",
        "        ${1} \\_(_)_/  ",
        NULL
    }
};

static const char* cachyos_COLORS[] = { "\033[38;2;0;168;135m", NULL };
static const RealEquivalentLogo cachyos_logo = {
    .id = "cachyos",
    .default_colors = cachyos_COLORS,
    .lines = {
        "${1}                                                  \033[0m",
        "${1}                                                  \033[0m",
        "${1}          ygggggggggggggggggggggggg               \033[0m",
        "${1}         y@@@@@@@@@@@@@@@@@@@@@@@@~      __       \033[0m",
        "${1}        g@@@@@@@@@@@@@@@@@@@@@@@@~      a@@W      \033[0m",
        "${1}       a@@@@@@@@@@@@@@@@@@@@@@@F        `~~       \033[0m",
        "${1}     y@@@@@@@@@@@@@@@@@@@@@@@@F                   \033[0m",
        "${1}    y@@@@@@@@@@@F~~~~~~~~~~~~`                    \033[0m",
        "${1}   g@@@@@@@@@@@~                   a@@@$_         \033[0m",
        "${1}  g@@@@@@@@@@@^                   4@@@@@$         \033[0m",
        "${1}y@@@@@@@@@@@F                      7R@RF~         \033[0m",
        "${1}4@@@@@@@@@@@,                               ____  \033[0m",
        "${1} 7@@@@@@@@@@@_                            yg@@@@@y\033[0m",
        "${1}  ~@@@@@@@@@@@y                           @@@@@@@@\033[0m",
        "${1}    @@@@@@@@@@@g                          4@@@@@@F\033[0m",
        "${1}     4@@@@@@@@@@$yyyyyyyyyyyyyyyyyyyyyyyy+ `~FF~` \033[0m",
        "${1}      7@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F         \033[0m",
        "${1}       `@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@~          \033[0m",
        "${1}         @@@@@@@@@@@@@@@@@@@@@@@@@@@@@^           \033[0m",
        "${1}          4@@@@@@@@@@@@@@@@@@@@@@@@@F             \033[0m",
        "${1}           ~~~~~~~~~~~~~~~~~~~~~~~~~              \033[0m",
        "${1}                                                  \033[0m",
        "${1}                                                  \033[0m",
        NULL
    }
};
static const char* arch_COLORS[] = { "\033[38;2;23;147;209m", NULL };
static const RealEquivalentLogo arch_logo = {
    .id = "arch",
    .default_colors = arch_COLORS,
    .lines = {
        "${1}                        gy                        \033[0m",
        "${1}                       y@@y                       \033[0m",
        "${1}                      y@@@@y                      \033[0m",
        "${1}                     _@@@@@@y                     \033[0m",
        "${1}                    _$@@@@@@@_                    \033[0m",
        "${1}                   _$@@@@@@@@@_                   \033[0m",
        "${1}                   0@@@@@@@@@@@y                  \033[0m",
        "${1}                 _gy~@@@@@@@@@@@y                 \033[0m",
        "${1}                y@@@@gyB@@@@@@@@@y                \033[0m",
        "${1}               y@@@@@@@@@@@@@@@@@@y               \033[0m",
        "${1}              y@@@@@@@@@@@@@@@@@@@@g              \033[0m",
        "${1}             y@@@@@@@@@@@@@@@@@@@@@@@             \033[0m",
        "${1}            g@@@@@@@@@@@@@@@@@@@@@@@@$            \033[0m",
        "${1}           a@@@@@@@@@@@PFFF@@@@@@@@@@@$_          \033[0m",
        "${1}          g@@@@@@@@@@F      ~@@@@@@@@@@@_         \033[0m",
        "${1}        y$@@@@@@@@@@~        \"@@@@@@@@@@@y        \033[0m",
        "${1}       y@@@@@@@@@@@$          4@@@@@@@@@@@y       \033[0m",
        "${1}      y@@@@@@@@@@@@$          4@@@@@@@@$y~FK      \033[0m",
        "${1}     g@@@@@@@@@@@@@$          d@@@@@@@@@@@@y_     \033[0m",
        "${1}    a@@@@@@@@@@PF~~`          `~~FP@@@@@@@@@@g_   \033[0m",
        "${1}  _@@@@@@@F~~                        `~5R@@@@@@_  \033[0m",
        "${1} y@@@P~~                                  ~~A@@@y \033[0m",
        "${1}zP~`                                          `~AL\033[0m",
        NULL
    }
};

static void real_fetch_print_line(const char *line, const char **colors,
                                  const char *info) {
    int width = 0;                        /* visible columns printed */

    while (*line) {
        if (*line == '$' && *(line + 1) == '{') {
            char num_char = *(line + 2);
            if (isdigit((unsigned char)num_char) && *(line + 3) == '}') {
                int color_index = num_char - '1';
                if (color_index >= 0 && color_index < 2 && colors[color_index] != NULL)
                    printf("%s", colors[color_index]);
                line += 4;
                continue;
            }
        }
        if (*line == '\033') {
            while (*line && *line != 'm') {
                putchar(*line);
                line++;
            }
            if (*line) {
                putchar(*line);
                line++;
            }
            continue;
        }
        /* count only the first byte of each UTF-8 character */
        if (((unsigned char)*line & 0xC0) != 0x80)
            width++;
        putchar(*line);
        line++;
    }

    printf("\033[0m");
    for (; width < LOGO_WIDTH; width++)   /* pad up to the info column */
        putchar(' ');
    printf("%s\n", info);
}

static void parse_and_get_os_id(char *output, size_t max_size) {
    snprintf(output, max_size, "linux");
    FILE *f = fopen("/etc/os-release", "r");
    if (!f) return;

    char line_buffer[256];
    while (fgets(line_buffer, sizeof(line_buffer), f)) {
        if (strncmp(line_buffer, "ID=", 3) == 0) {
            char *start = line_buffer + 3;
            if (*start == '"' || *start == '\'') start++;

            size_t len = 0;
            while (start[len] && start[len] != '"' && start[len] != '\'' &&
                   start[len] != '\n' && start[len] != '\r' && start[len] != ' ') {
                len++;
            }

            if (len > 0 && len < max_size) {
                for (size_t i = 0; i < len; i++) {
                    output[i] = (char)tolower((unsigned char)start[i]);
                }
                output[len] = '\0';
            }
            break;
        }
    }
    fclose(f);
}



static const char* UBUNTU_COLORS[]  = { "\033[38;5;202m", "\033[38;5;202m", NULL };
static const RealEquivalentLogo ubuntu_logo = {
    .id = "ubuntu",
    .default_colors = UBUNTU_COLORS,
    .lines = {
        "                                                             \033[0m",
        "                                                             \033[0m",
        "                                                             \033[0m",
        "                                                             \033[0m",
        "                                    _g$@$gy                  \033[0m",
        "                        __yyyyyyyy, @@@@@@@w                 \033[0m",
        "                    , a@@@@@@@@@@@@ @@@@@@@F                 \033[0m",
        "                 _g@@y 4@@@@@@@@@@@$yTPRPF\"                  \033[0m",
        "               _a@@@@@g ~PFTT~~TT5R@@@@$$@@$_                \033[0m",
        "              y@@@@@@@F             ~F@@@@@@@y               \033[0m",
        "             y@@@@@@F                  3@@@@@@y              \033[0m",
        "         _y_,4@@@@@~                    ~@@@@@@            ' \033[0m",
        "       g@@@@@$ 5@@$                      9@@@@@L             \033[0m",
        "       @@@@@@@K @@F                      ```````             \033[0m",
        "       5@@@@@P g@@$                      g@@@@@F             \033[0m",
        "         ~~~`g@@@@@y                    y@@@@@@              \033[0m",
        "             ~@@@@@@g                  g@@@@@@~              \033[0m",
        "              ~@@@@@@@g             _g@@@@@@@~               \033[0m",
        "               `5@@@@@F yggyyyyyygg@@@@RR@@P~                \033[0m",
        "                 `F@@~ g@@@@@@@@@@@@~ygggy_                  \033[0m",
        "                    ` 4@@@@@@@@@@@$ $@@@@@@L                 \033[0m",
        "                        `~~TTFFTT~~ @@@@@@@F                 \033[0m",
        "                                    `FR@RP~                  \033[0m",
        "                                                             \033[0m",
        "                                                             \033[0m",
        "                                                             \033[0m",
        "                                                             \033[0m",
        NULL
    }
};
static const char* DEBIAN_COLORS[]  = { "\033[38;5;196m", "\033[38;5;196m", NULL };
static const RealEquivalentLogo debian_logo = {
    .id = "debian",
    .default_colors = DEBIAN_COLORS,
    .lines = {
        "                                                 \033[0m",
        "                ..::::::::::::::..               \033[0m",
        "             .::::::::::::::::::::::::..         \033[0m",
        "          .::::::::```````````````::::::::.      \033[0m",
        "        :::::::```                 ``:::::::.    \033[0m",
        "      .:::::``                        `:::::::   \033[0m",
        "     .:::``                             `:::``:  \033[0m",
        "    :::``                 ....           `:::.`  \033[0m",
        "   ::::               .: ``````           :::`   \033[0m",
        "  :::`               :`                   ::::   \033[0m",
        "  :::               :`                    `:::   \033[0m",
        "  :::              :`                     `::`   \033[0m",
        "  ::`              ::                     :::    \033[0m",
        "  ::               `:                    :::     \033[0m",
        "  :::               `:.                .::`      \033[0m",
        "  :::                ``:.            .::`        \033[0m",
        "  `::.                 ```::.....:::```          \033[0m",
        "   :::..                `' ```````               \033[0m",
        "   `::::                                         \033[0m",
        "    `::::                                        \033[0m",
        "      `:::                                       \033[0m",
        "       `:::.                                     \033[0m",
        "         `:::.                                   \033[0m",
        "           ``::.                                 \033[0m",
        "             ```:..                              \033[0m",
        "                ````:.                           \033[0m",
        "                      ``                         \033[0m",
        NULL
    }
};

/* UNDER HERE NO LOGOS*/

static const RealEquivalentLogo *all_logos[] = { 
    &fedora_logo, &arch_logo, &cachyos_logo, &ubuntu_logo, &debian_logo
};

void list_logos(void) {
    for (size_t i = 0; i < sizeof(all_logos) / sizeof(all_logos[0]); i++)
        puts(all_logos[i]->id);
}

void get_logo(char info[][INFO_LEN], int n, const char *forced) {
    char current_id[64];
    if (forced) snprintf(current_id, sizeof current_id, "%s", forced);
    else parse_and_get_os_id(current_id, sizeof(current_id));

    const RealEquivalentLogo *selected = &fallback_logo;
    size_t total = sizeof(all_logos) / sizeof(all_logos[0]);

    for (size_t i = 0; i < total; i++) {
        if (strcmp(all_logos[i]->id, current_id) == 0) {
            selected = all_logos[i];
            break;
        }
    }

    int rows = 0;
    while (rows < 64 && selected->lines[rows] != NULL)
        rows++;

    int height = rows > n ? rows : n;
    int offset = rows > n ? (rows - n) / 2 : 0;   /* center info vertically */

for (int i = 0; i < height; i++) {
        int j = i - offset;
        const char *logo_line = i < rows ? selected->lines[i] : "";
        const char *info_line = (j >= 0 && j < n) ? info[j] : "";
        
    if (selected->default_colors && selected->default_colors[0]) {
        printf("%s", selected->default_colors[0]);
    }

    real_fetch_print_line(logo_line, selected->default_colors, info_line);
    }
}


