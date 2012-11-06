10 INPUT "Enter temperature in Fahrenheit: ", f$
20 IF VALLEN(f$)=0 THEN 10
25 LET f=VAL(f$)
30 LET c = (f - 32) / 1.8
40 PRINT "=", c, "Celsius" 
