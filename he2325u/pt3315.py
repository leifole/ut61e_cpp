#!/usr/bin/env python

import fileinput
import struct

for packet in fileinput.input():
    bbs = bytearray(packet,'utf-8')

    for i,byte in enumerate(bbs):
        bbs[i] = byte & 0x0F
        
    prec, d3,d2,d1,d0,function,status,option1,option2 = struct.unpack('BBBBBBBBBxx',bbs)

    if function == 0b1011:

        v = d3 * 1e3 + d2 * 1e2 + d1 * 1e1 + d0
        if (status & 0b0000100):
            v = -v

        if prec == 0x00: fac = 1e-1
        elif prec == 0x01: fac = 1e-3
        elif prec == 0x02: fac = 1e-2
        elif prec == 0x03: fac = 1e-1
        elif prec == 0x04: fac = 1
        else: fac = 1

        v = v * fac

        print "V: ",v

