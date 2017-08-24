
pushd "%~dp0" 
rem set path="C:\Program Files\WinRAR"
set path="C:\Program Files (x86)\WinRAR\"

set toolname=IoT-SDK_V2.0.zip

erase %toolname%

set foldername=IoT-SDK_V2.0

start /wait winrar a -r %toolname% %foldername%\*.*  

pause

