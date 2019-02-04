# [`trie`](https://en.wikipedia.org/wiki/Trie) implementation for a specific use-case

*This is an implementation for a very specific use case, don't copy it
unless you understand it and are sure it applies to you!*

If you do want it though, this code is MIT licensed, so you should be
able to use it anywhere you want :)

## Use case

Our use case is a pre-sorted list of keys, and a single pointer as
a value to be retrieved.

All the keys start with the same prefix, then have a variable middle,
and sometimes a variant with a suffix added.

Example:
- eglCreateImage
- eglCreateImageKHR
- eglCreatePbufferSurface
- eglCreatePixmapSurface
- eglCreateWindowSurface
- eglDestroyImage
- eglDestroyImageKHR
- eglDestroySurface

## Our restrictions

We want to build the trie at build-time, so the the run-time cost is
only the fetch cost, which is constant.

The main code is in `C`, but we can use `python` to generate code at
build-time.

## Testing

To build and test this code, you need to have a C compiler, Python, and
[Meson](https://mesonbuild.com).

```
mkdir build
cd build
meson ..
ninja test
```
