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
echo Test 1 was passed

%PROGRAM% %CD%\tests\usual.input.txt %CD%\tests\anotherOneUsual.input.txt> %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 2 was passed

%PROGRAM% %CD%\tests\determinant0.input.txt > %OUT%
fc %CD%\tests\determinant0.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 3 was passed

%PROGRAM% %CD%\tests\letters.input.txt > %OUT%
fc %CD%\tests\wrongMatrix.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 4 was passed
                                                                        
%PROGRAM% %CD%\tests\usual.input.txt > %OUT%
fc %CD%\tests\usual.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 5 was passed
         
%PROGRAM% %CD%\tests\usual2.input.txt > %OUT%
fc %CD%\tests\usual2.output.txt %OUT% > %TEMPTRASH% || goto err
echo Test 6 was passed
                                                                                                              
echo Test passed
exit /B 0

:err
echo Test failed
exit /B 1
