#!/bin/bash

# Function to format C and H files in a directory recursively
format_files() {
    local dir="$1"

    # Loop through files and directories in the given directory
    for file in "$dir"/*; do
        if [ -d "$file" ]; then
            # If it's a directory, recursively call the function
            format_files "$file"
        elif [[ "$file" == *.c || "$file" == *.h ]]; then
            # If it's a C or H file, run the formatter
            c_formatter_42 < "$file" > "$file.tmp" && mv "$file.tmp" "$file"
            echo "Formatted: $file"
        fi
    done
}

# Check if an argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Check if the argument is a directory
if [ ! -d "$1" ]; then
    echo "$1 is not a directory."
    exit 1
fi

# Call the function with the provided directory
format_files "$1"
