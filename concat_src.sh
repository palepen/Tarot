#!/bin/bash

# Usage: ./concat_sources.sh /path/to/source_dir output_file.txt

SOURCE_DIR="$1"
OUTPUT_FILE="$2"

if [[ -z "$SOURCE_DIR" || -z "$OUTPUT_FILE" ]]; then
    echo "Usage: $0 <source_directory> <output_file>"
    exit 1
fi

# Ensure output file is empty before starting
> "$OUTPUT_FILE"

# File extensions to include
EXTENSIONS=("*.c" "*.cpp" "*.h" "*.hpp" "*.cc" "*.cxx")

echo "Collecting source files from $SOURCE_DIR ..."

for ext in "${EXTENSIONS[@]}"; do
    find "$SOURCE_DIR" -type f -name "$ext" | sort | while read -r file; do
        echo "Appending $file ..."
        echo -e "\n\n// -------- $file --------\n" >> "$OUTPUT_FILE"
        cat "$file" >> "$OUTPUT_FILE"
    done
done

echo "All source files written to $OUTPUT_FILE"
