#include <Python.h>
#include <math.h>

static PyObject *insertion(PyObject *self, PyObject *args){
    PyObject* list;
    int i, n, l;
    double res;
    double newElement;
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
    for (i = 1; i < n; i++){
            newElement = a[i];
            l = i - 1;
            while(l >= 0 && a[l] > newElement){
                a[l+1] = a[l];
                l = l - 1;
            }
            a[l+1] = newElement;
        }
    PyObject *my_list = PyList_New(n);
    for (i=0; i<n; i++)
    PyList_SetItem(my_list, i,  PyFloat_FromDouble(a[i]));
    return my_list;
    free(a);
}

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
void heapify(double a[], int n, int i){
        int swap;
        int largest = i;
        int l = 2*i + 1;
        int r = 2*i + 2;

        if (l < n && a[l] > a[largest])
            largest = l;

        if (r < n && a[r] > a[largest])
            largest = r;
        if (largest != i)
        {
            swap = a[i];
            a[i] = a[largest];
            a[largest] = swap;

            heapify(a, n, largest);
        }
}

void sort(double a[],int n){
        int i;
        int temp;
        for (i = n / 2 - 1; i >= 0; i--)
            heapify(a, n, i);
        for (i=n-1; i>=0; i--)
        {
            temp = a[0];
            a[0] = a[i];
            a[i] = temp;

            heapify(a, i, 0);
        }
}



static PyObject *pyramid(PyObject *self, PyObject *args){
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

    sort(a, n);

    PyObject *my_list = PyList_New(n);
    for (i=0; i<n; i++)
    PyList_SetItem(my_list, i,  PyFloat_FromDouble(a[i]));
    return my_list;
    free(a);
}

static PyMethodDef ownmod_methods[] = {
    {
	"insertion",
	insertion,
	 METH_VARARGS,
	"insertion"
    },
    {
	"merge",
	merge,
	 METH_VARARGS,
	"merge"
    },
    {
	"pyramid",
	pyramid,
	 METH_VARARGS,
	"pyramid"
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
