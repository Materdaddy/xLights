10 REM Calendar program.
20 DIM months$(12) = "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
40 INPUT "Day of birth? ",day
60 INPUT "Month? ", month
70 REM Make sure day and month are legal
80 IF day >= 1 AND day <= 31 AND month >= 1 AND month <= 12 THEN 110
90 PRINT "That's impossible"
100 GOTO 40
110 IF day <> INT(day) OR month <> INT(month) THEN 90
120 PRINT "Your birthday is", day, months$(month) 
