@echo off
pushd libraries
for %%f in (*.def) do (
    lib /MACHINE:X64 /DEF:%%~nxf /OUT:%%~nf.lib
)
popd
