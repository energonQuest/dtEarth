testOcean 

To run, use the Delta3D GameStart utility and supply the library name on the command line.

Usage:
"GameStart.exe testOcean" or "GameStartD.exe testOcean"



** Visual Studio **
If running via Visual Studio, edit the testAAR project settings:
 - Debugging->Command: GameStart.exe (or "GameStartD.exe" for debug).
 - Debugging->Command Arguments: testOcean
 - Debugging->Working Directory: <path to where the testOcean .dll is>
 
Note: Make sure your PATH environment is set to %DELTA_ROOT%/bin so MSVC can 
      find the GameStart executable. 
