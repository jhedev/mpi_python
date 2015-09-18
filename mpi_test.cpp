#include <Python.h>

#include <mpi.h>

using namespace std;


static PyObject * get(PyObject *self, PyObject *args){
  int rank, nprocs;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Finalize();

  Py_RETURN_NONE
}

static PyMethodDef TestmpiMethods[] = {
  {"get", get, METH_VARARGS, "get"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef testmpimodule = {
  PyModuleDef_HEAD_INIT,
  "testmpi", /* name of the module */
  NULL,
  -1,
  TestmpiMethods
};

PyMODINIT_FUNC PyInit_testmpi(void) {
  return PyModule_Create(&testmpimodule);
}
