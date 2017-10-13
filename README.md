# particle-system

A particle system written in C++ that uses GPU.

## Libraries

* OpenGL
* OpenGL Mathematics (glm)
* OpenCL
* Simple DirectMedia Layer (SDL)

## Usage

In your terminal:  
```sh
git clone https://github.com/4quet/particle_system.git
cd particle_system
make
```
  
Launch using:  
`./particle_system <amount>` where `<amount>` is a number between **100** and **5000000**.

### Key bindings

* **R**: Reset to initial shape (sphere or cube)>
* **TAB**: Switch between shapes (sphere or cube). Only works while on inital shape.
* **Left Mouse Button**: Hold to enable a gravity point.
* **Right Mouse Button**: Create a particle emitter.
* **W**: Move forward.
* **S**: Move backward.
* **A**: Strafe left.
* **D**: Strafe right.
* **+**: Increase movement speed.
* **-**: Decrease movement speed.
* **RETURN**: Generate random particles colors.
* **B**: Switch background color (black or white).
* **F**: Toggle FPS counter in window title.
* **SPACE**: Toggle pause.
* **ESCAPE**: Quit.

## Screenshots

![screenshot1](./screenshots/screenshot1)
![screenshot2](./screenshots/screenshot2)
![screenshot3](./screenshots/screenshot3)
![screenshot4](./screenshots/screenshot4)
