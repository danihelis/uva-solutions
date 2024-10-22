#!/usr/bin/env python
import sys
import os
import shutil

source = '/home/daniel/Projects/uva/solved/'
destiny = '/home/daniel/Projects/uva-solutions/'
count = 0
for f in os.listdir(source):
    volume = f[:-4]
    volume_dir = os.path.join(destiny, volume)
    if not os.path.exists(volume_dir):
        os.makedirs(volume_dir)
    shutil.copy(os.path.join(source, f), volume_dir)
    count += 1
print('Copied %d files' % count)
