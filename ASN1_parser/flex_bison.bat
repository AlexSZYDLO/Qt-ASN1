set cur=%cd%

cd /D "%~dp0"

..\..\_bin\win_flex_bison\win_flex.exe --wincompat Lexer.l



..\..\_bin\win_flex_bison\win_bison.exe -v Parser.y

cd %cd%
