#!/bin/bash
#
#
rm makefile
cp makefile--.txt makefile
cd ../../../ && make
cd examples/linux/mqtt/

