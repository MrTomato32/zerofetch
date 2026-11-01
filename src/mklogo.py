import re
import sys

# Usage: chafa ... | python3 mklogo.py NAME
name = sys.argv[1]
print(f"static const RealEquivalentLogo {name}_logo = {{")
print(f'    .id = "{name}",')
print("    .default_colors = NO_COLORS,")
print("    .lines = {")
for line in sys.stdin.read().splitlines():
    line = re.sub(r"\x1b\[\?25[lh]", "", line)   # drop cursor hide/show
    line = line.replace("\\", "\\\\").replace('"', '\\"')
    line = line.replace("\x1b", "\\033")          # ESC -> C escape
    print(f'        "{line}\\033[0m",')
print("        NULL")
print("    }")
print("};")
