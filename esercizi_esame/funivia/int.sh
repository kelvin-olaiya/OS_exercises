#!/bin/bash
find /usr/include/linux/ -name "*.h" -exec grep "int" {} \; | cut -b 1-3