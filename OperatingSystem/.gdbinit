set disassembly intel
source gdb/map_load.py
map-load obj/operating-system.m
target remote 10.0.0.8:1234

