# Asynchronous IO Examples with libuv

This repository contains examples of asynchronous I/O operations using the `libuv` library. It includes an echo server and a file reader, demonstrating non-blocking network and file I/O.

## Prerequisites

Before you can build and run the programs, you must install `libuv`. This library provides the core functionality for asynchronous operations.

### Installing libuv

#### On Ubuntu/Debian:

```bash
sudo apt-get update
sudo apt-get install libuv1-dev
```

#### On CentOS/Fedora:

```bash
sudo yum install libuv-devel
```

#### On macOS (using Homebrew):

```bash
brew install libuv
```

#### Building from Source:

If you prefer to build `libuv` from source:

```bash
git clone https://github.com/libuv/libuv.git
cd libuv
sh autogen.sh
./configure
make
make check
sudo make install
```

## Repository Contents

- `echo_server.c`: An echo server that reads from clients and sends back what it reads.
- `file_async_read.c`: Asynchronously reads from a file named `example.txt` and prints its contents to the standard output.

## Compilation

To compile the examples, run the following commands in your terminal:

```bash
make all
```

This command will compile both the echo server and the file reading example using the provided Makefile.

## Running the Programs

To run the echo server:

```bash
make run_echo_server
```

To run the file reading example (ensure you have an `example.txt` file in your directory):

```bash
make run_file_async_read
```

## Cleanup

To clean up executable files and other intermediates:

```bash
make clean
```

## Additional Information

- Make sure that the file `example.txt` exists in the same directory as `file_async_read` before running it.
- The echo server listens on port 8080 by default. You can connect using a network tool like `telnet` or `socat` to test.
