#!/usr/bin/env python3
"""
Minimal stub for vsdk_json_to_header.py
Converts a JSON config file into C header and source files for control manager native builds.
Embeds JSON sections as C string constants.
"""
import argparse
import json
import sys
import os
import re


def json_to_c_string(data):
    """Convert a JSON-serializable object to an escaped C string literal."""
    s = json.dumps(data, indent=3)
    # Escape for C: backslashes, double quotes, newlines
    s = s.replace("\\", "\\\\")
    s = s.replace('"', '\\"')
    lines = s.split("\n")
    return "\n".join([f'   "{line}\\n"' for line in lines])


def sanitize_var(name):
    """Make a safe C variable name."""
    return re.sub(r"[^a-zA-Z0-9_]", "_", name)


def main():
    parser = argparse.ArgumentParser(description="Convert JSON config to C header/source")
    parser.add_argument("-i", "--input", required=True, help="Input JSON file")
    parser.add_argument("-o", "--output", required=True, help="Output header file")
    parser.add_argument("-c", "--source", required=True, help="Output C source file")
    parser.add_argument("-v", "--variables", required=True, help="Comma-separated list of JSON sections")
    parser.add_argument("-d", "--disabled", default="", help="Comma-separated list of disabled sections")

    args = parser.parse_args()

    with open(args.input, "r") as f:
        config = json.load(f)

    sections = [s.strip() for s in args.variables.split(",") if s.strip()]
    disabled = [s.strip() for s in args.disabled.split(",") if s.strip()] if args.disabled else []

    header_guard = "_CTRLM_CONFIG_DEFAULT_H_"

    # Generate header
    with open(args.output, "w") as h:
        h.write(f"#ifndef {header_guard}\n")
        h.write(f"#define {header_guard}\n\n")
        for section in sections:
            var = sanitize_var(section)
            h.write(f"extern const char *{var}_config_default;\n")
        h.write(f"\n#endif /* {header_guard} */\n")

    # Generate source
    with open(args.source, "w") as c:
        c.write('#include "ctrlm_config_default.h"\n\n')
        for section in sections:
            var = sanitize_var(section)
            if section in config:
                json_str = json_to_c_string(config[section])
            else:
                json_str = '   "{}"'
            c.write(f"const char *{var}_config_default =\n{json_str};\n\n")


if __name__ == "__main__":
    main()
