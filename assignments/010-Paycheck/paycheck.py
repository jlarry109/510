"""
    Paycheck
   Write a program that computes a simple weekly paycheck for an individual. 
   Prompt the user to enter the number of hours worked and the pay rate. 
   If an individual works over 40 hours, then the individual is paid at 1.5 times the hourly rate for the hours worked over 40.
   Print the initial total. Of course, the government taxes the individualʼs pay. Assume the tax rate is 20%. 
   Print the amount withheld for taxes. Then print the net amount to be paid to the individual.
   
"""
def compute_paycheck(num_workhours, pay_rate):
    regular_hours = min(40, num_workhours)
    overtime = 0
    if (num_workhours > 40):
        overtime = num_workhours - regular_hours
    print("Total pay:", ((regular_hours * pay_rate) + (overtime * 1.5 * pay_rate)))
    print("Taxes:", ((regular_hours * pay_rate) + (overtime * 1.5 * pay_rate)) * 0.2)
    print("Net pay:", ((regular_hours * pay_rate) + (overtime * 1.5 * pay_rate)) * 0.8)
    return ((regular_hours * pay_rate) + (overtime * 1.5 * pay_rate)) * 0.8

num_workhours = float(input("How many hours did the employee work?\n"))
pay_rate = float(input("What is the employee's pay rate?\n"))
compute_paycheck(num_workhours, pay_rate)
