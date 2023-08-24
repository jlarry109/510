def insertion_sort(arr):
    for i in range(1, len(arr)):
        key = arr[i]  # Current element to be inserted at the correct position
        j = i - 1  # Index of the previous element
        
        # Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key  # Insert the current element at its correct position


input_array = [12, 11, 13, 5]
print("Original Array:", input_array)
    
insertion_sort(input_array)
    
print("Sorted Array:", input_array)
