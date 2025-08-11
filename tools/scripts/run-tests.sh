#!/bin/bash

# CHTL Integration Test Suite

set -e

CHTL_BIN=${CHTL_BIN:-"./build/chtl"}
TEST_DIR="test-results"
FAILED=0
PASSED=0

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Create test results directory
mkdir -p $TEST_DIR

# Test function
run_test() {
    local test_name=$1
    local test_file=$2
    local expected_pattern=$3
    
    echo -n "Testing $test_name... "
    
    if $CHTL_BIN $test_file -o $TEST_DIR/$test_name 2>/dev/null; then
        if [ -n "$expected_pattern" ]; then
            if grep -q "$expected_pattern" $TEST_DIR/$test_name/index.html; then
                echo -e "${GREEN}PASSED${NC}"
                ((PASSED++))
            else
                echo -e "${RED}FAILED${NC} (pattern not found: $expected_pattern)"
                ((FAILED++))
            fi
        else
            echo -e "${GREEN}PASSED${NC}"
            ((PASSED++))
        fi
    else
        echo -e "${RED}FAILED${NC} (compilation error)"
        ((FAILED++))
    fi
}

# Run tests
echo "Running CHTL Integration Tests"
echo "=============================="

# Variable group tests
run_test "var-function" "test-var-function-fixed.chtl" "#3498db"
run_test "var-override" "test-var-function-fixed.chtl" "#ff6666"

# Delete syntax tests
if [ -f "test-delete-correct.chtl" ]; then
    run_test "delete-syntax" "test-delete-correct.chtl" ""
fi

# Error recovery tests
if [ -f "test-complex-file.chtl" ]; then
    run_test "error-recovery" "test-complex-file.chtl" "" || true
fi

# Basic syntax tests
echo 'div { text { "Hello World" } }' > $TEST_DIR/basic.chtl
run_test "basic-syntax" "$TEST_DIR/basic.chtl" "Hello World"

echo '[Template] @Style Theme { color: red; }' > $TEST_DIR/template.chtl
echo 'div { style { @Style Theme; } }' >> $TEST_DIR/template.chtl
run_test "template-style" "$TEST_DIR/template.chtl" "color: red"

# CJmod tests
echo '[Import] @CJmod from "reactive";' > $TEST_DIR/cjmod.chtl
echo 'div { text { "CJmod Test" } }' >> $TEST_DIR/cjmod.chtl
run_test "cjmod-import" "$TEST_DIR/cjmod.chtl" "CJmod Test"

# Summary
echo "=============================="
echo -e "Tests Passed: ${GREEN}$PASSED${NC}"
echo -e "Tests Failed: ${RED}$FAILED${NC}"

# Clean up
rm -rf $TEST_DIR

# Exit with error if any test failed
if [ $FAILED -gt 0 ]; then
    exit 1
fi

exit 0