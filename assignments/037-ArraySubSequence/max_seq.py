def max_seq(l):
    """
    max_seq returns a the maximum increasing contiguous subsequence in the list.
    (as determined by length).  If two or more subsequences have equal lengths,
    return the first subsequence found.
   
    Args:
    l(list): list of numbers

    Returns:
    the maximum increasing contiguous subsequence as a list. If the l is empty,
    an empty list is returned

    Raises:
    TypeError if the list contains an item that is not arithmetically 
    compatible with ints and floats
    """
    # MLP 37
    if not isinstance(l, list):
        raise TypeError("Invalid type passed into max_seq; max_seq takes a list of numbers")
        
    n = len(l)
    i, start, end, maxlen, iter = 1, 0, 1, 1, 0
    for i in range(n):
        value = l[i]
        if not isinstance(value, (int, float)):
            raise TypeError("Passed a list of {} into max_seq; max_seq takes a list of numbers".format(type(value))) 
        
        if (l[i] <= l[i - 1]):
            if (len(l[iter: i]) > maxlen):
                maxlen = len(l[iter: i])
                start = iter
                end = i
            iter = i
                
            
    return l[iter : i + 1] if i + 1 - iter > end - start else l[start : end]

