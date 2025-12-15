#!/bin/bash
timeout 2 valgrind --leak-check=full --show-leak-kinds=all ./cub3d ./map/map.cub 2>&1 &
PID=$!
sleep 0.5
# Close the window by sending Escape key event if possible, or just kill after timeout
wait $PID 2>/dev/null || true
