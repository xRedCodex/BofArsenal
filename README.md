# BOFArsenal

![Rust](https://img.shields.io/badge/made%20with-C++-pink)
![Platform](https://img.shields.io/badge/platform-windows-blueviolet)
![Forks](https://img.shields.io/github/forks/joaoviictorti/BOFS)
![Stars](https://img.shields.io/github/stars/joaoviictorti/BOFS)
![License](https://img.shields.io/github/license/joaoviictorti/BOFS)

The most extensive collection of BOFs (Beacon Object Files) tailored for Red Teams

## Table of Contents

* [Examples BOFS](#examples-bofs)
* [Build](#build)
    * [Build all](#build-all)
* [License](#license)

## Examples BOFS

1. [**env**](/Generic/env)
    - Retrieve and display environment variables of the target system.

2. [**dnscache**](/Generic/dnscache)
    - Enumerate and analyze the DNS cache entries on the target machine.

3. [**ipconfig**](/Generic/ipconfig)
    - Display detailed IP configuration and network adapter information.

4. [**enumhandles**](/Generic/enumhandles)
    - Enumerating file handles.

5. [**routeprint**](/Generic/routeprint)
    - Displays the system routing table.

## Build

### Build all

1. Generate the build files using CMake:
```bash
cmake -S . -B build
```

2. Compile all subprojects:
```bash
cmake --build build
```

This ensures that all directories with Makefiles are automatically built.

## License

This project is licensed under the MIT License. See the [LICENSE](/LICENSE) file for details.