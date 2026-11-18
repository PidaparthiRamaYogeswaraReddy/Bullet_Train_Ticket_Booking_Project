# Bullet Train Ticket Booking System

A first-semester C programming group project that demonstrates a simple
console-based train ticket booking system.

## Project overview

The project is divided into four modules:

1.  **Train & Route Module** -- stores train and route information and
    supports train searching.
2.  **Passenger & Booking Module** -- collects passenger details,
    accepts journey details, and handles booking and fare calculation.
3.  **Ticket & PNR Module** -- generates and displays ticket information
    and supports ticket-related operations.
4.  **Cancellation & Admin Module** -- handles ticket cancellation,
    refund calculation, administrator access, booking records, and fare
    updates.

## Project files

Keep all source files together in the same project folder:

``` text
Bullet_Train_Ticket_Booking_Project/
├── main.c
├── railway.h
├── common.c
├── module1_train.c
├── module2_booking.c
├── module3_ticket.c
├── module4_admin.c
└── README.md
```

If your downloaded copy has additional files, keep them in the folder
too.

## Requirements

You need a C compiler and (recommended) Visual Studio Code.

### macOS

1.  Open Terminal.

2.  Install Apple's command-line developer tools if they are not already
    installed:

    ``` bash
    xcode-select --install
    ```

3.  Check the compiler:

    ``` bash
    clang --version
    ```

### Windows

Install a GCC toolchain, such as **MSYS2 with MinGW-w64**, and make sure
`gcc` is available in your terminal's PATH.

Check the installation:

``` bash
gcc --version
```

## Download the project

1.  Open the GitHub repository.
2.  Click the green **Code** button.
3.  Select **Download ZIP**.
4.  Extract the ZIP file.
5.  Open the extracted folder in VS Code.

Alternatively, if Git is installed, clone the repository:

``` bash
git clone https://github.com/bsrisaiharsha/Bullet_Train_Ticket_Booking_Project.git
```

## Compile and run

Open the VS Code terminal **inside the project folder**.

### macOS (Apple Clang)

Compile all C source files together:

``` bash
clang -std=c99 -Wall -Wextra main.c common.c module1_train.c module2_booking.c module3_ticket.c module4_admin.c -o railway
```

Run:

``` bash
./railway
```

### Windows (GCC)

Compile:

``` bash
gcc -std=c99 -Wall -Wextra main.c common.c module1_train.c module2_booking.c module3_ticket.c module4_admin.c -o railway.exe
```

Run in PowerShell:

``` powershell
.\railway.exe
```

**Important:** Compile all six `.c` files in the same command. Compiling
only `main.c` will not link the other modules.

## Working with GitHub

If you are a project collaborator:

1.  Accept the repository invitation.

2.  Clone the repository to your computer.

3.  Before starting work, get the latest changes:

    ``` bash
    git pull
    ```

4.  Edit the source file assigned to you.

5.  Review your changes:

    ``` bash
    git status
    ```

6.  Stage, commit, and push:

    ``` bash
    git add .
    git commit -m "Describe your changes"
    git push
    ```

Coordinate with the team before editing shared files. Avoid having
multiple members change the same file at the same time. For a larger
team workflow, use separate branches and pull requests.

## Notes

-   Keep `main.c`, `railway.h`, `common.c`, and all four module source
    files together.
-   Run the compile command again after changing source code.
-   Booking data may be stored locally by the program. A data file on
    one teammate's computer is not automatically shared with the others.
-   Do not commit passwords, private keys, access tokens, or other
    confidential information to GitHub.
-   If compilation fails, check that the filenames in the command match
    the files in your folder.

## Project repository

https://github.com/bsrisaiharsha/Bullet_Train_Ticket_Booking_Project
