#   Cron-Parser

A command line application which parses a cron string and expands each field to show the times at which it will run. This program was a task for an internship.

Can parse minutes, hours, days of month, monthes and days of week. But does not support special strings as "@yearly", "L", "W", "?", "#".

## Installation and Run
```bash
make cron-parser
./cron-parser "*/15 0 1,15 * 1-5 /usr/bin/find"
```

##  Input
There is an example of input
```bash
./cron-parser "*/15 0 1,15 * 1-5 /usr/bin/find"
```

## Output
```bash
minute 0 15 30 45
hour 0
day of month 1 15
month 1 2 3 4 5 6 7 8 9 10 11 12
day of week 1 2 3 4 5
command /usr/bin/find
```

## Tests
```bash
make test
./test
```
