@echo off
dotnet publish -c Release -r win-x64 -p:PublishAot=true -p:DebugType=none
