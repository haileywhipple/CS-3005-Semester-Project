# CS-3005 Semester Project

To see the final project, run in gui-src:
```
./glut_main
```

The following keyboard commands do this:
```
'J': creates Julia1
'j': creates Julia2
'M': creates Mandelbrot1
'm': creates Mandelbrot2
'C': creates ComplexFractal1
'c': creates ComplexFractal2

'T': sets the interaction mode to color table
't': sets the interaction mode to fractal

'b': sets the fractal mode to mandelbrot
'n': sets the fractal mode to julia
'F': sets the fractal mode to complex

'>', '.': increases color table size
'<', ',': decreases color table size

'r': if the interaction mode is the color table, then it randomizes color 1.
'R': if interaction mode is the color table, randomizes color2,
otherwise if the interaction mode is the fractal, then it resets the plane.

'z': zooms the screen in
'Z': zooms the screen out

'+', '=': increases max number
'-', '_': decreases max number

'0': sets color table mode to the next one
'1': sets interaction mode to IM_COLOR1
'2': sets interaction mode to IM_COLOR2
'3': sets interaction mode to IM_COLOR3

'Y': increases the red color
'y': decreases the red color
'U': increases the green color
'u': decreases the green color
'I': increases the blue color
'i': decreases the blue color
'e': randomizes the color 3

'a': toggles anti-alias
's': decreases anti-alias reduction count
'S': increases anti-alias reduction count
```

The following special keyboard commands do this:
```
left: moves the screen to the left
right: moves the screen to the right
down: moves the screen downwards
up: moves the screen upwards

left_mouse_click: if fractal mode is not Julia, setAB is called,
the fractal mode is changed to Julia and the fractal is created.
```
