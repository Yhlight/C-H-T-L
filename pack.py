#!/usr/bin/env python3
"""
CHTL 打包入口脚本
"""
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'scripts', 'cross-platform'))
from pack import main

if __name__ == "__main__":
    sys.exit(main())