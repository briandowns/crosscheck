# Crosscheck

[![Build and Deploy](https://github.com/briandowns/crosscheck/actions/workflows/main.yml/badge.svg)](https://github.com/briandowns/crosscheck/actions/workflows/main.yml/badge.svg)

Crosscheck is a very simple unit testing library for C code.

## Usage

Initialize the library

```c
cc_init();
```

Running tests

```c
cc_run(test_func);
```

Complete testing and print out results

```c
cc_complete();
```

## Test Functions

Test functions have 1 requirement. They need to return a `cc_result_t` type. This is done automatically for you using any of the provided "asserts" and a simple macro is provided (`CC_SUCCESS`)to be put at the end of the function. Check out the example.c file for a full exmaples.

Though not a requirement, all test function names should be prepended with "test_".

## Asserts

The library is meant to be as small and simple as possible so only 4 "asserts" are provided.

* CC_ASSERT_EQUAL
* CC_ASSERT_NOT_EQUAL
* CC_ASSERT_STRING_EQUAL
* CC_ASSERT_STRING_NOT_EQUAL

## Contributing

Please feel free to open a PR!

## Contact

Brian Downs [@bdowns328](http://twitter.com/bdowns328)

## License

BSD 2 Clause [License](/LICENSE).
