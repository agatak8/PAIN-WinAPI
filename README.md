# PAIN-WinAPI
A two program Win32 API application. The two programs communicate via broadcasted Windows API messages.
## Summary and controls
### master.exe (one instance)
Displays 3 basic shapes at a random location and allows moving them. Controls:
- 1,2,3 : choose shape to be controlled (circle, triangle, square respectively)
- arrow keys : move shape
- mouse-click : move shape to mouse location
### slave.exe (one or more instances)
Copies the shapes' locations from master and displays them at a scale. Controls:
- Ctrl+ : increase scale
- Ctrl- : decrease scale


## Building
Use `make` to compile. On Windows, `cl` is used by default. Otherwise `i686-w64-mingw32-gcc-win32` is used.
## Usage
Run `master.exe` once and then run `slave.exe` once or more times.
