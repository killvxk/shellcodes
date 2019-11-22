#!/usr/bin/env python2.7
# -*- coding:utf-8 -*-
import pefile

pe = pefile.PE('payload.exe')
dat = pe.sections[0].get_data()
f = open("payload.bin", "wb+")
f.write(dat)
f.close()
