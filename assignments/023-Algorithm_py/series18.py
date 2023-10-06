def series18(n):
    """Implement your function below"""
    if n == 0:
         return
    # Allocate space for 2 * n contiguous elements, call it arr
    arr = []
    # Count from 0 to 3 * N exclusively (call it i) 
    for i in range(3 * n): 
    # and for each i:
    # put the value of  -(n*n) + (i * i) inside position i of arr
        arr.append((-1 * n * n) + (i * i))
  
    for i in arr:
        print(i, end=" ")
    print("")
  # arr is the answer
    return arr