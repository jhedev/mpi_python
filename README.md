###Build

```
python3 setup.py build
```

Creates the `build` directory.

###Run

```
export PYTHONPATH=`pwd`/build/lib.linux-x86_64-3.4:$PYTHONPATH # or similar depending on your python version and platform
mpirun -np 1 test_it.py
```

which produces the following error message:

```
[aia256:15841] mca: base: component_find: unable to open /pds/opt/openmpi-1.8.7/lib64/openmpi/mca_shmem_posix: /pds/opt/openmpi-1.8.7/lib64/openmpi/mca_shmem_posix.so: undefined symbol: opal_shmem_base_framework (ignored)
[aia256:15841] mca: base: component_find: unable to open /pds/opt/openmpi-1.8.7/lib64/openmpi/mca_shmem_mmap: /pds/opt/openmpi-1.8.7/lib64/openmpi/mca_shmem_mmap.so: undefined symbol: opal_show_help (ignored)
[aia256:15841] mca: base: component_find: unable to open /pds/opt/openmpi-1.8.7/lib64/openmpi/mca_shmem_sysv: /pds/opt/openmpi-1.8.7/lib64/openmpi/mca_shmem_sysv.so: undefined symbol: opal_show_help (ignored)
--------------------------------------------------------------------------
It looks like opal_init failed for some reason; your parallel process is
likely to abort.  There are many reasons that a parallel process can
fail during opal_init; some of which are due to configuration or
environment problems.  This failure appears to be an internal failure;
here's some additional information (which may only be relevant to an
Open MPI developer):

opal_shmem_base_select failed
--> Returned value -1 instead of OPAL_SUCCESS
--------------------------------------------------------------------------
--------------------------------------------------------------------------
It looks like orte_init failed for some reason; your parallel process is
likely to abort.  There are many reasons that a parallel process can
fail during orte_init; some of which are due to configuration or
environment problems.  This failure appears to be an internal failure;
here's some additional information (which may only be relevant to an
Open MPI developer):

opal_init failed
--> Returned value Error (-1) instead of ORTE_SUCCESS
--------------------------------------------------------------------------
--------------------------------------------------------------------------
It looks like MPI_INIT failed for some reason; your parallel process is
likely to abort.  There are many reasons that a parallel process can
fail during MPI_INIT; some of which are due to configuration or environment
problems.  This failure appears to be an internal failure; here's some
additional information (which may only be relevant to an Open MPI
developer):

ompi_mpi_init: ompi_rte_init failed
--> Returned "Error" (-1) instead of "Success" (0)
--------------------------------------------------------------------------
*** An error occurred in MPI_Init
*** on a NULL communicator
*** MPI_ERRORS_ARE_FATAL (processes in this communicator will now abort,
***    and potentially your MPI job)
[aia256:15841] Local abort before MPI_INIT completed successfully; not able to aggregate error messages, and not able to guarantee that all other processes were killed!
-------------------------------------------------------
Primary job  terminated normally, but 1 process returned
a non-zero exit code.. Per user-direction, the job has been aborted.
-------------------------------------------------------
--------------------------------------------------------------------------
mpirun detected that one or more processes exited with non-zero status, thus causing
the job to be terminated. The first process to do so was:

Process name: [[7992,1],0]
Exit code:    1
--------------------------------------------------------------------------
```

###Notes

Answer from the `users@open-mpi.org` mailing list:

>Short version:
>
>The easiest way to do this is to configure your Open MPI installation with --disable-dlopen.
>
>More detail:
>
>Open MPI uses a bunch of plugins for its functionality. When you dlopen libmpi in a private namespace (like Python does), and then libmpi tries to dlopen its plugins, the plugins can't find the symbols that they need in the main libmpi library (because they're in a private namespace).
>The workaround is to build Open MPI with all of its plugins slurped up into the libmpi library itself (i.e., so that Open MPI doesn't have to dlopen its plugins). 

See [here](http://www.open-mpi.org/community/lists/users/2015/09/27608.php).

mpi4py uses [this workaround](https://bitbucket.org/mpi4py/mpi4py/src/master/src/lib-mpi/compat/openmpi.h?fileviewer=file-view-default#openmpi.h-52)).
