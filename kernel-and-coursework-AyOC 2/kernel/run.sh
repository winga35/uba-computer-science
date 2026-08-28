#!/usr/bin/env bash
set -e
cd "$(dirname "$0")/src"
make image
exec qemu-system-i386 -drive format=raw,if=floppy,file=diskette.img "$@"
