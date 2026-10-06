# Numerical Analysis — Refactored

This project is a refactoring of a numerical-analysis C program originally written in 2020 and present in the folder legacy

## Main changes

- Split the monolithic source file into modules.
- Separate numerical algorithms from the CLI.
- Replace magic constants with named configuration.
- Use `size_t` and 0-based indexing consistently.
- Replace fixed `float[10][10]` matrices with a dynamic `Matrix` type.
- Remove unnecessary iteration-history allocations.
- Return explicit `Status` values instead of calling `exit()` inside algorithms.
- Standardize root-finding results with `RootResult`.
- Replace `scanf()`/`fflush(stdin)` input handling with `fgets()` + parsing.
- Add unit tests for root-finding algorithms.
- Add compiler warnings and an AddressSanitizer/UndefinedBehaviorSanitizer target.

## Build

```bash
make
```

## Test

```bash
make test
```

## Sanitizers

```bash
make debug
./numerical_analysis-asan
```

## Important note

This is a refactoring plus a correctness cleanup. The original program contains
several indexing, loop-condition, allocation and convergence issues. The new
version intentionally does not preserve those bugs. Mathematical formulas are
implemented as explicit, testable functions.
