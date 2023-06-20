# A Simple Chat App in C++

## Requirement
 - CMake
   - Linux
     ```bash
     sudo apt install cmake
     ```
   - Windows 
     Install with choco package manager
     ```bash
     choco install cmake
     ```
     Or, Download CMake windows installer on [here](https://cmake.org/download/)     

## Library
#### Installation Library
- Websocketpp (Added on path lib/websocketpp - no more action)
  - asd
- Boost (manual install)
  - Linux
    ```
    sudo apt install libboost-all-dev
    ```
  - Windows
    you can follow the installation guide on windows [here](https://robots.uc3m.es/installation-guides/install-boost.html#install-boost-windows) 


## Build
   - Change working directory to `{YOUR_PROJECT_PATH}/build`
     ```
     - cwd for build server
     ```bash
     cd build/server
     ```
   - CMake Build Initialization
     - cwd for build client
     ```bash
     cd build/client
     ```
     - Build client
     ```bash
     cmake ../ 
     ```
     or
     ```bash
     cmake ../ -DBUILD_TYPE_SERVER=OFF 
     ```
     - Build server
   - Make & linking file
     ```bash
     cmake ../ -DBUILD_TYPE_SERVER=OFF
     ```

## Run
Make sure, change working directory Like in step 1 on `build` if your current working directory in _C:/path/to/YOUR_PROJECT_PATH_

- On Linux
  ```bash
  main.so
  ```
- On Windows
  ```bash
  main.exe
  ```


## Build & Run
Make sure your current working directory like _[C|D]:/path/to/YOUR_PROJECT_PATH_
- Client
  - Initilize CMakeFiles
  ```
  cd build/client && cmake ../ && cd ../../
  ```
  - Compile source to binary file
  ```
  make -C ./build/client -s
  ```
- Windows