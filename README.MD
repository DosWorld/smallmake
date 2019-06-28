# Make

There is MAKE utility for Small C by J. Hendrix.
Good compiler, but toolchain definitly must be enhanced.

The second reason to recreate this utility - absent
"make" for DOS real mode (16 bit). DJGPP purpose DPMI tools.

This "make" does not support variables.

Source code 100% wroten in Small C (with Assembler inlines).

# Makefile format

    target1: [dependency1] [.. dependency2]
           [build_command_1]
           [.. build_command_2]

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

## Restrictions

Max target count - 1024

Max MAKEFILE size - 16KB

# License

Public domain
