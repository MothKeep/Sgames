# Sgames

**Sgames** is a lightweight application featuring a small collection of classic, traditional minigames.  
Developed in **C++** using the **SDL3** library, this project serves as a learning platform for exploring game development concepts and practicing modern C++ programming.

### Included Minigames

- Tic Tac Toe  
- Pong  
- Arkanoid  

## Build Instructions

### Prerequisites

Ensure the following dependencies are installed on your system:

- **CMake** (version 3.16 or higher)
- A **C++ compiler** with C++17 support
- **SDL3**
- **SDL3_image**
- **SDL3_ttf**

### Build Steps

Follow these steps to build the project:

```bash
# Clone the repository
git clone https://github.com/yourusername/Sgames.git
cd Sgames

# Create and navigate to the build directory
mkdir build
cd build

# Run CMake to configure the project
cmake ..

# Build the executable
cmake --build .
```

The compiled executable will be located in the `build/` directory with the name `Sgames`.

## Running the Application

After building, you can run the program from the build directory:

```bash
./Sgames
```
