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
echo Test 1 passed

%PROGRAM% infile.txt > %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 2 passed

%PROGRAM% infile.txt outfile.txt wrongfile.txt > %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 3 passed                   

%PROGRAM% %CD%\tests\noStart.input.txt %OUT% > %OUT%
fc %CD%\tests\noStart.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 4 passed

%PROGRAM% %CD%\tests\wrongContour.input.txt %OUT% > %OUT%
fc %CD%\tests\wrongContour.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 5 passed

                                                               
echo Tests passed
exit /B 0

:err
echo Tests failed
exit /B 1
