[github.com/](https://github.com/mistlure/csv-db)

# CSV Database Manager

A lightweight, terminal-based tool written in C for managing and analyzing CSV files. It supports statistical calculations, editing (adding rows/columns), and offers both a console command mode and an interactive UI menu.

## Features

* **Dual Modes**:
    * **Console Mode**: Type commands manually (shell-style).
    * **Interactive Menu**: User-friendly UI with numbered options.
* **Statistical Analysis**: Calculate `Average`, `Sum`, `Min`, and `Max` for any column.
* **Editing**: Add new rows or columns to the database.
* **CSV Parsing**: Handles header parsing and data splitting automatically.
* **Colorful UI**: Uses ANSI escape codes for a modern terminal look.

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