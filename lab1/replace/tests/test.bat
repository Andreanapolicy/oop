@echo off

set PROGRAM="%~1"
if %PROGRAM%=="" (
	echo Please specify path to the program
	exit /B 1
)

set OUT="c:/dev/executable/out.txt"
set TEMPTRASH="%TEMP%/out.txt"

 
%PROGRAM% > %OUT%
fc error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% input.txt > %OUT%
fc error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% input.txt output.txt > %OUT%
fc error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% input.txt output.txt searchString > %OUT%
fc error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% emptyInputFile.txt %OUT% laptop notebook
fc emptyOutputFile.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% notepad.txt %OUT% notepad laptop
fc notepad.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% notepad.txt %OUT% '' laptop
fc notepad.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% notepad.txt %OUT% notepad notepad
fc notepad.txt %OUT% > %TEMPTRASH% || goto err


echo Test passed
exit /B 1

:err
echo Test failed
exit /B 1
