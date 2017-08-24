
pushd "%~dp0" 
rem set path="C:\Program Files\WinRAR"
set path="C:\Program Files (x86)\WinRAR\"

set toolname=elevatoryun.zip

erase %toolname%

set foldername=elevatoryun

start /wait winrar a -r %toolname% %foldername%\*.*  

pause

