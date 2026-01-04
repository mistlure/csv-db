# CSV Database Manager

A lightweight, terminal-based tool written in C for managing and analyzing CSV files. It supports statistical calculations, editing (adding/deleting rows, adding columns), and offers both a console command mode and an interactive UI menu.

## Build & Installation

Prerequisites: `gcc` and `make`.

1.  **Compile the project:**
    ```bash
    make
    ```
    This generates the `databaze` executable.

2.  **Clean build files (optional):**
    ```bash
    make clean
    ```

## Usage

The program requires an input CSV file and an output path for saving results.

### Basic Syntax
```bash
./databaze --input <source.csv> --output <destination.csv>