# Make

There is MAKE tool for Small C by J. Hendrix.
Good compiler, but toolchain definitly must be enhanced.

The second reason to recreate this utility - absent
MAKE for DOS 16-bit (real mode). DJGPP offers just DPMI tools.

This MAKE does not support variables - smallest as possible.

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

By default, MAKE start search EXE and COM in current
directory and in PATH.

If found - run.

If not found (it could be BAT or built-in command like
COPY or DEL) - try execute

     COMMAND.COM /C build_command

(Path to COMMAND.COM will be received from COMSPEC env variable)


So, if You wrote "cc mycool.c" it could start

     K:\SMALLC20\CC.EXE mycool.c

or

     K:\SMALLC22\CC.EXE mycool.c

depends to directory order in PATH.

## How to build

Just type

    make

Must be in PATH:

* SmallC 2.2
* ASM (Small Assembler)
* VAL (linker)
* UPX (executable file compressor)

Some of this tools you can download from https://github.com/DosWorld/smallc

## Restrictions

Max target count - 1024

Max MAKEFILE size - 16KB

# License

Public domain
