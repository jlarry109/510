

def compute__account_balance(balance, rate_of_return, contribution):
  interest = balance * rate_of_return
  return balance + contribution + balance * rate_of_return

def print_info(start_age, curr_month, initial_balance):
  age_years = (start_age + curr_month) // 12
  age_months = (start_age + curr_month) % 12
  print(f"Age {age_years:3d} month {age_months:2d} you have ${initial_balance:,.2f}")
  
def get_retirement_info(start_age, curr_month, initial_savings, my_info):
  while (curr_month < my_info["months"]):
    print_info(start_age, curr_month, initial_savings)
    initial_savings = compute__account_balance(initial_savings, my_info["rate_of_return"], my_info["contribution"]);
    curr_month += 1
  return initial_savings, curr_month

def retirement(start_age, initial_savings, working_info, retired_info):
    """
    Prints the current status of an individual's retirement account.

    The dictionaries both have these fields:
         "months","contribution","rate_of_return"

    Args:
      start_age (int): At what age (in months) does the individual start
      initial_savings (float): initial savings in dollars
      working_info (dict): information about working
      retired_into (dict): information about retirement
    Returns:
      None
    """
    
    initial_savings, curr_month = get_retirement_info(start_age, 0, initial_savings, working_info)
    retired_info["months"] = retired_info.get("months") + curr_month
    get_retirement_info(start_age, curr_month, initial_savings, retired_info)

working_info = {}
working_info["contribution"] = 1000
working_info["months"] = 489
working_info["rate_of_return"] = 0.045/12

retired_info = {}

retired_info["contribution"] = -4000
retired_info["months"] = 384;
retired_info["rate_of_return"] = 0.01/12
  
startAge = 327
initial_savings = 21345
retirement(startAge, initial_savings, working_info, retired_info);