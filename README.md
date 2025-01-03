# Pathfinding with SDL2

A simple SDL project simulating a path finding algorithm in a 2D environment

## Preview
![img.png](img.png)

## How to Run

1. Clone the repository.
2. Open the project in CLion 2024.1.1 or any other C++ IDE that supports CMake.
3. Build and run the project.

## Features

- Grid-based path-finding simulation.
- Interactive mode to add or remove walls.
- Visual representation of the path to the target.

## How to play

- Use ESC to switch between edit and simulation mode.
- When in edit mode, left-click to add a cell or right-click to remove a wall.
- When in simulation mode, the agent will automatically find the shortest path to the target.

## Limitations

- The project currently uses absolute paths for asset loading, which might need to be adjusted on your system.
- The path-finding algorithm is simple and does not handle complex scenarios.

## Future Work

- Implement a more advanced path-finding algorithm like A*.
- Add support for multiple agents and targets.
- Improve the user interface and controls.

## Contributing

Contributions are welcome. Please fork the repository and create a pull request with your changes.
## Author
- [Toudonou](https://github.com/Toudonou)

## Useful Links
- Based on this tutorial : https://www.youtube.com/watch?v=UAlYELsxYfs&t=5s
- For SDL_image : https://416rehman.medium.com/setup-sdl2-image-for-clion-using-cmake-82affc3b6f7a
- Good : https://cpp-lang.net/

## License

This project is open source, under the MIT License.