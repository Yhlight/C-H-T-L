#!/usr/bin/env bash
set -euo pipefail
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)
ROOT_DIR=$(cd "$SCRIPT_DIR/.." && pwd)
BIN_DIR="$ROOT_DIR/bin"
TOOLS_DIR="$ROOT_DIR/tools"
ANTLR_JAR="$TOOLS_DIR/antlr-4.13.1-complete.jar"

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <input.css>" >&2
  exit 1
fi

java -classpath "$BIN_DIR:$ANTLR_JAR" chtl.css.CssMain "$1"