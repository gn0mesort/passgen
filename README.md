# passgen

`passgen` is a password generation utility for Linux based operating systems.

## Dependencies

`passgen` requires
[GNU Getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html)
to handle command line input. If Getopt is not available on your system
`passgen` won't work.

`passgen` also requires [`meson`](https://mesonbuild.com) and
[`ninja`](https://ninja-build.org) to build.

Generating HTML documentation requires
[`doxygen`](http://www.doxygen.nl/index.html).

## Building

```sh
$ meson build
$ meson configure build -Dbuildtype=release
$ ninja -C build
```

## Installing

```sh
$ ninja -C build install
```

## Generating Documentation

```sh
$ doxygen
```
or

```sh
$ ninja -C build doxygen
```
