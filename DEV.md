## Compile with debug flags

```shell
make clean
make BUILD_DEBUG=1 all test
```

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

### Profiling

#### Runtime profiling with gprof

```shell
PROGRAM="./.build/t/canary"
$PROGRAM
gprof $PROGRAM
```

#### Memory profiling with Valgrind

Need to make sure that ASAN is disabled.

```shell
PROGRAM="./.build/t/canary"
make BUILD_ENABLE_ASAN=0 all test
valgrind $PROGRAM
```
