#!/bin/bash

# Get the absolute path to the Git repository root
REPO_ROOT=$(git rev-parse --show-toplevel)

# Check if the platform is macOS
if [[ "$OSTYPE" == "darwin"* ]]; then
    OUTPUT_DIR="$REPO_ROOT/docs/doxygen"
else
    # Assume the platform is Windows
    OUTPUT_DIR="$REPO_ROOT/docs/doxygen"
fi

# Set the OUTPUT_DIRECTORY variable in the Doxyfile
sed -i.bak "s#^OUTPUT_DIRECTORY.*#OUTPUT_DIRECTORY = $OUTPUT_DIR#" Doxyfile
