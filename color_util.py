#!/usr/bin/env python3

h = input('Enter hex: ').lstrip('#')
res = tuple(int(h[i:i+2], 16) for i in (0, 2, 4))
print('RGB =', res)
print('RGB [0, 1] =', tuple(col/255 for col in res))
