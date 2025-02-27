# dagdaOS

dagdaOS is a simple operating system written as an exercise in C and low-level programming.

![image](https://github.com/user-attachments/assets/236ca8af-7746-47eb-a260-befdb7a0f858)


## Description

dagdaOS is a simple operating system written as an exercise in C and low-level programming. A lot of the shell commands take inspiration from the Scottish Gaelic language. This operating system is not meant to replace anyones current operating system.

## Getting Started

### Dependencies
* CMake
* NASM
* GCC

### Installing

* Download the source files
* Open a terminal
* Now run:
* ```
  make clean
  make
  ```
* The iso will be built in the "bin" folder

### Executing program

* Running using QEMU:
```
qemu-system-i386 -cdrom bin/dagdaOS.iso
```
* Running from disk:
```
make run-disk
```

dagdaOS hasn't yet been tested on physical hardware :)

## Authors

Euan O'Rourke  
[@sexyscrumm](https://twitter.com/sexyscrumm)


## License

This project is licensed under GPL v3 (GNU General Public License v3.0). For more information go to the LICENSE file.

## Acknowledgments

Inspiration, code snippets, etc.
* [awesome-readme](https://github.com/matiassingers/awesome-readme)
* [cavOS](https://github.com/malwarepad/cavOS/tree/master)
* [printf implementation](https://github.com/mpaland/printf)
