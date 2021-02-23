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

%PROGRAM% %CD%\tests\usual.input.txt %CD%\tests\anotherOneUsual.input.txt> %OUT%
fc %CD%\tests\wrongCountParams.output.txt %OUT% > %TEMPTRASH% || goto err

%PROGRAM% %CD%\tests\determinant0.input.txt > %OUT%
fc %CD%\tests\determinant0.output.txt %OUT% > %TEMPTRASH% || goto err
                                                                        
%PROGRAM% %CD%\tests\usual.input.txt > %OUT%
fc %CD%\tests\usual.output.txt %OUT% > %TEMPTRASH% || goto err
         
%PROGRAM% %CD%\tests\usual2.input.txt > %OUT%
fc %CD%\tests\usual2.output.txt %OUT% > %TEMPTRASH% || goto err

                                                                                                              
echo Test passed
exit /B 0

:err
echo Test failed
exit /B 1
