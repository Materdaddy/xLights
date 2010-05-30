10 REM Test Date/Time functions
30 REM By Matt Brown
40 LET T=NOW
50 PRINT "NOW as number: ",T
60 PRINT "DATE ",YEAR(T),"-",MONTH(T),"-",DAY(T)
70 PRINT "TIME ",HOUR(T),":",MINUTE(T),":",SECOND(T)
80 PRINT "Formatted (date/time): ",FORMATDATETIME$(T,0)
81 PRINT "Formatted (date): ",FORMATDATETIME$(T,1)
82 PRINT "Formatted (long time): ",FORMATDATETIME$(T,3)
83 PRINT "Formatted (short time): ",FORMATDATETIME$(T,4)
100 LET Y=1990
110 FOR M=1 TO 12
115 LET T=DATESERIAL(Y,M,1)
120 PRINT "Y=",Y," M=",M," D=",1," number=",T," formatted=",FORMATDATETIME$(T,1)
130 NEXT M
