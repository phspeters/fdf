<h1 align="center">
	🏗️ fdf
</h1>

<h3 align="center">
  FDF is short for ’fil de fer’ in French which means ’wireframe model’.
</h3>

## 💡 About the project

The representation in 3D of a landscape is a critical aspect of modern mapping. For example, in these times of spatial exploration, to have a 3D representation of Mars is a prerequisite condition to its conquest.
As another example, comparing various 3D representations of an area of high tectonic activity will allow you to better understand these phenomena and their evolution, and as a result, be better prepared.
It’s your turn today to modelize some 3D magnificent landscapes, imaginary or not.

## 📝 Requirements

**Mandatory part:**

This project is about creating a simple wireframe model representation of a 3D landscape by linking various points (x, y, z) thanks to line segments (edges).
Your project must comply with the following rules:
- You must use the MiniLibX. Either the version available on the school machines, or installing it using its sources.
- You have to turn in a Makefile which will compile your source files. It must not relink.
- Global variables are forbidden.
- Your program has to represent the model in isometric projection.
- The coordinates of the landscape are stored in a .fdf file passed as a parameter to your program. Here is an example:
```
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  10 10 0  0  10 10 0  0  0  10 10 10 10 10 0  0  0
0  0  10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
0  0  10 10 0  0  10 10 0  0  0  0  0  0  0  10 10 0  0
0  0  10 10 10 10 10 10 0  0  0  0  10 10 10 10 0  0  0
0  0  0  10 10 10 10 10 0  0  0  10 10 0  0  0  0  0  0
0  0  0  0  0  0  10 10 0  0  0  10 10 0  0  0  0  0  0
0  0  0  0  0  0  10 10 0  0  0  10 10 10 10 10 10 0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
```
- Each number represents a point in space:
  - The horizontal position corresponds to its axis.
  - The vertical position corresponds to its ordinate.
  - The value corresponds to its altitude
- Your program has to display the image in a window.
- The management of your window must remain smooth (changing to another window, minimizing, and so forth).
- Pressing ESC must close the window and quit the program in a clean way.
- Clicking on the cross on the window’s frame must close the window and quit the
program in a clean way.
- The use of the images of the MiniLibX is mandatory

**Bonus part:**

- Include one extra projection (such as parallel or conic)!
- Zoom in and out.
- Translate your model.
- Rotate your model.
- Add one more bonus of your choice.

## 📋 Testing

To compile, navigate to the project directory and run:

```shell
$ make 
```

Then, execute the program with the path of the map chosen as your second argument:

```shell
$ ./fdf maps/t2.fdf
```

## 🕹️ Playing

- W, S -> X rotation
- A, D -> Y rotation
- Q, E -> Z rotation
- SHIFT + rotation -> Speed up rotation
- Up, Down, Left, Right -> Move
- -, = -> Zoom in or out
- Mouse Scroll -> Zoom in or out
- R -> Randomize background color
- F -> Disable background
- 1, 2, 3 -> Change projection
- Spacebar -> Reset position
