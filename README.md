# Spica

## About

Spica is a prototype game engine developed from scratch in C++ as part of [UPC's Master's degree in advanced programming for AAA video games](https://www.talent.upc.edu/ing/estudis/formacio/curs/201200/master-advanced-programming-aaa-video-games/).

Being a prototype, the engine has limited functionality (described in the [Functionality](#Functionality) section); mainly, it allows the user to load an inspect an `.fbx` model. That said, a lot of care has been placed in making the engine well organized and extensible in the hopes it can serve as a base for the engine that will be developed throughout the Master's degree.

## Author

[Gerard Queralt](https://github.com/gerard-queralt)

After finishing my Informatics Engineering degree, specializing in Software Engineering, I enrolled on the [master](https://www.talent.upc.edu/ing/estudis/formacio/curs/201200/master-advanced-programming-aaa-video-games/) in the hopes of being able to joint the video game industry and help creating some of the worderful experiences games can bring.

## Usage

Spica has very intuitive controls to navigate the scene.

- While holding **Right click**, you can move freely with WASD and move the camera around with the mouse. Holding **LShift** makes you move twice as fast.

- You can zoom with the **mouse wheel**.

- While holding **Alt + Left click** you can orbit around the loaded geometry.

- You can focus the camera on the loaded geometry by pressing **F**.

## Functionality

### Loading FBX models

Spica allows you to load an `.fbx` model from anywhere in your system. Simply drag and drop the file onto the engine, and it will take care of everything for you!

Additionally, Spica can give you information about the loaded model and its meshes, like the number of triangles in each mesh.

### Scene as window

Even though it was outside of the scope for this deliverable, the scene where the geometry is loaded is also a dockable window. This allows you to easlily resize it, move it around and even disable it.

To do so, the scene is rendered into a texture, which is in turn rendered into an ImGui window. If you'd like to see the code behind it:

- [ModuleRenderer, where the texture and the necessary buffers are created, updated and rendered into](https://github.com/gerard-queralt/Spica/blob/main/Spica/Source/Modules/ModuleRender.cpp).

- [WindowScene, where the texture is passed to ImGui](https://github.com/gerard-queralt/Spica/blob/main/Spica/Source/Models/Windows/EditorWindows/WindowScene.cpp).

### Integrated console

Spica has an integrated console that logs what it's doing in the background, like the initialization of libraries or the steps when loading a model.

### Hardware detection

The engine can show you information about your system or the graphics card in which it's running.

### Configuration

Almost all parameters of the program can be changed through its graphical interface, be it the window's size, the maximum FPS, or the shaders used in rendering.

## Known issues

- In some devices, loading multiple FBXs will cause the engine to stop rendering completely. However, in some others it keeps working just fine, so the cause hasn't been identified yet.

- When resizing the window, the camera's position does not change, so even though the aspect ratio is correct it can look weird (for example, when setting the window to fullscreen). A workaround has not been found as of yet.

## Additional comments

Even though the functionality of the engine is, quite frankly, limited, as stated before, I'm very proud of my architectural work. I tried to organize and separate the different functions to make the code follow the SOLID design principles. This also made it so there is little repeated code, so changes can be made quickly and propagate in a transparent manner. Also, the different class hierarchies used - most notably [Window](https://github.com/gerard-queralt/Spica/tree/main/Spica/Source/Models/Windows) - allow for easy extension of the software with minimal work required.

## Link

This project is hosted in [this GitHub repository](https://github.com/gerard-queralt/Spica).

## License

[MIT](https://choosealicense.com/licenses/mit/)