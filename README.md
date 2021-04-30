# BSArchive DLL and C bindings
BSArchive Dynamic Link Library and C bindings

## How to build

1) Create a `XEditPath` environment variable and set it to the directory containing the XEdit code
2) Build the DLL in Delphi by opening the `libbsarch.dproj` project
3) Build the LIB with CMake

## How to use

With CMake: 
Use ``add_subdirectory`` and ``target_link_library``
Then ``#include "libbsarch.h"``
See the example for code use.

Without CMake:
Use `libbsarch.dll` (provided in delphi/lib), `libbsarch.lib` and `libbsarch.h` in your project.

## Credits

The original BSArchive can be found at: https://github.com/TES5Edit/TES5Edit/tree/dev/Tools/BSArchive
The version in this project had been modified by Deorder for better compatibility with C/C++ and allow the users to allocate their own memory in some cases.
Deorder is the one who made the original C bindings.
