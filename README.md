# Game of Life

## Instructions to Compile and Run

To compile the Game of Life program, use the following command in your terminal:

```bash
make
```

Once the compilation is complete, you can run the program with:

```bash
./game_of_life <config_file>
```

Replace `<config_file>` with the path to your initial configuration file.

## Using Initial Configuration Files

The Game of Life accepts initial configuration files that define the starting state of the board. 
You can create your own configuration files or use the provided examples.

## Control Keys

- Press **A** to increase the speed.
- Press **Z** to decrease the speed.
- Press **Space** to exit the program.

## Requirements

Make sure to have the following library installed:
- **ncurses**: This library is required to run the Game of Life program. You can install it using your package manager. For example:
  - On Ubuntu:
    ```bash
    sudo apt-get install libncurses5-dev libncursesw5-dev
    ```
  - On macOS:
    ```bash
    brew install ncurses
    ```
