#!/bin/bash
#
#
rm makefile
cp makefile--.txt makefile
cd ../../../ && make clean
cd examples/linux/mqtt/

