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
static const char* linuxmint_COLORS[] = { "\033[38;2;135;207;62m", NULL };
static const RealEquivalentLogo linuxmint_logo = {
    .id = "linuxmint",
    .default_colors = linuxmint_COLORS,
    .lines = {
        "${1}                                                  \033[0m",
        "${1}                     ________                     \033[0m",
        "${1}               _yg$@@@@@@@@@@@@$gy_               \033[0m",
        "${1}            yg@@@@@@@@@@@@@@@@@@@@@@gy,           \033[0m",
        "${1}         _a@@@@@@@@@@@@@@@@@@@@@@@@@@@@g_         \033[0m",
        "${1}        a@@@RRR@@@@@@@@@@@@@@@@@@@@@@@@@@g,       \033[0m",
        "${1}      y@@@@F   $@@@@@@@@PPR@@@@PPPR@@@@@@@@_      \033[0m",
        "${1}     y@@@@@F   $@@@@F`      ``      ~R@@@@@@y     \033[0m",
        "${1}     @@@@@@F   $@@@F   yggy    yggy   4@@@@@@,    \033[0m",
        "${1}    a@@@@@@F   $@@@L   @@@@    @@@@   4@@@@@@$    \033[0m",
        "${1}    @@@@@@@F   $@@@L   @@@@    @@@@   4@@@@@@@    \033[0m",
        "${1}    @@@@@@@F   $@@@L   @@@@    @@@@   4@@@@@@@    \033[0m",
        "${1}    @@@@@@@F   $@@@L   @@@@    @@@@   4@@@@@@@    \033[0m",
        "${1}    @@@@@@@F   $@@@yyyy@@@@yyyy@@@@   4@@@@@@$    \033[0m",
        "${1}    \"@@@@@@$   ?@@@@@@@@@@@@@@@@@@F   g@@@@@@~    \033[0m",
        "${1}     ?@@@@@@y   `~FPPPPPPPPPPPPFF`   y@@@@@@F     \033[0m",
        "${1}      `@@@@@@@y_                  _y$@@@@@@~      \033[0m",
        "${1}        4@@@@@@@@$gggggggggggggg$@@@@@@@@F~       \033[0m",
        "${1}         `5@@@@@@@@@@@@@@@@@@@@@@@@@@@@F`         \033[0m",
        "${1}            ~R@@@@@@@@@@@@@@@@@@@@@@P~            \033[0m",
        "${1}               ~~P@@@@@@@@@@@@@@PF~               \033[0m",
        "${1}                     `~~~~~~`                     \033[0m",
        "${1}                                                  \033[0m",
        NULL
    }
};

static const char* manjaro_COLORS[] = { "\033[38;2;135;207;62m", NULL };
static const RealEquivalentLogo manjaro_logo = {
    .id = "manjaro",
    .default_colors = manjaro_COLORS,
    .lines = {
        "${1}@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@PPPPPPPPPPPPPPPPPP   4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L                    4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@L   @@@@@@@@@@@@@@L  4@@@@@@@@@@@@@@\033[0m",
        NULL
    }
};

static const char* opensuse_COLORS[] = { "\033[38;2;135;207;62m", NULL };
static const RealEquivalentLogo opensuse_logo = {
    .id = "opensuse",
    .default_colors = opensuse_COLORS,
    .lines = {
        "${1}                                                  \033[0m",
        "${1}                  _yyyyggggyyyy_                  \033[0m",
        "${1}             _ya$@@@@@@@@@@@@@@@@@gy_             \033[0m",
        "${1}          _y$@@@@@@@@@@@@@@@@@@@@@@@@@y_          \033[0m",
        "${1}        _a@@@~FPPR@@@@@@@@@@@@@@@@@@@@@@g_        \033[0m",
        "${1}        ~FR@@        `~~~5A@@@@@@@@@@@@@@@g       \033[0m",
        "${1}                             `~~F@@@@@@@@@@@_     \033[0m",
        "${1}                         _yag$$gy_ ~R@@@@@@@@_    \033[0m",
        "${1}                        g@@F~~~~A@$_ ~@@@@@@@@    \033[0m",
        "${1}                       g@F  u$@$w`@@  ^@@@@@@@L   \033[0m",
        "${1}                       $@L   ~T~~ @@   4@@@@@@@   \033[0m",
        "${1}                y_     \"@@y_    yg@F    5@@@@@@   \033[0m",
        "${1}                ~@@gy_   T@@@$@@@P~      @@@@@@   \033[0m",
        "${1}                 ~F@@@@gyy_ ~~~`     _yg@@@@@@F   \033[0m",
        "${1}                     ~~P@@@@@gggggg@@@@F9@@@@@    \033[0m",
        "${1}                          `~~FFFFF~~`  y@@@@@^    \033[0m",
        "${1}                                   _ya@@@@@@^     \033[0m",
        "${1}         _yyyy____       ____yyyg$@@@@@@@@F       \033[0m",
        "${1}        \"5@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@P~        \033[0m",
        "${1}          `~@@@@@@@@@@@@@@@@@@@@@@@@@@F~          \033[0m",
        "${1}             `~F@@@@@@@@@@@@@@@@@@P~`             \033[0m",
        "${1}                  `~~FFFPPFFF~~~                  \033[0m",
        "${1}                                                  \033[0m",
        NULL
    }
};

static const char* popos_COLORS[] = { "\033[38;2;72;185;199m", NULL };
static const RealEquivalentLogo popos_logo = {
    .id = "popos",
    .default_colors = popos_COLORS,
    .lines = {
        "${1}               _yyg$@@@@@@@@@@$gyy_               \033[0m",
        "${1}           _yg@@@@@@@@@@@@@@@@@@@@@@$y_           \033[0m",
        "${1}        _a@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@g_        \033[0m",
        "${1}      yg@@@@@@P~~`     `~@@@@@@@@@@@@@@@@@$y      \033[0m",
        "${1}    _g@@@@@P~             ~@@@@@@@@@@@@@@@@@$_    \033[0m",
        "${1}   y@@@@@@~      $@$y       @@@@@@@@@@@@@@@@@@y   \033[0m",
        "${1}  g@@@@@@@_      9@@@$      \"@@@@@@@@@@@@@@@@@@g  \033[0m",
        "${1} g@@@@@@@@@y     \"@@@@L      @@@@~`  ~T@@@@@@@@@g \033[0m",
        "${1} @@@@@@@@@@@y     \"@@@F     g@@@F      $@@@@@@@@@_\033[0m",
        "${1}g@@@@@@@@@@@@y      ~~    _a@@@@      g@@@@@@@@@@$\033[0m",
        "${1}@@@@@@@@@@@@@@$         ya@@@@@@     g@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@@$      a@@@@@@@@$    a@@@@@@@@@@@@@\033[0m",
        "${1}@@@@@@@@@@@@@@@@$_    \"@@@@@@@@$  _@@@@@@@@@@@@@@@\033[0m",
        "${1}4@@@@@@@@@@@@@@@@@_    ?@@@@@@@$_y@@@@@@@@@@@@@@@$\033[0m",
        "${1}\"@@@@@@@@@@@@@@@@@@y    4@@@@@@@@@@@@@@@@@@@@@@@@^\033[0m",
        "${1} 4@@@@@@@@@@@@@@@@@@$,   $@@@@~ `@@@@@@@@@@@@@@@F \033[0m",
        "${1}  4@@@@@@@@@@@@@@@@@@@gya@@@@@yyy@@@@@@@@@@@@@@F  \033[0m",
        "${1}   7@@@@@@@@@PPPPPPPPPPPPPPPPPPPPPPPR@@@@@@@@@F   \033[0m",
        "${1}    `@@@@@@@                          $@@@@@@`    \033[0m",
        "${1}      ~@@@@@$gyyyyyyyyyyyyyyyyyyyyyyag@@@@@~      \033[0m",
        "${1}        ~5@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F~        \033[0m",
        "${1}           ~FR@@@@@@@@@@@@@@@@@@@@@@@F~           \033[0m",
        "${1}               ~~FPR@@@@@@@@@@RPF~~               \033[0m",
        NULL
    }
};

static const char* endeavouros_COLORS[] = { "\033[38;2;127;63;191m", NULL };
static const RealEquivalentLogo endeavouros_logo = {
    .id = "endeavouros",
    .default_colors = endeavouros_COLORS,
    .lines = {
        "${1}                           y$@y                   \033[0m",
        "${1}                         y$@@@@@y                 \033[0m",
        "${1}                       yg@@@@@@@@@y               \033[0m",
        "${1}                     yg@@@@@@@@@@@@@y             \033[0m",
        "${1}                   _a@@@@@@@@@@@@@@@@@y           \033[0m",
        "${1}                  a@@@@@@@@@@@@@@@@@@@@g_         \033[0m",
        "${1}                y@@@@@@@@@@@@@@@@@@@@@@@@g        \033[0m",
        "${1}              y@@@@@@@@@@@@@@@@@@@@@@@@@@@@_      \033[0m",
        "${1}            yg@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@g     \033[0m",
        "${1}          _a@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$,   \033[0m",
        "${1}         a@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@_  \033[0m",
        "${1}       y@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@_ \033[0m",
        "${1}     y@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$ \033[0m",
        "${1}   yg@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L\033[0m",
        "${1} _a@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@$\033[0m",
        "${1}=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F\033[0m",
        "${1}    `~@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F \033[0m",
        "${1}    _@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F`  \033[0m",
        "${1}   y@@@@@@@@@@@@@@@@@@@@@@@@@@@RRR@PPFFF~~~`      \033[0m",
        NULL
    }
};

static const char* kali_COLORS[] = { "\033[38;2;54;123;240m", NULL };
static const RealEquivalentLogo kali_logo = {
    .id = "kali",
    .default_colors = kali_COLORS,
    .lines = {
        "${1}                                                  \033[0m",
        "${1}                                                  \033[0m",
        "${1}                                                  \033[0m",
        "${1}                  _yyaggggggyyy_                  \033[0m",
        "${1}              _yg@@@@@@@@@@@@@@@@gy_              \033[0m",
        "${1}    ____    ua@@@@@@@@@@@@@@@@@@@@@@$y            \033[0m",
        "${1}  ~~~~~~~~Q@@$ggyZZFP@@@@@@@@@@@@@@@@@@y          \033[0m",
        "${1}    ____yyZyyyyyyyZZDL$@@@@@@@@@@@@@@@@@g         \033[0m",
        "${1}==FT~~``g@@RPFTZyyygg@J@@@@@@@$@@@@@@@@@@g        \033[0m",
        "${1}       _Eag@@@@@@@@@@P~yyyy_~~FaZ@@@@@@@@@_       \033[0m",
        "${1}   y*fT@@@@@@@@@@@@@~y@@@@@@@@$g,~R@@@@@@@$       \033[0m",
        "${1}       $@@@@@@@@@@@$ $@@@@@@@@@@@gy~$@@@@@$       \033[0m",
        "${1}       4@@@@@@@@@@@@_~@@@@@@@@@@@@@@@@@@@@$       \033[0m",
        "${1}       \"@@@@@@@@@@@@@g_~FPPPRRR@@@@@@@@@@@^       \033[0m",
        "${1}        4@@@@@@@@@@@@@@@@@@$$ggyy_~ZA@@@@F        \033[0m",
        "${1}         4@@@@@@@@@@@@@@@@@@@@@@@@g~@gM@F         \033[0m",
        "${1}          ~@@@@@@@@@@@@@@@@@@@@@@@@@y@@`          \033[0m",
        "${1}            ~@@@@@@@@@@@@@@@@@@@@@@@@\" 7          \033[0m",
        "${1}              `~R@@@@@@@@@@@@@@@@@F~ )            \033[0m",
        "${1}                  `~T5P#RRPPFF~~                  \033[0m",
        "${1}                                                  \033[0m",
        "${1}                                                  \033[0m",
        "${1}                                                  \033[0m",
        NULL
    }
};

static const RealEquivalentLogo *all_logos[] = {
    &fedora_logo, &arch_logo, &cachyos_logo, &linuxmint_logo, &manjaro_logo, &opensuse_logo, &popos_logo, &endeavouros_logo, &kali_logo
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
        real_fetch_print_line(logo_line, selected->default_colors, info_line);
    }
}

void list_logos(void) {
    for (size_t i = 0; i < sizeof(all_logos) / sizeof(all_logos[0]); i++)
        puts(all_logos[i]->id);
}
