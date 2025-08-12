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

# Collect sources
find "$OUT_DIR" "$SRC_DIR" -name '*.java' > "$ROOT_DIR/.sources.list"

# Conditionally drop CSS/JS mains if generated parsers are missing
if [[ ! -f "$OUT_DIR/css/CSS3Lexer.java" ]]; then
  grep -v "/src/chtl/css/CssMain.java" "$ROOT_DIR/.sources.list" > "$ROOT_DIR/.sources.tmp" || true
  mv "$ROOT_DIR/.sources.tmp" "$ROOT_DIR/.sources.list"
fi
if [[ ! -f "$OUT_DIR/js/ECMAScriptLexer.java" ]]; then
  grep -v "/src/chtl/js/JsMain.java" "$ROOT_DIR/.sources.list" > "$ROOT_DIR/.sources.tmp" || true
  mv "$ROOT_DIR/.sources.tmp" "$ROOT_DIR/.sources.list"
fi

# Compile
javac -classpath "$ANTLR_JAR" -d "$BIN_DIR" @"$ROOT_DIR/.sources.list"