#!/bin/bash

# Check if xclip or xsel is installed
if ! command -v xclip &>/dev/null && ! command -v xsel &>/dev/null; then
    echo "Error: You need to install xclip or xsel."
    echo "Install via: sudo apt install xclip"
    exit 1
fi

# Check if files are passed
if [ "$#" -eq 0 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

# Combine all file contents into one string
combined=""
for file in "$@"; do
    if [ -f "$file" ]; then
        combined+=$(<"$file")
        combined+=$'\n'  # Add newline between files
    else
        echo "Warning: $file is not a valid file. Skipping."
    fi
done

# Copy to clipboard using xclip or xsel
if command -v xclip &>/dev/null; then
    printf "%s" "$combined" | xclip -selection clipboard
    echo "[✔] Copied to clipboard using xclip."
elif command -v xsel &>/dev/null; then
    printf "%s" "$combined" | xsel --clipboard
    echo "[✔] Copied to clipboard using xsel."
fi

