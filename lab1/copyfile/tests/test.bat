@echo off

set PROGRAM="%~1"
if %PROGRAM%=="" (
	echo Please specify path to the program
	exit /B 1
)

set OUT="%TEMP%/out.txt"

 
%PROGRAM% > %OUT%
fc error.txt %OUT% || goto err

%PROGRAM% input.txt > %OUT%
fc error.txt %OUT% || goto err

%PROGRAM% input.txt output.txt additionalFile.txt > %OUT%
fc error.txt %OUT% || goto err

%PROGRAM% emptyInputFile.txt output.txt > %OUT%
fc emptyOutputFile.txt output.txt || goto err

%PROGRAM% fillInputFile.txt output.txt > %OUT%
fc fillOutputFile.txt output.txt || goto err


echo Test passed
exit /B 1

:err
echo Test failed
exit /B 1
