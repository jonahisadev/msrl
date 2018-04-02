# My Simple Runtime Library (MSRL)

This is my simple runtime library.

## About

I was bored with some of my projects so I decided to challenge myself
by making some sort of supplement or replacement of the C runtime
library. Because that's fun.

This is far from being actually helpful. Below is a to-do list of
things I'd like to add to it that would allow independence of the
standard C library.

## Using

If for some bizzare reason you'd like to use this library, you can
clone the repository and include either individual headers or the
main header `msrl.h` which includes all the other headers and
some extra helper functions (which may move to a separate file
later on in the development process)

## To Do

- [x] Memory (msrl_mem.h)
- [ ] Strings (msrl_string.h)
- [ ] IO (msrl_io.h)
- [ ] Lists (msrl_list.h)