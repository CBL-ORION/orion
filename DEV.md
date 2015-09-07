## Compile with coverage and profiling options

```shell
make clean
make BUILD_GCOV=1 BUILD_GPROF=1 all test
```

### Coverage output

```shell
make check-gcov-quick

make check-gcov-full

make check-lcov
```

## Profiling

```shell
PROGRAM="./.build/t/canary"
$PROGRAM
gprof $PROGRAM
```
