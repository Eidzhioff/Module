import sortingMethods
import random
import time
import matplotlib.pyplot as plt
import numpy as np

arr=random.sample(range(1, 100000), 10000)

types_sort = ["INSERTION SORT", "MERGE SORT", "PYRAMID SORT", "PYTHON SORT - TimeSort"]

def compare_timings (n, iterations=20):
    time_array = [0.0]*4
    result=[]
    for i in range (iterations):
        arr=random.sample(range(1, 3*n), n)
        
        start = time.time()
        sortingMethods.insertion(arr)
        end = time.time()

        while ((end-start)==0):
            start = time.time()
            sortingMethods.insertion(arr)
            end = time.time()
        time_array[0] += end-start
##        print (f"INSERTION - {(end-start)}")
        

        start = time.time()
        sortingMethods.merge(arr)
        end = time.time()

        while ((end-start)==0):
            start = time.time()
            sortingMethods.merge(arr)
            end = time.time()
        time_array[1] += end-start
##        print (f"MERGE - {(end-start)}")

        

        start = time.time()
        sortingMethods.pyramid(arr)
        end = time.time()

        while ((end-start)==0):
            start = time.time()
            sortingMethods.pyramid(arr)
            end = time.time()
        time_array[2] += end-start
##        print (f"PYRAMID - {(end-start)}")

        start = time.time()
        sorted(arr)
        end = time.time()
        
        while ((end-start)==0):
            start = time.time()
            sorted(arr)
            end = time.time()
        time_array[3] += end-start
##        print (f"PYTHON - {(end-start)}")
    
    for i in range (len(types_sort)):
        result.append((time_array[i]*(10**3))/iterations)
    return result


all_results=[]
##all_n = [i for i in range (1000, 101001, 50000)] 
##all_n = [i for i in range (1000, 3001, 1000)]
all_n=[1000, 5000, 10000, 30000]

for i in all_n:
    all_results += compare_timings(i)

print (all_results)


x = np.arange(0, 2*len(all_n), 2)
width = 0.2
  
plt.bar(x-width*1.5, all_results[::4], width, color='#7FB5B5')
plt.bar(x-width*0.5, all_results[1::4], width, color='#FF8C69')
plt.bar(x+width*0.5, all_results[2::4], width, color='#AFDAFC')
plt.bar(x+width*1.5, all_results[3::4], width, color='#B39F7A')
plt.xticks(x, all_n)
plt.xlabel("Number of elements")
plt.ylabel("Time(ms)")
plt.legend(types_sort)
plt.title("Time comparison")
plt.show()

