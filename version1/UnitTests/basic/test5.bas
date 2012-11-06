10 REM Improved square root program
30 INPUT "Enter a number: ", x$
35 IF VALLEN(x$)=0 THEN 30
37 LET x=VAL(x$)
40 REM Prompt user if negative
50 IF x >= 0 THEN 80
60 PRINT "Number may not be negative"
70 GOTO 30
80 PRINT "Square root of ", x, "is", SQRT(x)


