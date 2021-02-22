

set PROGRAM="%~1"
if %PROGRAM%=="" (
	echo Please specify path to the program
	exit /B 1
)

set OUT="c:/dev/executable/out.txt"
set TEMPTRASH="%TEMP%/out.txt"

 
%PROGRAM% > %OUT%
fc %CD%\tests\error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\input.txt > %OUT%
fc %CD%\tests\error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\input.txt %CD%\tests\output.txt > %OUT%
fc %CD%\tests\error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\input.txt %CD%\tests\output.txt searchString > %OUT%
fc %CD%\tests\error.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\emptyInputFile.txt %OUT% laptop notebook
fc %CD%\tests\emptyOutputFile.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\notepad.txt %OUT% notepad laptop
fc %CD%\tests\notepad.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\notepad.txt %OUT% '' laptop
fc %CD%\tests\notepad.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\notepad.txt %OUT% notepad notepad
fc %CD%\tests\notepad.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\notepad.txt %OUT% ote laptop
fc %CD%\tests\notepad-middle.output.txt %OUT% > %TEMPTRASH% || goto err


echo Test passed
exit /B 0

:err
echo Test failed
exit /B 1
