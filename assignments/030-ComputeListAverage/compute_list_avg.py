def compute_average(l):
    """
    Computes the average of list, ignoring any entries that 
    are not numbers (floats or ints)

    Args:
    l(list): list of items to compute the average
 
    returns:
    average of the numbers in the list
    
    raises:
    ValueError if the argument is not a list or if the list does not contain any numbers
    """
    if not isinstance(l, list):
        raise ValueError("Argument must be a list")
    
    numbers = [x for x in l if isinstance(x, (int, float))]
    
    if not numbers:
        raise ValueError("List does not contain any numbers")
    
    return sum(numbers) / len(numbers)

    