# ComputerGraphics_OpenGL
This repository is for everyone who is learning OpenGL. You can learn with me.

## Setting Up The Code

This guide will walk you through cloning the repository and setting up an OpenGL codebase for development.

## Quick Setup Guide

This guide will help you quickly set up your development environment by copying the pre-configured dependencies into your project folder.

### Setup Instructions

1. **Clone the Repository**:
    - Clone this repository to your local machine:

    ```bash
    git clone https://github.com/Xplosiveginger/ComputerGraphics_OpenGL.git
    ```

    - If you are using github desktop, you can straight up just clone the repo.

2. **Open the Dependencies Zip File**:
    - I have provided you with [glfw file](glfw-3.3.9.bin.WIN64.zip) that contains the headers and the specific libraries for different visual studio versions.
    - This file will be cloned along with the repo.
    - Navigate to your cloned repository and open the file called `glfw-3.3.9.bin.WIN64.zip`. You can open it with any software of your choice.

3. **Extract and Copy Dependencies**:
    - Inside the '.zip' file, you'll find libraries for different versions of Visual Studio.
    - Choose the appropriate library folder for your version of Visual Studio (e.g., VS2019, VS2022).
    - for example if you are using the visual studio 2022 version, You need to choose `lib-vc2022` folder.
    - Copy the entire library folder.
    
4. **Paste into the Project**:
    - Navigate to the "Dependencies" folder in your cloned repository.
    - Paste the copied library folder into the "Dependencies" folder.
    - Rename the pasted folder to "lib".

5. **Change Version**:
    - If you are using Visual Studio 2022, You do not need to do this step.
    - Now Open your `OpenGL.sln` file in visual studio.
    - You'll have 2 projects.
          `1. WindowCreation and 
          2. TriangleRender`
    - For both of these projects right click and go to the properties.
    - Under `Configuration Properties` click on the `General` tab.
    - In the `General Properties` you'll see a property called `Platform Toolset`.
    - By default it will be set to `v(143)` (This is because I'm using visual studio 2022 to run this project.)
    - You can click on the field and use the dropdown and select your Visual Studio version there.

7. **You're Ready to Go!**:
    - Your project is now configured with the necessary dependencies.
    - You can start working on your project without worrying about setting up dependencies.

## Additional Notes

- **Download Files**: If you don't want to clone the repository, You can always just download the code in a `.zip` file.
- **Visual Studio Versions**: Make sure to choose the correct library folder corresponding to your version of Visual Studio to avoid compatibility issues.
- **Troubleshooting**: If you encounter any issues with dependencies or setup, feel free to reach out for assistance.

## Documentation

- **OpenGL Documentation**: Refer to the [OpenGL documentation](https://www.opengl.org/documentation/) for learning OpenGL basics and advanced techniques.
- **GLFW Documentation**: Explore the [GLFW documentation](https://www.glfw.org/docs/latest/) for detailed information on GLFW functions and usage.
- **GLAD Documentation**: Refer to the [GLAD documentation](https://github.com/Dav1dde/glad) for understanding GLAD usage and OpenGL function loading.

