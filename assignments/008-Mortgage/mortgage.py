p = float(input("What is the amount borrowed?"))
r = float(input("What is the annual interest rate - express this as a decimal such as 0.07 for 7%?"))

# place your code here after this line
r = r / 12 #00
num_payments = 360
print("p is:" + str(p))
print("r is:" + str(r))
periodic_amortization = p * (r * (1 + r) ** num_payments)/ (-1 + (1 + r)**num_payments) 
payment_amount = int(periodic_amortization * 100)/100
print(payment_amount)
