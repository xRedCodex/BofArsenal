# BOFArsenal

![C++](https://img.shields.io/badge/made%20with-C++-pink)
![Platform](https://img.shields.io/badge/platform-windows-blueviolet)
![Forks](https://img.shields.io/github/forks/xRedCodex/BofArsenal)
![Stars](https://img.shields.io/github/stars/xRedCodex/BofArsenal)
![License](https://img.shields.io/github/license/xRedCodex/BofArsenal)

The most extensive collection of BOFs (Beacon Object Files) tailored for Red Teams

## Table of Contents

* [Examples BOFS](#examples-bofs)
* [Build](#build)
    * [Build all](#build-all)
* [License](#license)

## Generics

| Name            |                                                              Description                                                               |
|-----------------|:--------------------------------------------------------------------------------------------------------------------------------------:|
| **env**         |                                    Retrieve and display environment variables of the target system.                                    |
| **dnscache**    |                                   Enumerate and analyze the DNS cache entries on the target machine.                                   |
| **enumhandles** |                                                       Enumerating file handles.                                                        | 
| **ipconfig**    |                                   Display detailed IP configuration and network adapter information.                                   |
| **routeprint**  |                                                   Displays the system routing table.                                                   |  
| **selfdelete**  |                                                 Self delete the agent file in the disk                                                 |
| **screnshoot** | Take a screenshot and send to C2 |
| **rmcallback**  | Remote the Instrumentation Callback     |
| **getcallback** | Check if Instrumentation Callback is set | 
| **firewalruleadd** | Add rule to firewall |

## Jmp-Exec (lateral moviment)

| Name     |  Description  |
|----------|:-------------:|
| **wsman** | Executes the command in the remote machine via winrm |
| **scm** | Create service in the remote machine via open service control manager |
| **wmi** | Create the process in the remote machine via wmi |

## Persistence

| Name     |  Description  |
|----------|:-------------:|
| **autostart** | Use registry to persist file execution in the machine start |

## Build

### Build all

1. Generate the build files using CMake:
```bash
cmake -B build -G "Unix Makefiles"  
```

2. Compile all subprojects:
```bash
cmake --build build
```

This ensures that all directories with Makefiles are automatically built.

## License

This project is licensed under the MIT License. See the [LICENSE](/LICENSE) file for details.
