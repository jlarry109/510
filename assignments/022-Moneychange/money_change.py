import math

def print_change(change):
    """

    Args:
        change (dictionary):
    This function prints the change in order of the descending denomination and their corresponding amount. 
    
    """
    for key, value in change.items():
        print("{}{:.2f}: {}".format("$", key, value))
        
        
def make_change(amount):
    """
    This function take amount as input and returns a dictionary containing 
    the smallest number of bills and coins that add up to that number. 
    The possible denominations are 100.00, 50.00, 20.00, 10.00, 5.00, 2.00,
    1.00, 0.25, 0.10, 0.05, and 0.01.
    
    """
    list = [100.00, 50.00, 20.00, 10.00, 5.00, 2.00, 1.00, 0.25, 0.10, 0.05, 0.01]
    denominations = {}
    for denomination in list:
        if (amount >= denomination):
            num_denom = int(math.ceil(amount // denomination))
            denominations[denomination] = denominations.get(denomination, 0) + num_denom
            amount = round(amount % denomination, 2)
    return denominations  
    