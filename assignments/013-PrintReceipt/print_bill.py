#def print_receipt(subtotal, tax_rate, tip_rate):
def compute_tax_and_tips(subtotal, tax_rate, tip_rate):
    tax = tax_rate * subtotal
    tips = tip_rate * subtotal
    return tax, tips


def print_receipt(subtotal, tax_rate, tip_rate):
    """_summary_
     This function computes and prints out part of the bill/receipt 
     provided to customers at a restaurant

    Args:
        subtotal (_float_): total cost of food and drink items bought
        tax_rate (_float_): the effective tax rate on the subtotal 
        tip_rate (_float_): the percentage of subtotal, paid to wait staff, in addition to subtotal and tax 
    """
    tax, tips = compute_tax_and_tips(subtotal, tax_rate, tip_rate)
    total = tax + tips + subtotal
    tax = "{:.2f}".format(tax)
    tips = "{:.2f}".format(tips)
    subtotal = "{:.2f}".format(subtotal)
    total = "{:.2f}".format(total)
    
    print("     Subtotal: ${:>10}".format(subtotal))
    print("     Tax: ${:>10}".format(tax))
    print("     Tip: ${:>10}".format(tips))
    print("           {}".format("=========="))
    print("   Total: ${:>10}".format(total))
    