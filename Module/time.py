import sortingMethods
import random
import time
import matplotlib.pyplot as plt
import numpy as np

def compare_timings (n, iterations=20, insertionSortFlag=1):
    time_array = [0.0]*3 + insertionSortFlag*[0.0]
    result=[]
    for i in range (iterations):
        arr=random.sample(range(1, 3*n), n)

        if insertionSortFlag==1:
            start = time.time()
            sortingMethods.insertionSort(arr)
            end = time.time()

            while ((end-start)==0):
                start = time.time()
                sortingMethods.insertionSort(arr)
                end = time.time()
            time_array[0] += end-start
    ##        print (f"INSERTION - {(end-start)}")
        

        start = time.time()
        sortingMethods.mergeSort(arr)
        end = time.time()

        while ((end-start)==0):
            start = time.time()
            sortingMethods.mergeSort(arr)
            end = time.time()
        time_array[insertionSortFlag*1] += end-start
##        print (f"MERGE - {(end-start)}")

        

        start = time.time()
        sortingMethods.pyramidSort(arr)
        end = time.time()

        while ((end-start)==0):
            start = time.time()
            sortingMethods.pyramidSort(arr)
            end = time.time()
        time_array[insertionSortFlag*1+1] += end-start
##        print (f"PYRAMID - {(end-start)}")

        start = time.time()
        sorted(arr)
        end = time.time()
        
        while ((end-start)==0):
            start = time.time()
            sorted(arr)
            end = time.time()
        time_array[insertionSortFlag*1+2] += end-start
##        print (f"PYTHON - {(end-start)}")
    
    for i in range (len(time_array)):
        result.append((time_array[i]*(10**3))/iterations)
    return result


def print_compare_timings(all_n, iterations=20, insertionSortFlag=1):
    types_sort = ["INSERTION SORT", "MERGE SORT", "PYRAMID SORT", "PYTHON SORT - TimeSort"]
    all_results=[]

    for i in all_n:
        all_results += compare_timings(i, iterations, insertionSortFlag)


    x = np.arange(0, 2*len(all_n), 2)
    if insertionSortFlag==1:
        width = 0.2
          
        plt.bar(x-width*1.5, all_results[::4], width, color='#7FB5B5')
        plt.bar(x-width*0.5, all_results[1::4], width, color='#FF8C69')
        plt.bar(x+width*0.5, all_results[2::4], width, color='#AFDAFC')
        plt.bar(x+width*1.5, all_results[3::4], width, color='#B39F7A')
        plt.xticks(x, all_n)
        plt.legend(types_sort)
    else:
        width = 0.2
          
        plt.bar(x-width, all_results[::3], width, color='#7FB5B5')
        plt.bar(x, all_results[1::3], width, color='#FF8C69')
        plt.bar(x+width, all_results[2::3], width, color='#AFDAFC')
        plt.xticks(x, all_n)
        plt.legend(types_sort[1:])

    plt.xlabel("Number of elements")
    plt.ylabel("Time(ms)")
    plt.title("Time comparison")
    plt.show()



all_n1=[1000, 5000, 10000, 30000]
all_n2=[1000, 5000, 10000]
all_n3=[10000, 100000, 200000]


print_compare_timings(all_n2, 20, 1)
        

