#!/usr/bin/python2

import time
from math import floor

"""
Gaussian algorithm to determine day of week
"""
def day_of_week(year, month, day):
    """
    w = (d+floor(2.6*m-0.2)+y+floor(y/4)+floor(c/4)-2*c) mod 7

    Y = year - 1 for January or February
    Y = year for other months
    d = day (1 to 31)
    m = shifted month (March = 1, February = 12)
    y = last two digits of Y
    c = first two digits of Y
    w = day of week (Sunday = 0, Saturday = 6)
    """

    d = day
    m = (month - 3) % 12 + 1
    if m > 10: Y = year - 1
    else: Y = year
    y = Y % 100
    c = (Y - (Y % 100)) / 100

    w = (d + floor(2.6 * m - 0.2) + y + floor(y/4) + floor(c/4) - 2*c) % 7

    return int(w)


def months_start_range(day,year_start,year_end):
    """
    Compute the number of months starting on a given day of the week in range of years
    """
    total = 0
    for year in range(year_start, year_end + 1):
        for month in range(1,13):
            if day_of_week(year, month, 1) == day: total += 1
    return total

start = time.time()
total = months_start_range(0,1901,2000)
elapsed = time.time() - start

print("%s found in %s seconds") % (total,elapsed)
