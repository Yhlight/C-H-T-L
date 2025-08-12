#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)
GRAMMAR_DIR="$ROOT_DIR/grammar"
OUT_DIR="$ROOT_DIR/gen"
JAR="$ROOT_DIR/tools/antlr-4.13.1-complete.jar"
mkdir -p "$OUT_DIR"
java -jar "$JAR" -Dlanguage=Java -visitor -no-listener -package chtl.parser -o "$OUT_DIR" "$GRAMMAR_DIR/CHTL.g4"