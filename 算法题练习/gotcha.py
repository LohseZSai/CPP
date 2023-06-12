time1,time2 = map(str,input().split(','))

hour1 = int(time1[:2])
minute1 = int(time1[2:])
hour2 = int(time2[:2])
minute2 = int(time2[2:])

diff_hour = hour2 - hour1
diff_minute = minute2 - minute1

if diff_minute < 0:
    diff_hour -= 1
    diff_minute += 60

diff_str = '{:02d}{:02d}'.format(diff_hour, diff_minute)
print(diff_str)