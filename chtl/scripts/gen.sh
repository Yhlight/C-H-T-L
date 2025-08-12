#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)
GRAMMAR_DIR="$ROOT_DIR/grammar"
OUT_DIR="$ROOT_DIR/gen"
JAR="$ROOT_DIR/tools/antlr-4.13.1-complete.jar"

mkdir -p "$OUT_DIR"

# Generate CHTL
java -jar "$JAR" -Dlanguage=Java -visitor -no-listener -package chtl.parser -o "$OUT_DIR" "$GRAMMAR_DIR/CHTL.g4"

# Generate CSS
CSS_GRAMMAR_DIR="$GRAMMAR_DIR/css"
CSS_OUT_DIR="$OUT_DIR/css"
mkdir -p "$CSS_OUT_DIR"
java -jar "$JAR" -Dlanguage=Java -visitor -no-listener -package chtl.css.parser -o "$CSS_OUT_DIR" "$CSS_GRAMMAR_DIR/CSS3.g4"

# Generate JS (ECMAScript)
JS_GRAMMAR_DIR="$GRAMMAR_DIR/js"
JS_OUT_DIR="$OUT_DIR/js"
mkdir -p "$JS_OUT_DIR"
java -jar "$JAR" -Dlanguage=Java -visitor -no-listener -package chtl.js.parser -o "$JS_OUT_DIR" "$JS_GRAMMAR_DIR/ECMAScript.g4"