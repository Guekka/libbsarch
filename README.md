# BSArchive DLL and C++ bindings
BSArchive Dynamic Link Library and C++ bindings

## How to build

1) Create a `XEditPath` environment variable and set it to the directory cointaining the XEdit code
2) Build the DLL in Delphi by opening the `libbsarch.dproj` project
3) Build the LIB in Visual Studio by opening the `libbsarch.sln` project
4) Rename `libbsarch_dummy.lib` to `libbsarch.lib`

## How to use

Use the `libbsarch.dll`, `libbsarch.lib` and `libbsarch.h` in your project.