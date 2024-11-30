# Virtual Pet Adoption Center

A C++ console-based application that simulates a virtual pet adoption center. The project demonstrates object-oriented programming by allowing users to interact with virtual pets, manage their well-being, and handle adoption-related activities.

## Project Purpose

This project was developed in C++ programming to apply object-oriented design to a small interactive application. It brings together class design, inheritance, collections, and file handling in a virtual pet adoption scenario.

## Features

- **Pet Management:** Maintain and interact with virtual pets.
- **Pet Adoption:** Manage the adoption of available pets.
- **Pet Care:** Track pet health and happiness.
- **Inheritance:** Use a `MythicalPet` class to represent a specialized type of pet.
- **Polymorphism:** Use base-class pointers to work with different pet types.
- **File Handling:** Save adopted pets and deceased pets to text files.
- **Dynamic Memory and Collections:** Manage pet objects through pointers and a collection of pets.

## Concepts Demonstrated

- Classes and objects
- Encapsulation
- Inheritance and polymorphism
- Dynamic memory allocation
- C++ pointers and vectors
- File input/output
- Basic application and state management

## Technologies Used

- **Language:** C++
- **IDE:** Code::Blocks
- **Standard Library:** `vector`, file streams, and other standard C++ features

## Getting Started

### Prerequisites

- A C++ compiler, such as GCC
- Code::Blocks or another C++ development environment

### Running the Project

1. Clone or download this repository.
2. Open the `.cbp` project file in Code::Blocks.
3. Build the project.
4. Run the compiled application and follow the console prompts.

Alternatively, compile `main.cpp` from a terminal if the project is self-contained:

```bash
g++ main.cpp -o VirtualPetAdoptionCenter
```

Run on Windows:

```bash
VirtualPetAdoptionCenter.exe
```

## Data Files

The application generates text files to store pet information, including:

- `adopted_pets.txt`
- `dead_pets.txt`

These files will be created when the application runs, depending on whether the information of adopted and un-adopted pets are saved.



