#!/usr/bin/env bash
set -eu

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SRC_DIR="$ROOT_DIR/src"
OUT_DIR="$ROOT_DIR/build"
OUTPUT="$OUT_DIR/game"
OUTPUT="$OUT_DIR/game"

mkdir -p "$OUT_DIR"

g++ -std=c++17 -Wall -Wextra \
  -I/usr/local/include \
  -I"$ROOT_DIR/src" \
g++ -std=c++17 -Wall -Wextra \
  -I/usr/local/include \
  -I"$ROOT_DIR/src" \
  "$SRC_DIR"/*.cpp \
  -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lsfml-network-s \
  -lfreetype -lz -lbz2 -lpng16 -lGL -lX11 -lXrandr -lXcursor -lXfixes -lXi -ludev \
  -l:libxkbcommon.so.0 -l:libxkbcommon-x11.so.0 \
  -lopenal -lvorbisenc -lvorbis -logg -lvorbisfile -lFLAC -pthread \
  -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-audio-s -lsfml-network-s \
  -lfreetype -lz -lbz2 -lpng16 -lGL -lX11 -lXrandr -lXcursor -lXfixes -lXi -ludev \
  -l:libxkbcommon.so.0 -l:libxkbcommon-x11.so.0 \
  -lopenal -lvorbisenc -lvorbis -logg -lvorbisfile -lFLAC -pthread \
  -o "$OUTPUT"

printf '\nRunning %s\n' "$OUTPUT"
exec "$OUTPUT"
