cd ..
call .\vendor\bin\premake\premake5.exe vs2022 .\premake5.lua
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)