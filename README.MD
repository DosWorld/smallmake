# Make

There is `MAKE` tool for `Small C by J. Hendrix`.
Good compiler, but toolchain definitly must be enhanced.

The second reason to recreate this utility - absent
`MAKE` for DOS 16-bit (real mode). DJGPP offers just DPMI-based
tools.

This `MAKE` does not support variables - smallest as possible.
`MAKE` is real small - just 5KB on your hard drive!

Source code 100% wroten in Small C (with Assembler inlines).

# Makefile format

    target1: [dependency1] [.. dependency2]
           [build_command_1]
           [.. build_command_2]

    target2: [dependency2] [.. dependency3]
           [build_command_x]
           [.. build_command_z]

By default, start build first target.

## Notes about command execution in MS-DOS.

By default, `MAKE` start search EXE and COM in current
directory and in `PATH`.

If found - run.

If not found (it should be BAT or built-in command like
COPY or DEL) - try execute

     COMMAND.COM /C build_command

Path to `COMMAND.COM` will be received from `COMSPEC` env variable


So, if You wrote "cc mycool.c" it could start

     K:\SMALLC20\CC.EXE mycool.c

or

     K:\SMALLC22\CC.EXE mycool.c

depends to directory order in `PATH`.

## How to build

Just type

    make

Must be in `PATH`:

* Small C 2.2
* ASM (Small Assembler)
* VAL (linker)
* UPX (executable file compressor)

Some of this tools you can download for free from

* My Small-C "museum": https://github.com/DosWorld/smallc
* UPX official site: https://upx.github.io/

### Exesize

By default, VAL-linker put 0xFFFF into `max memory` field (in exe-header).
It is means - DOS will allocate all available memory for programm, when
start it. It is bad choice, if you want start execute another programm.
Child process will be crashed with "no memory" error. So, I wrote
`exesize.exe` - patch for `MAKE`'s exe header, to avoid this problem.
This patch must be applied to `make.exe` after linking.

## Restrictions

Max target count - 1024

Max MAKEFILE size - 16KB

# License

Public domain (The Unlicense http://unlicense.org)
