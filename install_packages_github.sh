#!/bin/bash

set -e  # Exit on error

# Check for required arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <directory_name> <header_url>"
    echo "Example: $0 json https://raw.githubusercontent.com/nlohmann/json/develop/single_include/nlohmann/json.hpp"
    exit 1
fi

DIR_NAME=$1
HEADER_URL=$2
HEADER_FILE=$(basename "$HEADER_URL")

TARGET_DIR="libs/${DIR_NAME}"
TARGET_FILE="${TARGET_DIR}/${HEADER_FILE}"

echo "[+] Creating directory: ${TARGET_DIR}"
mkdir -p "$TARGET_DIR"

echo "[+] Downloading ${HEADER_URL}"
curl -sSL "$HEADER_URL" -o "$TARGET_FILE"

if [ -f "$TARGET_FILE" ]; then
    echo "[✓] Downloaded: $TARGET_FILE"
else
    echo "[✗] Download failed!"
    exit 1
fi

