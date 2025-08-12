#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)
OUT_DIR="$ROOT_DIR/gen"
SRC_DIR="$ROOT_DIR/src"
BIN_DIR="$ROOT_DIR/bin"
TOOLS_DIR="$ROOT_DIR/tools"
ANTLR_JAR="$TOOLS_DIR/antlr-4.13.1-complete.jar"

mkdir -p "$BIN_DIR"

find "$OUT_DIR" "$SRC_DIR" -name '*.java' > "$ROOT_DIR/.sources.list"

javac -classpath "$ANTLR_JAR" -d "$BIN_DIR" @"$ROOT_DIR/.sources.list"