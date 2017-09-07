# iSVD
Integrated Singular Value Decomposition (iSVD)

## Information

### Git
* https://github.com/emfomy/isvd

### Documentation
* http://emfomy.github.io/isvd

### Author
* Mu Yang <<emfomy@gmail.com>>

## Requirements
* [CMake](https://cmake.org) 2.8+ (CMake 3+ recommended).
* C/C++ compiler with C99/C++98 standard support ([GCC](https://gcc.gnu.org) 4.4+ recommended).
* [BLAS](http://www.netlib.org/blas) & [LAPACK](http://www.netlib.org/lapack) library (Used for multi-core parallelization).
* MPI Library v2.2+ ([MPICH](http://www.mpich.org) or [OpenMPI](https://www.open-mpi.org)).

### Optional
* [Intel&reg; Math Kernel Library](https://software.intel.com/en-us/intel-mkl) (**Recommended** for better performance, used for BLAS & LAPACK).
* [MAGMA](http://icl.cs.utk.edu/magma/) 2+ (Used for BLAS & LAPACK with GPU support).
* [OpenMP](http://openmp.org) Library (**Recommended** for better performance, used for multi-thread parallelization).
* [Google Test Library](https://github.com/google/googletest) (Used for code testing).
* [DOxygen](http://www.stack.nl/~dimitri/doxygen/) (Used for documentation).

## Installation

Please use the following commands to create Makefiles

```
mkdir build
cd build
cmake <path-to-source>
```

### Options

Use the following command to set options

```
ccmake <path-to-source>
```

The following table are the main options

| Option                 | Detail                             | Note                           |
|------------------------|------------------------------------|--------------------------------|
| `ISVD_BLAS`            | the selection BLAS/LAPACK library. | Options: `BLAS/MKL`            |
| `ISVD_BUILD_DEMO`      | build demo codes.                  |                                |
| `ISVD_BUILD_DOC`       | build documentation.               |                                |
| `ISVD_BUILD_LIB`       | build libraries.                   |                                |
| `ISVD_BUILD_TEST`      | build unit tests.                  |                                |
| `ISVD_INDEX_TYPE`      | the selection index type.          | Options: `32/64`               |
| `ISVD_OMP`             | the selection OpenMP library.      | Options: `OFF/GOMP/IOMP`       |
| `ISVD_USE_GPU`         | enable GPU support.                |                                |
| `ISVD_VERBOSE_TEST`    | enable verbose unit tests.         |                                |
| `GTEST_ROOT`           | the root path of Google Test.      | Require `ISVD_BUILD_TEST`      |
| `INTEL_ROOT`           | the root path of Intel libraries.  | Require `ISVD_BLAS = MKL`      |
| `MKL_ROOT`             | the root path of Intel MKL.        | Require `ISVD_BLAS = MKL`      |
| `MPI_PROCS`            | the number of MPI processes.       | Only used in demo codes.       |
| `OMP_THRDS`            | the number of OpenMP threads.      | Only used in demo/check codes. |

### Makefile

The following table are the main make rules

| Command        | Detail                         |
|----------------|--------------------------------|
| `make all`     | build all libraries            |
| `make install` | install package                |
| `make check`   | build and run unit tests       |
| `make doc`     | build documentation            |
| `make help`    | display make-rules             |

## Usage

* Define `ISVD_USE_ILP64` before include `isvd.h` to use 64-bit integer.
* All 64bit libraries and executables are named with suffix "`_64`".

### Libraries

Please link exact one library of each kind.

* Correct
  * `gcc test.c -I<include-path> -L<library-path> -Wl,-rpath <library-path> -lisvd_core -lisvd_la_mkl_iomp -lisvd_gpu_magma`
  * `gcc test.c -I<include-path> -L<library-path> -Wl,-rpath <library-path> -lisvd_core -lisvd_la_blas -lisvd_gpu_none`
* Wrong
  * `gcc test.c -I<include-path> -L<library-path> -Wl,-rpath <library-path> -lisvd_core`
    * (Some kind of libraries are not linked)
  * `gcc test.c -I<include-path> -L<library-path> -Wl,-rpath <library-path> -lisvd_core -lisvd_la_blas -lisvd_gpu_magma -lisvd_gpu_none`
    * (Some kind of libraries are linked multiple times)

| Name                   | Kind           | Detail                                 |
|------------------------|----------------|----------------------------------------|
| `isvd_core`            | Core           | Core routines                          |
| `isvd_la_blas`         | Linear Algebra | Sequential Plain BLAS                  |
| `isvd_la_mkl`          | Linear Algebra | Sequential Intel MKL                   |
| `isvd_la_mkl_gomp`     | Linear Algebra | Parallel Intel MKL using GNU OpenMP    |
| `isvd_la_mkl_iomp`     | Linear Algebra | Parallel Intel MKL using Intel OpenMP  |
| `isvd_gpu_none`        | GPU            | No GPU                                 |
| `isvd_gpu_magma`       | GPU            | MAGMA GPU                              |

## Q&amp;A

### How to set CMake options?

* Use `ccmake ..` or `ccmake <path-to-source>` in the `build` folder.
* Press `<Enter>` on the option you want to change, change it, and press `<Enter>` again.
* After changing the options, press `<c>` to configure, and press `<g>` to generate Makefiles if configured successfully.
* To quit without saving, press `<q>`.

### Why Intel MKL is not found?

* Source `mklvars.sh` in the `bin` folder of your Intel MKL to set the environment variables.

### Why Google Test is not found?

* Set `GTEST_ROOT` to a folder containing `include` and `lib` of Google Test.

### How to enable multithread support?

* Set `ISVD_OMP` with `ccmake` before building libraries.
* Make sure your LAPACK&amp;BLAS / Intel MKL uses supports multithreading.

### How to use 64-bit integer?

* Set `ISVD_USE_ILP64` with `ccmake` before building libraries.
* Add `-DISVD_USE_ILP64` to compile flag.
* Make sure your LAPACK&amp;BLAS / Intel MKL uses 64bit integer.

## Reference
* [Ting-Li Chen, Dawei D. Chang, Su-Yun Huang, Hung Chen, Chienyao Lin, Weichung Wang, “Integrating Multiple Random Sketches for Singular Value Decomposition”](https://arxiv.org/abs/1608.08285)
* [Mu Yang, “Highly Scalable Parallelism of Integrated Randomized Singular Value Decomposition with Big Data Applications”](http://doi.org/10.6342/NTU201702960)

## License
@include LICENSE.md
