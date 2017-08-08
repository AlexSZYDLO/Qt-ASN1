# Qt-ASN1
ASN.1 parser writen in C++ with Qt GUI and Qt Script

The visual studio solution only integrates ASN1_lib and ASN1_console

There is 5 Qt Creator projects with dependencies. To be compiled in this order:
  1     - ASN1_lib
  
  1 bis - ASN1_parser - if changes are made in parser.y or lexer.l, execute flex_bison.bat 
          (requires win_flex.exe and win_bison.exe. Check the path in bat file)
          
  2 - ASN1_console - only a test executable for ASN1_lib, not needed for the rest
  
  3 - ASN1_Qt_Script_lib
  
  4 - ASN1_Qt_gui

  
