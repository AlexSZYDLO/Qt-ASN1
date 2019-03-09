cd C:\Users\yqgx4n\VSProjects\
set binfolder=ASN1_bin
set RorD=release
set version=64

set outfolderConsole=%binfolder%\ASN1_console\qtcreator\%RorD%
set outfolderGUI=%binfolder%\ASN1_Qt_gui\qtcreator\%RorD%

set dllext=""
set qtdllext=""

set result=false
IF %version%==64 ( 
	set result=true 
	)
IF %RorD%==debug (
	set result=true
	set qtdllext=_d.dll
	)
IF %result%==true ( 
	set dllext=_
	)
IF %version%==64 ( 
	set dllext=%dllext%64
	)
IF %RorD%==debug ( 
	set dllext=%dllext%d
	)
set dllext=%dllext%.dll

set libdll=%binfolder%\ASN1_lib\qtcreator\%RorD%
set parsedll=%binfolder%\ASN1_parser\qtcreator\%RorD%
set scriptdll=%binfolder%\ASN1_Qt_Script_lib\qtcreator\%RorD%

set lib=%libdll%\ASN1_lib%dllext%
set parser=%parsedll%\ASN1_parser%dllext%
set script=%scriptdll%\ASN1_Qt_Script_lib%qtdllext%

echo y | xcopy "%lib%" "%outfolderConsole%"
echo y | xcopy "%parser%" "%outfolderConsole%"

echo y | xcopy "%lib%" "%outfolderGUI%"
echo y | xcopy "%parser%" "%outfolderGUI%"
echo y | xcopy "%script%" "%outfolderGUI%"

pause
