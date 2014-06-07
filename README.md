# Robospace

## Build

Build options:

* `TEST` = ON | OFF. Build tests. Defaults to OFF.
* `CMAKE_BUILD_TYPE` = Debug | Release.

Dependencies:

* cmake
* >=lua-5.1
* >=boost-1.54 (coroutine)
* gtest (if TEST=ON)

```
mkdir build
cd build
cmake .. -DTEST=ON|OFF -DCMAKE_BUILD_TYPE=Debug|Release
make -j <num-jobs>
```

where `<num_jobs>` is number of jobs to run in parallel.

## Run tests

```
make test
```

## Run cppcheck

```
make check
```

## Run clang static analyzer

```
mkdir analyze
cd analyze
scan-build cmake .. -DCMAKE_BUILD_TYPE=Debug -DTEST=ON
scan-build make
```
