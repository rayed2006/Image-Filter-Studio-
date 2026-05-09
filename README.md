# Image-Filter-Studio-
FAST semester 2 final project 2026
# Image Filter Studio (C++)

A robust console-based image processing application built in C++. This project was designed as a showcase of Object-Oriented Programming (OOP) concepts, specifically focusing on manual memory management and runtime polymorphism.

## Key Features
- **Real Image I/O**: Loads and saves real `.jpg` and `.png` files using the `stb` library.
- **Dynamic Pixel Grid**: Manages a 2D array of Pixel objects using dynamic memory allocation (Double Pointers) on the heap.
- **Filter Pipeline**: Chain multiple filters together (Grayscale, Box Blur, Flip, etc.) using method chaining.
- **ASCII Preview**: Generates a real-time text-art approximation of the image in the terminal.

## OOP Concepts Used
- **Encapsulation**: Private data members for Pixel and Image classes with strict getter/setter access.
- **Inheritance**: Abstract base classes for `User` and `Filter` hierarchies.
- **Multiple Inheritance**: `Image` class implements both `Saveable` and `Previewable` interfaces.
- **Polymorphism**: Virtual functions used for the Filter logic and User login permissions.
- **Memory Management**: Full manual control over heap memory (No STL containers like `vector` or `map` used).

##  How to Build
Compile all files using g++:
```bash
g++ *.cpp -o ImageStudio
