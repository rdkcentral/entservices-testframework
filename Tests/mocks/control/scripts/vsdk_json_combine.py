#!/usr/bin/env python3
"""
Minimal stub for vsdk_json_combine.py
Merges JSON config files for control manager native builds.
In this stub version, overlay files (-a, -s) are ignored if empty/missing.
"""
import argparse
import json
import sys
import os


def deep_merge(base, overlay):
    """Deep merge overlay into base dict."""
    for key, value in overlay.items():
        if key in base and isinstance(base[key], dict) and isinstance(value, dict):
            deep_merge(base[key], value)
        else:
            base[key] = value


def deep_subtract(base, subtract):
    """Remove keys from base that exist in subtract."""
    for key, value in subtract.items():
        if key in base:
            if isinstance(base[key], dict) and isinstance(value, dict):
                deep_subtract(base[key], value)
            else:
                del base[key]


def main():
    parser = argparse.ArgumentParser(description="Combine JSON config files")
    parser.add_argument("-i", "--input", required=True, help="Input JSON file")
    parser.add_argument("-o", "--output", required=True, help="Output JSON file")
    parser.add_argument("-a", "--add", action="append", default=[], help="Add/merge JSON file")
    parser.add_argument("-s", "--subtract", action="append", default=[], help="Subtract JSON file")

    args = parser.parse_args()

    with open(args.input, "r") as f:
        config = json.load(f)

    # Process all add/subtract operations in order
    all_ops = []
    for a in args.add:
        all_ops.append(("add", a))
    for s in args.subtract:
        all_ops.append(("sub", s))

    for op, path in all_ops:
        if not path or not os.path.isfile(path):
            continue
        try:
            with open(path, "r") as f:
                data = json.load(f)
            if op == "add":
                deep_merge(config, data)
            else:
                deep_subtract(config, data)
        except (json.JSONDecodeError, IOError):
            print(f"Warning: skipping {path}", file=sys.stderr)

    with open(args.output, "w") as f:
        json.dump(config, f, indent=3)


if __name__ == "__main__":
    main()
