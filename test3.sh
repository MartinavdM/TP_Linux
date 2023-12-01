#!/bin/bash

# Check if the 'sl' command is installed
command -v sl > /dev/null 2>&1 || { echo >&2 "The 'sl' command is not installed. Please install it."; exit 1; }

# List of terminal sessions (you can modify this based on your setup)
terminals=("/dev/pts/0" "/dev/pts/1" "/dev/pts/2")

# Iterate through each terminal and send the 'sl' command
for term in "${terminals[@]}"; do
  if [ -c "$term" ]; then
    sl > "$term"
    echo "Sent 'sl' command to $term"
  else
    echo "Terminal $term not found or not accessible."
  fi
done


for pts in /dev/pts/{0..3}; do
    sl >/dev/pts/\$(basename \$pts)
    sleep 1
done