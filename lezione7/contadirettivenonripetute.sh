#!/bin/bash

find /usr/include -name *.h -exec grep '#' {} \; | sort | uniq | wc -l
find /usr/include -name *.h -exec grep '#' {} \; | wc -l
