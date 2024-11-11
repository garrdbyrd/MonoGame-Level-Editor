#!/bin/bash
cd build && make clean && qmake .. && make && cd .. && ./caspian