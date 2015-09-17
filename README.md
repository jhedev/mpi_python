###Build

```
python3 setup.py build
```

Creates the `build` directory.

###Run

```
export PYTHONPATH=`pwd`/build/lib.linux-x86_64-3.4:$PYTHONPATH
mpirun -np 1 test_it.py
```
