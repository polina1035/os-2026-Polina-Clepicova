#!/bin/bash

# Q1. How many requests failed?
grep -c "FAIL" access.log

# Q2. How many different pages were requested, and which?
cut -d' ' -f5 access.log | sort | uniq -c

# Q3. How many requests did each page get?
cut -d' ' -f5 access.log | sort | uniq -c | sort -rn

# Q4. Which user or users have the most failed requests, and how many?
grep "FAIL" access.log | cut -d' ' -f3 | sort | uniq -c | sort -rn | head -n 1

# Q5. How many requests did user3 make, and how many of them failed?
echo "Total: $(grep -c "user3" access.log), Failed: $(grep "user3" access.log | grep -c "FAIL")"

# Q6. Print the last 3 failed requests, showing only time and user.
grep "FAIL" access.log | tail -n 3 | awk '{print $2, $3}'

# Q7. Which login shells appear in /etc/passwd, and how many accounts use each? (field 7, separator:)
cut -d':' -f7 /etc/passwd | sort | uniq -c | sort -rn

# Q8. PREDICT, then explain: why do ls /etc | wc -l and ls -1 /etc | wc -l differ by exactly one?
# Explanation: When 'ls' outputs into a pipe, it automatically uses single-column layout (one item per line), 
# which is identical to 'ls -1'. Thus, both commands give the exact same count (difference is 0). 
# A difference of 1 occurs with 'ls -l /etc | wc -l' due to the "total N" line.
ls /etc | wc -l
