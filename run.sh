#!/usr/bin/env bash
set -eu

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SRC_DIR="$ROOT_DIR/src"
OUT_DIR="$ROOT_DIR/build"
OS_NAME="$(uname -s)"
CXX="${CXX:-c++}"
PKG_CONFIG="${PKG_CONFIG:-pkg-config}"
SFML_PACKAGES=(sfml-graphics sfml-window sfml-system)

case "$OS_NAME" in
  Linux*)
    PLATFORM="Linux"
    OUTPUT="$OUT_DIR/omarchu"
    ;;
  Darwin*)
    PLATFORM="macOS"
    OUTPUT="$OUT_DIR/omarchu"
    ;;
  MINGW*|MSYS*|CYGWIN*)
    PLATFORM="Windows (POSIX shell)"
    OUTPUT="$OUT_DIR/omarchu.exe"
    ;;
  *)
    PLATFORM="$OS_NAME"
    OUTPUT="$OUT_DIR/omarchu"
    ;;
esac

mkdir -p "$OUT_DIR"

if ! command -v "$CXX" >/dev/null 2>&1; then
  printf 'Error: C++ compiler not found: %s\n' "$CXX" >&2
  printf 'Set CXX to an installed C++17 compiler (for example, g++ or clang++).\n' >&2
  exit 1
fi

if ! command -v "$PKG_CONFIG" >/dev/null 2>&1; then
  printf 'Error: pkg-config was not found. Install pkg-config and SFML 3 development files.\n' >&2
  exit 1
fi

if ! "$PKG_CONFIG" --exists "${SFML_PACKAGES[@]}"; then
  printf 'Error: SFML development packages were not found by pkg-config.\n' >&2
  printf 'This project uses the SFML 3 API; install SFML 3 and ensure its .pc files are discoverable.\n' >&2
  exit 1
fi

SFML_VERSION="$("$PKG_CONFIG" --modversion sfml-graphics)"
SFML_MAJOR="${SFML_VERSION%%.*}"
if [[ ! "$SFML_MAJOR" =~ ^[0-9]+$ ]] || (( SFML_MAJOR < 3 )); then
  printf 'Error: found SFML %s, but this project requires SFML 3 or newer.\n' "$SFML_VERSION" >&2
  exit 1
fi

read -r -a SFML_CFLAGS <<< "$("$PKG_CONFIG" --cflags "${SFML_PACKAGES[@]}")"
read -r -a SFML_LIBS <<< "$("$PKG_CONFIG" --libs "${SFML_PACKAGES[@]}")"

printf 'Platform: %s (%s)\n' "$PLATFORM" "$(uname -m)"
printf 'Compiler: %s\n' "$CXX"
printf 'SFML: %s\n' "$SFML_VERSION"
printf 'Building: %s\n' "$OUTPUT"

"$CXX" -std=c++17 -Wall -Wextra \
  -I"$SRC_DIR" \
  "${SFML_CFLAGS[@]}" \
  "$SRC_DIR"/*.cpp \
  "${SFML_LIBS[@]}" \
  -o "$OUTPUT"

if [[ "${BUILD_ONLY:-0}" == "1" ]]; then
  printf 'BUILD_ONLY=1; skipping execution.\n'
  exit 0
fi

printf '\nRunning %s\n' "$OUTPUT"
cd "$ROOT_DIR"
exec "$OUTPUT" "$@"
