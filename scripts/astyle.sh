#!/bin/bash
ASTYLE=${HOME}/git/devenv/tools/astyle/build/gcc/bin/astyle
ASTYLERC=${HOME}/git/devenv/tools/astyle/astylerc
TARGET=$1

$ASTYLE $TARGET --options=${ASTYLERC}
