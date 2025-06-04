@echo off
setlocal enabledelayedexpansion

:: Collect all .cpp files in src and subdirectories
set sources=
for /R ../src %%f in (*.cpp) do (
    set sources=!sources! "%%f"
)

:: Compile using g++
g++ !sources! -o Game.exe -O -I ../include/ -L ../lib/ -lraylib -lgdi32 -lwinmm

:: Run the game if compilation succeeds
if exist Game.exe (
    echo Running Game.exe...
    Game.exe
    pause
) else (
    echo Compilation failed. Game.exe not found.
    pause
)

:: Pause to see errors (if any)
:: pause