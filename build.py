#!/usr/bin/env python3
"""
CHTL 构建入口脚本
"""
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'scripts', 'cross-platform'))
from build import main

if __name__ == "__main__":
    sys.exit(main())