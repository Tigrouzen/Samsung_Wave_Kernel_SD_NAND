#!/bin/sh

export USE_CCACHE=1

        CCACHE=ccache
        CCACHE_COMPRESS=1
        CCACHE_DIR=/home/dominik/android/ccache
        export CCACHE_DIR CCACHE_COMPRESS
###########################################################################################################
./i9000.sh
./brasil.sh

rm arch/arm/boot/compressed/piggy.xzkern
