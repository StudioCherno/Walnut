#!/usr/bin/echo Download https://premake.github.io and run: "premake5 gmake2 && make". Best regards, 
@echo off

pushd ..
vendor\bin\premake5.exe vs2022
popd
pause
