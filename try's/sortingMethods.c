#include <Python.h>
#include <math.h>

void merge_sort(double a[], int n)
    {
      if (n == 1)
        return;

      merge_sort(a, n/2);
      merge_sort(&a[n/2], n - n/2);

      int liter = 0;
      int riter = 0;
      int *tmp = (int**)malloc(n * sizeof(int*));
      int i;

      for(i = 0; i < n; i++){
        if(a[liter] < a[n/2 + riter])
          tmp[i] = a[liter++];
        else
          tmp[i] = a[n/2 + riter++];

        if (liter == n / 2){
          while(riter < n - n / 2)
            tmp[++i] = a[n/2 + riter++];
          break;
        } else if (riter == n - n / 2){
          while(liter < n / 2)
            tmp[++i] = a[liter++];
          break;
        }
      }

      for(i = 0; i < n; i++)
        a[i] = tmp[i];
    }

static PyObject *merge(PyObject *self, PyObject *args){
    PyObject* list;
    int n;
    int i;
    double res;
    if (!PyArg_ParseTuple(args, "O", &list)){
        return NULL;
    }
	n = PyList_GET_SIZE(list);
    double *a = (double**)malloc(n * sizeof(double*));
    for (i=0; i<n; i++){
        PyObject* item = PySequence_Fast_GET_ITEM(list, i);
	    res = PyFloat_AsDouble(item);
	    a[i] = res;
    }

    merge_sort(a, n);

    PyObject *my_list = PyList_New(n);
    for (i=0; i<n; i++)
    PyList_SetItem(my_list, i,  PyFloat_FromDouble(a[i]));
    return my_list;
    free(a);
}


static PyMethodDef ownmod_methods[] = {

    {
	"merge",
	merge,
	 METH_VARARGS,
	"merge"
    },
    { NULL, NULL, 0, NULL }
};

static PyModuleDef simple_module = {

    PyModuleDef_HEAD_INIT,
    "sortingMethods",
    "sortingMethods",
    -1,
    ownmod_methods,
    NULL,NULL,NULL
};

PyMODINIT_FUNC PyInit_sortingMethods(void)
{
    PyObject* m;
    m = PyModule_Create(&simple_module);
    if (m == NULL)
        return NULL;
    return m;}
