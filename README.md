# Graph Visualization Program

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Upcoming Features](#upcoming-features)
- [Contributing](#contributing)
- [License](#license)

## Description
This C++ program is designed for creating and visualizing graphs using the SDL library. It allows users to interactively add nodes, connect them with edges, and visualize the resulting graph on a canvas. The project aims to serve as a foundation for more advanced graph-related features.

## Features
- **Node Insertion Mode:** Toggle this mode to add nodes by clicking on the canvas.
- **Node Connection Mode:** Switch to this mode to connect nodes by clicking on them.
- **Interactive Canvas:** The program offers an interactive canvas for node and edge manipulation.
- **Graph Visualization:** Nodes are displayed as circles, and edges are represented as lines connecting nodes.
- **Clean Exit:** Users can exit the program gracefully by pressing the 'Escape' key.

**Function Mode:**
- **Adjacency Matrix Creation:** In function mode, press 'a' to create an adjacency matrix for the graph.
- **Node Degree Calculation:** In function mode, press 'd' to calculate and print the degree of each node.
- **Node Removal Mode:** Enter this mode to remove nodes and associated edges by clicking on them.

## Requirements
To run this program, you'll need the following:
- C++ compiler (C++11 or later)
- SDL library (Simple DirectMedia Layer)
- SDL_ttf library (for text rendering)

## Getting Started
1. Clone this repository to your local machine.
2. Ensure that you have the required libraries (SDL and SDL_ttf) installed.
3. Compile the program using your C++ compiler (e.g., `g++ -o graph_program main.cpp -lSDL2 -lSDL2_ttf`).
4. Run the compiled binary.

## Usage
- Press 'n' to enter Node Insertion Mode. Click on the canvas to create nodes.
- Press 'c' to enter Node Connection Mode. Click on two nodes to create an edge.
- Press 'f' to enter function Mode. 
    - Press 'a' in Function Mode to create an adjacency matrix.
    - Press 'd' in Function Mode to calculate and print the degree of each node.
- Press 'Escape' to exit any active mode and return to the default mode.
- Click the 'X' button or press 'Ctrl + C' to exit the program.

## Upcoming Features
The program's development is ongoing. Upcoming features and improvements include:
- Support for weighted graphs.
- Implementation of spanning tree algorithms.
- Enhanced rendering for improved visualization.

## Contributing
Contributions, bug reports, and feature requests are welcome. Feel free to submit issues or pull requests on the [GitHub repository](https://github.com/your-repo-link).

## License
This project is licensed under the MIT License.

