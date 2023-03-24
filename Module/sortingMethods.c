#include <Python.h>
#include <math.h>

static PyObject *insertionSort(PyObject *self, PyObject *args){ /* Сортировка вставками */
    PyObject* list;
    int i, n, l;
    double res;
    double newElement;
    if (!PyArg_ParseTuple(args, "O", &list)){ /* PyArg_ParseTuple - обработка аргументов функции и трасформация типы данных Python в типы данных C.
    Первый агрумент PyObject, кортеж переданных функции аргументов,  второй - тип переменных в которые мы хотим преобразовать наши аргументы 
    ("O" - произвольный агрумент, то есть будет сохраняться объект Python (без какого-либо преобразования) в указателе объекта C). Далее идут сами 
    переменныке в которые мы сохраняем преобразованные значения. Также осуществляется проверка, корректно ли отработала функция. */
        return NULL;
    }
    /*Преобразование данных из PyObject в наш массив в С */
	n = PyList_GET_SIZE(list); /*Длина объекта списка в list */
    double *a = (double**)malloc(n * sizeof(double*));
    for (i=0; i<n; i++){
        PyObject* item = PySequence_Fast_GET_ITEM(list, i); /* Возвращает ссылку на i-й элемент list */
	    res = PyFloat_AsDouble(item); /* Возвращает double представление элемента item */
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

    PyObject *my_list = PyList_New(n); /* Создаем массив объектов типа PyObject длины n, точнее указатель на первый элемент массива длины n*/
    for (i=0; i<n; i++)
    PyList_SetItem(my_list, i,  PyFloat_FromDouble(a[i])); /* Устанавливает элемент в список my_list на индекс i, перед этим  создаем объект PyFloatObject из a[i]*/
    return my_list; 
    free(a);
}

void main_merge(double a[], int n) /* Основная функция для сортировки слиянием */
    {
      if (n == 1)
        return;

      /* Разбиваем массив пополам и рассматриваем каждую половину отдельно. Такое разбиение происходит до тех пор 
      пока из одного массива не получится несколько мелких — размером не более двух элементов. */
      main_merge(a, n/2); 
      main_merge(&a[n/2], n - n/2);

      int l = 0;
      int r = 0;
      int *tmp = (int**)malloc(n * sizeof(int*));
      int i;

      for(i = 0; i < n; i++){
        if(a[l] < a[n/2 + r])
          tmp[i] = a[l++];
        else
          tmp[i] = a[n/2 + r++];

        if (l == n / 2){
          while(r < n - n / 2)
            tmp[++i] = a[n/2 + r++];
          break;
        } else if (r == n - n / 2){
          while(l < n / 2)
            tmp[++i] = a[l++];
          break;
        }
      }

      for(i = 0; i < n; i++)
        a[i] = tmp[i];
    }

static PyObject *mergeSort(PyObject *self, PyObject *args){ /*Сортировка слиянием*/
    PyObject* list;
    int n;
    int i;
    double res;
    if (!PyArg_ParseTuple(args, "O", &list)){ /* PyArg_ParseTuple - обработка аргументов функции и трасформация типы данных Python в типы данных C.
    Первый агрумент PyObject, кортеж переданных функции аргументов,  второй - тип переменных в которые мы хотим преобразовать наши аргументы 
    ("O" - произвольный агрумент, то есть будет сохраняться объект Python (без какого-либо преобразования) в указателе объекта C). Далее идут сами 
    переменныке в которые мы сохраняем преобразованные значения. Также осуществляется проверка, корректно ли отработала функция. */
        return NULL;
    }
    /*Преобразование данных из PyObject в наш массив в С */
	n = PyList_GET_SIZE(list); /*Длина объекта списка в list */
    double *a = (double**)malloc(n * sizeof(double*));
    for (i=0; i<n; i++){
        PyObject* item = PySequence_Fast_GET_ITEM(list, i); /* Возвращает ссылку на i-й элемент list */
	    res = PyFloat_AsDouble(item); /* Возвращает double представление элемента item */
	    a[i] = res;
    }

    /* Основная функция сортировки слиянием*/
    main_merge(a, n);

    PyObject *my_list = PyList_New(n); /* Создаем массив объектов типа PyObject длины n, точнее указатель на первый элемент массива длины n*/
    for (i=0; i<n; i++)
    PyList_SetItem(my_list, i,  PyFloat_FromDouble(a[i])); /* Устанавливает элемент в список my_list на индекс i, перед этим  создаем объект PyFloatObject из a[i]*/
    return my_list; 
    free(a);
}


void heapify(double a[], int n, int i){ /*Вспомогательная функция для пирамидальной сортировки для преобразования в двоичную кучу поддерева с коревым узлом i */
        int swap;
        int largest = i; /* Родительский узел */
        int l = 2*i + 1; /* Левый дочерний элемент */
        int r = 2*i + 2; /* Правый дочерний элемент */

        if (l < n && a[l] > a[largest])
            largest = l;

        if (r < n && a[r] > a[largest])
            largest = r;

        /* Меняем местами родительский узел с каким-то из его дочених узлов, если он оказался меньше */
        if (largest != i)
        {
            swap = a[i];
            a[i] = a[largest];
            a[largest] = swap;

            heapify(a, n, largest); /* Далее проталкиваем элемент вниз, если он оказался меньше, чем какой-то из его дочерних узлов */
        }
}

void main_pyramid(double a[], int n){ /* Реализация сортировки */
        int i;
        int temp;
        /* Первый этап сортировки, на котором элементы массива формируют двоичную кучу. Для этого 
        элементы массива с индексами 0 <= i < n / 2 проталкиваются вниз */
        for (i = n / 2 - 1; i >= 0; i--)
            heapify(a, n, i); /* преобразование в двоичную кучу поддерева с коревым узлом i */

        /*Второй этап работы алгоритма, на котором элементы массива по очереди берутся из корня двоичной кучи и меняются местами 
        с последним элементом массива, после чего новый корень дерева проталкивается вниз с помощью функции heapify */
        for (i=n-1; i>=0; i--)
        {
            temp = a[0];
            a[0] = a[i];
            a[i] = temp;
            heapify(a, i, 0);
        }
}



static PyObject *pyramidSort(PyObject *self, PyObject *args){ /*Пирамидальная сортировка*/
    PyObject* list;
    int n;
    int i;
    double res;
    if (!PyArg_ParseTuple(args, "O", &list)){ /* PyArg_ParseTuple - обработка аргументов функции и трасформация типы данных Python в типы данных C.
    Первый агрумент PyObject, кортеж переданных функции аргументов,  второй - тип переменных в которые мы хотим преобразовать наши аргументы 
    ("O" - произвольный агрумент, то есть будет сохраняться объект Python (без какого-либо преобразования) в указателе объекта C). Далее идут сами 
    переменныке в которые мы сохраняем преобразованные значения. Также осуществляется проверка, корректно ли отработала функция. */
        return NULL;
    }
    /*Преобразование данных из PyObject в наш массив в С */
	n = PyList_GET_SIZE(list); /*Длина объекта списка в list */
    double *a = (double**)malloc(n * sizeof(double*));
    for (i=0; i<n; i++){
        PyObject* item = PySequence_Fast_GET_ITEM(list, i); /* Возвращает ссылку на i-й элемент list */
	    res = PyFloat_AsDouble(item); /* Возвращает double представление элемента item */
	    a[i] = res;
    }
    /* Основная функция пирамидальной сортировки*/
    main_pyramid(a, n);

    PyObject *my_list = PyList_New(n); /* Создаем массив объектов типа PyObject длины n, точнее указатель на первый элемент массива длины n*/
    for (i=0; i<n; i++)
    PyList_SetItem(my_list, i,  PyFloat_FromDouble(a[i])); /* Устанавливает элемент в список my_list на индекс i, перед этим  создаем объект PyFloatObject из a[i]*/
    return my_list; 
    free(a);
}


/* Массив структур, описывающий методы модуля */
static PyMethodDef ownmod_methods[] = {  
    {
	"insertionSort", /* название функции внутри python */
	insertionSort, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"insertion sort" /* документация для функции внутри python */
    },
    {
	"mergeSort", /* название функции внутри python */
	mergeSort, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"merge sort" /* документация для функции внутри python */
    },
    {
	"pyramidSort", /* название функции внутри python */
	pyramidSort, /* функция C */
	 METH_VARARGS, /* макрос, поясняющий, что функция у нас с аргументами */
	"pyramid sort" /* документация для функции внутри python */
    },
    { NULL, NULL, 0, NULL }
};


/* Cтруктура, которая описывает непосредственно сам модуль */
static PyModuleDef simple_module = { 
    PyModuleDef_HEAD_INIT, /* обязательный макрос */
    "sortingMethods", /* sortingMethods.__name__ */
    "interesting sorting Methods: insertion Sort, merge Sort, pyramid Sort", /* sortingMethods.__doc__ */
    -1,
    ownmod_methods, /* передаем массив с методами модуля */
    NULL,NULL,NULL
};


/* Создание самого модуля */
PyMODINIT_FUNC PyInit_sortingMethods(void)
{
    PyObject* m;
    /* создаем модуль */
    m = PyModule_Create(&simple_module);
    /* если все корректно, то эта проверка не проходит */
    if (m == NULL)
        return NULL;
    return m;
}
