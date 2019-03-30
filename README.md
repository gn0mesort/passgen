# passgen

Generates passwords. 

## Dependencies

`passgen` requires
[GNU Getopt](https://www.gnu.org/software/libc/manual/html_node/Getopt.html)
to handle command line input. If Getopt is not part of your C library 
`passgen` won't work.

`passgen` also requires [`meson`](https://mesonbuild.com) and
[`ninja`](https://ninja-build,org) to build.

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
