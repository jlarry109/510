def array_max(array):
    """
    Finds the largest number in the list.
    Ignores elements that are not an int or a float

    Args:
        array (list): list of numbers (either float or int)

    Returns:
    Largest number in the list.  None if array is empty
    or if array is not a list.
    """
    i, currmax = 0, None

    while i < len(array) and type(array[i]) is not int and type(array[i]) is not float:
        i += 1
    if i < len(array): 
        if type(array[i]) is int or type(array[i]) is float:
            currmax = array[i]
            while i < len(array):
                if type(array[i]) is int or type(array[i]) is float:
                    currmax = array[i] if array[i] > currmax else currmax
                i += 1
        return currmax
    else: 
        return None
    