@echo off

set PROGRAM="%~1"
if %PROGRAM%=="" (
	echo Please specify path to the program
	exit /B 1
)

set OUT="%TEMP%/out.txt"
set TEMPTRASH="%TEMP%/trash.txt"

 
%PROGRAM% > %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% 12 > %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% 12 21 > %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% 12 21 12 21 > %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% 2 37 0 > %OUT%
fc %CD%\tests\radixOutOfRange.output.txt %OUT% > %TEMPTRASH% || goto err
                                                                       
%PROGRAM% 1 36 2 > %OUT%
fc %CD%\tests\radixOutOfRange.output.txt %OUT% > %TEMPTRASH% || goto err
                                                         
%PROGRAM% 2 12 asdz > %OUT%
fc %CD%\tests\wrongNumber.output.txt %OUT% > %TEMPTRASH% || goto err
                                                         
%PROGRAM% 2 2 40 > %OUT%
fc %CD%\tests\wrongNumber.output.txt %OUT% > %TEMPTRASH% || goto err
                                                         
%PROGRAM% 10 2 -1232132132132132132131 > %OUT%
fc %CD%\tests\numberOutOfRange.output.txt %OUT% > %TEMPTRASH% || goto err
                                                         
%PROGRAM% 10 4 12321 > %OUT%
fc %CD%\tests\numbers.output.txt %OUT% > %TEMPTRASH% || goto err
                                                         
%PROGRAM% 2 36 11011100000110 > %OUT%
fc %CD%\tests\letters.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% 16 10 -80000000 > %OUT%
fc %CD%\tests\int_min.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% 16 10 7FFFFFFF > %OUT%
fc %CD%\tests\int_max.output.txt %OUT% > %TEMPTRASH% || goto err
                                                               
echo Test passed
exit /B 0

:err
echo Test failed
exit /B 1
