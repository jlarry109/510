import sys


def compare_dates(date1, date2):
    """
    Compare two dates and return:
     1 if date1 is later than date2
     0 if date1 is equal to date2
     -1 if date1 is sooner than date2

    :param date1: The first date
    :param date2: The second date
    :return: 1 if date1 > date2, 0 if date1 == date2, -1 if date1 < date2
    """
    date1_year, date1_month = date1.split(".")
    date2_year, date2_month = date2.split(".")
    if (int(date1_year) > int(date2_year)):
        return 1
    elif (int(date1_year) <= int(date2_year)):
        return -1
    elif (int(date1_month) == int(date2_month)):
        return 0
    else:
        return 1 if int(date1_month) <= int(date2_month) else -1
     
     
def compute_adjacent_month(date_str, previous_or_next):
    """
    Compute the date of the adjacent month based on the provided date and direction.

    This function takes a date in the format "YYYY.MM" and computes the date of the adjacent month,
    either the previous month or the next month, based on the specified direction.

    :param date_str: The input date in the format "YYYY.MM".
    :param previous_or_next: The direction to compute the adjacent month, either "previous" or "next".
    
    :return: The date of the adjacent month in the format "YYYY.MM".

    :raises ValueError: If the input date format is incorrect or if the `previous_or_next` value
                       is not "previous" or "next".
    """
    # Split the input date into year and month parts
    year_str, month_str = date_str.split('.')

    # Convert year and month parts to integers
    year = int(year_str)
    month = int(month_str)
    # If we are computing previous month's date, then:
    if (previous_or_next == "previous"):
        # Subtract one from the month to get the previous month
        month -= 1

    # Handle the case where the month becomes zero (December of the previous year)
        if month == 0:
            month = 12
            year -= 1
    # If we are computing next month's date, then:
    elif (previous_or_next == "next"):
        month += 1

        # Handle the case where the month becomes 13 (January of the next year)
        if month == 13:
            month = 1
            year += 1
          
    else:
        raise ValueError("previous_or_next value must either be 'previous' or 'next'")
    # Format the result as "YYYY.MM"
    adjacent_month = f"{year:04d}.{month:02d}"

    return adjacent_month
  

def calculate_rate_of_return(curr_date, sp_data_dict=None, bond_data_dict=None):
    """
    Calculate the rate of return based on S&P level and bond rate at a specific time.

    :param sp_level: S&P level at time t
    :param bond_rate: Bond rate at time t
    :return: Rate of return based on the available investment data
    """
    previous_month_sp_level = None
    # Calculate the date for previous month
    previous_month_date = compute_adjacent_month(curr_date, "previous")
    
    if sp_data_dict is not None and bond_data_dict is not None:
        raise ValueError("Please specify only one of sp_level or bond_rate.")
    
    if sp_data_dict is not None:
        # retrieve previous month's sp_level
        try:
            previous_month_sp_level = sp_data_dict[previous_month_date][0]
        except KeyError as e:
            call_exit("sp", f"KeyError: you specified a date outside of the range of the valid period. More info: {e}")
            
        # Calculate rate of return for S&P
        curr_month_sp_level, curr_month_dividend = sp_data_dict[curr_date]
        sp_rate_of_return = (float(curr_month_sp_level) / float(previous_month_sp_level)) - 1
        div_rate_of_return = (float(curr_month_dividend) / 12) / float(curr_month_sp_level)
        rate_of_return = sp_rate_of_return + div_rate_of_return
    elif bond_data_dict is not None:
        # Calculate rate of return for bonds
        try:
            bond_rate_of_return = bond_data_dict[curr_date]
        except KeyError as e:
            call_exit("bonds", f"KeyError: you specified a date outside of the range of the valid period. More info:{e}")
        rate_of_return = (float(bond_rate_of_return) / 12) / 100
    else:
        raise ValueError("One of sp_level or bond_rate must be specified.")
    
    return rate_of_return


def call_exit(exit_type, message):
    """
    Terminate the program with an exit code based on the provided argument.

    This function is used to print the message in "message" and exit the program with an exit code. 
    The exit code is determined by the provided argument, which can be either "sp", "bonds" or "command_line". 
    If "sp" is provided, the program will exit with an exit code of 20. For any other value, the program will exit
    with an exit code of 30.

    :param exit_type: A string argument that specifies the exit behavior (error is related to sp_data, bonds_data,
    or issues with the command line).

    :param message: The error message to print before exiting.
    
    :return: This function does not return any value.
    """
    print(message)
    if exit_type == "sp":
        exit(20)
    elif exit_type == "bonds":
        exit(30)
    elif exit_type == "command_line":
        exit(10)
    else:
        raise ValueError("Must supply one of 'sp', 'bonds', or 'command_line' as the value of exit_type")

  
def validate_date(date, exit_type):
    """
    Validate the format of a date string and handle errors if invalid.

    This function checks the format of a date string in the "YYYY.MM" format. It validates
    whether the year is exactly 4 digits, contains only digits, whether the month is exactly
    2 digits, contains only digits, and if the month is a valid value (1 to 12).

    If the date format is invalid or an error occurs during validation, it prints an error
    message and exits the program with an appropriate exit code based on the 'bonds_or_sp'
    argument.

    :param date: The date string in the format "YYYY.MM" to be validated.
    :param bonds_or_sp: A string indicating whether the date is related to bonds or S&P.
    
    :return: This function does not return any value.
    """
    try:
        year_str, month_str = date.split(".")
        if len(year_str) != 4:
            call_exit(exit_type, "Invalid year format. Year must be exactly 4 digits.")
        if not year_str.isdigit():
            call_exit(exit_type, "Invalid year format. Year must contain only digits.")
        if len(month_str) != 2:
            call_exit(exit_type, "Invalid month format. Month must be exactly 2 digits.")
        if not month_str.isdigit():
            call_exit(exit_type, "Invalid month format. Month must contain only digits.")
        if int(month_str) > 12:
            call_exit(exit_type, "A valid month can't be greater than 12")
        
    except Exception as e:
        call_exit(
            exit_type,
            f"Year and Month must be separated by a period character. More info: "
            f"Date you provided: {date} An error occurred: {e}")


def validate_real_number(real_number, exit_type):
    """
    Validate the format of a real number string and handle errors if invalid.

    This function checks the format of a real number string, which is expected to be in
    the format "dollars.cents" or "dollars". It ensures that the real number contains at
    most one period ('.') character, and both the whole and decimal parts consist of
    digits only.

    If the real number format is invalid or an error occurs during validation, it prints
    an error message and exits the program with an appropriate exit code based on the
    'exit_type' argument.

    :param real_number: The real number string to be validated.
    :param exit_type: A string indicating whether the real number is related to bonds or S&P.
    
    :return: This function does not return any value.
    """
    real_number_list = []
    try:
        real_number_list = real_number.split(".")
        if not (0 < len(real_number_list) < 3):
            call_exit(exit_type, "Invalid real number format. Real_number must have at most one 'period' character")
        else:
            if len(real_number_list) == 1:
                # If real number has no decimal place/portion, append "00" to the list
                real_number_list.append("00")
            whole_part, decimal_part = real_number_list[0], real_number_list[1]
            for value in whole_part:
                if not value.isdigit():
                    call_exit(exit_type, 
                              "Invalid real number format. Real_number must contain at most, one non-digit character.")
            for value in decimal_part:
                if not value.isdigit():
                    call_exit(exit_type, 
                              "Invalid real number format. Real_number must contain at most, one non-digit character.")
    except Exception as e:
        call_exit(exit_type, f"An error occurred: {e}")

    
def validate_bond_data(data):
    """
    Validate the format of bond data and handle errors if invalid.

    This function checks the format of bond data, which is expected to be in the format
    "date,percent_rate". It ensures that there is exactly one comma separating the date
    and percent_rate, and it validates both parts.

    :param data: The bond data string to be validated.
    
    :return: This function does not return any value.
    
    :raises sys.exit(30): If the bond data format is invalid.
    """
    bond_data_list = []
    try:
        bond_data_list = data.split(",")
        if len(bond_data_list) != 2:
            call_exit("bonds", "There must be exactly one comma in a valid bond_data entry")
        else:
            date_str, percent_rate_str = bond_data_list[0], bond_data_list[1]
            validate_date(date_str, "bonds")
            validate_real_number(percent_rate_str, "bonds")
  
    except Exception as e:
        call_exit("bonds", f"An error occurred: {e}")

      
def validate_sp_data(sp_data):
    """
    Validate the format of S&P data and handle errors if invalid.

    This function checks the format of S&P data, which is expected to be in the format
    "date,index_level,dividend". It ensures that there are exactly two commas separating
    the date, index_level, and dividend, and it validates all three parts.

    :param sp_data: The S&P data string to be validated.

    :return: This function does not return any value.

    :raises sys.exit(20): If the S&P data format is invalid.
    """
    sp_data_list = []
    try:
        sp_data_list = sp_data.split(",")
        if len(sp_data_list) != 3:
            call_exit("sp", "There must be exactly two commas in a valid sp_data entry")

        else:
            date_str, index_level_str, dividend_str = sp_data_list[0], sp_data_list[1], sp_data_list[2]
            validate_date(date_str, "sp")
            validate_real_number(index_level_str, "sp")
            validate_real_number(dividend_str, "sp")
    except Exception as e:
        call_exit("sp", f"An error occurred: {e}")

      
def parse_sp_data(filename):
    """
    Parse index levels data from a file and store it in a dictionary.

    This function reads data from a file where each line is expected to be in the format
    "date,index_level,dividend". It parses the data and stores it in a dictionary with
    dates as keys and tuples of index_level and dividend as values.

    :param filename: The name of the file containing index levels data.

    :return: A dictionary containing parsed index levels data.

    :raises sys.exit(20): If the file does not exist or if there is a permission error.
    :raises Exception: If an error occurs while processing the file.
    """
    sp_levels_dict = {}
    try:
        # Process the file contents here
        with open(filename, "r") as file:
            next(file)
            for line in file:
                line = line.strip()
                date, index_level, dividend = line.split(",")
                sp_levels_dict[date] = (index_level, dividend)
    except FileNotFoundError:
        call_exit("sp", f"The file {filename} does not exist.")
    except PermissionError:
        call_exit("sp", "Permission denied. You don't have access to this file.")
    except Exception as e:
        call_exit("sp", f"An error occurred: {e}")
    return sp_levels_dict
  
  
def parse_bond_data(filename):
    """
    Parse bond data from a file and store it in a dictionary.

    This function reads data from a file where each line is expected to be in the format
    "date,percent_rate". It parses the data and stores it in a dictionary with dates as
    keys and percent rates as values.

    :param filename: The name of the file containing bond data.

    :return: A dictionary containing parsed bond data.

    :raises sys.exit(30): If the file does not exist or if there is a permission error.
    :raises Exception: If an error occurs while processing the file.
    """
    bond_data_dict = {}
    try:
        # Process the file contents here
        with open(filename, "r") as file:
            next(file)
            for line in file:
                line = line.strip()
                date, percent_rate = line.split(",")
                bond_data_dict[date] = percent_rate
    except FileNotFoundError:
        call_exit("bonds", f"The file {filename} does not exist.")
    except PermissionError:
        call_exit("bonds", "Permission denied. You don't have access to this file.")
    except Exception as e:
        call_exit("bonds", f"An error occurred: {e}")
    return bond_data_dict


def compute__account_balance(balance, rate_of_return, contribution):
    """
    Compute the account balance based on the given parameters.

    This function calculates the account balance based on the current balance, rate of
    return, and contribution amount.

    :param balance: The current balance in the account.
    :param rate_of_return: The rate of return on the investment.
    :param contribution: The contribution amount.

    :return: The computed account balance.
    """
    return balance + contribution + balance * rate_of_return


def calculate_equities(balance, rate_of_return, contribution):
    """
    Calculate the equities balance based on the given parameters.

    This function calculates the equities balance based on the current balance, rate of
    return, and contribution amount.

    :param balance: The current balance in the equities account.
    :param rate_of_return: The rate of return on equities investments.
    :param contribution: The contribution amount to equities.

    :return: The computed equities balance.
    """
    return compute__account_balance(balance, rate_of_return, contribution)


def calculate_bonds(balance, rate_of_return, contribution):
    """
    Calculate the bonds balance based on the given parameters.

    This function calculates the bonds balance based on the current balance, rate of
    return, and contribution amount.

    :param balance: The current balance in the bonds account.
    :param rate_of_return: The rate of return on bonds investments.
    :param contribution: The contribution amount to bonds.

    :return: The computed bonds balance.
    """
    return compute__account_balance(balance, rate_of_return, contribution)


def calculate_lifecycle_investment_balance(equities_balance, bonds_balance, contribution):
    """
    Calculate the lifecycle investment balance based on equities and bonds.

    This function calculates the lifecycle investment balance based on the balances of
    equities and bonds accounts and the contribution amount.

    :param equities_balance: The current balance in the equities account.
    :param bonds_balance: The current balance in the bonds account.
    :param contribution: The contribution amount.

    :return: The computed lifecycle investment balance.
    """
    return equities_balance + bonds_balance - contribution  # since contribution have been factored in twice


def write_info_to_file(start_date, contribution, to_write):
    """
    Write investment strategy information to a file.

    This function writes investment strategy information to a file, including the current
    date, balances of three investment strategies (strategy_one, strategy_two, strategy_three).

    :param start_date: The start date of the investment strategy.
    :param contribution: The monthly contribution amount for each strategy.
    :param to_write: A list of balance information for each date and strategy.

    :return: This function does not return any value.
    """
    try:
        file_to_write = open("portfolio.csv", "w")
        file_to_write.write("Date,StrategyOne,StrategyTwo,StrategyThree\n")
        file_to_write.write(f"{start_date},{contribution:.2f},{contribution:.2f},{contribution:.2f}\n")
        for balance_info in to_write:
            file_to_write.write(balance_info)
    except PermissionError:
        print("Permission denied. You don't have access to this file.")
    except Exception as e:
        print(f"An error occurred: {e}")
    file_to_write.close()


def update_January_based_parameters(contribution, strategy_three_equity_percent):
    """
    Update investment parameters based on the month of January.

    This function adjusts the contribution and equity percentage parameters based on the
    month of January during the investment strategy. It increases the contribution by 2.5%
    and decreases the equity percentage by 2% if the current month is January.

    :param contribution: The current contribution amount.
    :param strategy_three_equity_percent: The current equity percentage for strategy three.
    
    :return: Updated contribution and equity percentage values.
    """
    contribution += 0.025 * contribution
    if (strategy_three_equity_percent - 0.02 >= 0):
        strategy_three_equity_percent -= 0.02
    return contribution, strategy_three_equity_percent


def is_january(date):
    """
    Check if the given date corresponds to January.

    This function checks if the given date string corresponds to the month of January.

    :param date: The date string in "YYYY.MM" format.
    
    :return: True if the date is in January, False otherwise.
    """
    year, month = date.split(".")
    return int(month) == 1


def get_retirement_info(start_date, end_date, sp_data_dict, bonds_data_dict):
    """
    Calculate retirement information and return it as a list of balance records.

    This function calculates retirement information based on the provided investment data,
    including S&P and bond data, for a specified period. It iterates through dates, calculates
    balances for three investment strategies, and adjusts contributions based on specific conditions.

    :param start_date: The start date of retirement planning.
    :param end_date: The end date of retirement planning.
    :param sp_data_dict: A dictionary containing S&P investment data.
    :param bonds_data_dict: A dictionary containing bond investment data.
    
    :return: A list of balance records in the format "Date,StrategyOne,StrategyTwo,StrategyThree".
    """
    strategy_balances = []
    stategy_three_equity_percent = 1
    contribution = 100
    strategy_one_previous_balance = strategy_two_previous_balance = strategy_three_previous_balance = contribution

    curr_date = compute_adjacent_month(start_date, "next")
    if is_january(curr_date):
        contribution, stategy_three_equity_percent = update_January_based_parameters(
            contribution, 
            stategy_three_equity_percent
        )

    while (compare_dates(curr_date, end_date) <= 0):
        # Calculate rate_of_return for all strategies 1 and 2 
        strategy_one_rate_of_return = calculate_rate_of_return(curr_date, sp_data_dict=sp_data_dict)
        strategy_two_rate_of_return = calculate_rate_of_return(curr_date, bond_data_dict=bonds_data_dict)
        
        # Calculate balances for all three strategies at the current date
        strategy_one_curr_balance = calculate_equities(
            strategy_one_previous_balance, 
            strategy_one_rate_of_return, 
            contribution
        )

        strategy_two_curr_balance = calculate_bonds(
            strategy_two_previous_balance, 
            strategy_two_rate_of_return, 
            contribution
        )

        strategy_three_current_balance_equities = calculate_equities(
            stategy_three_equity_percent * strategy_three_previous_balance, 
            strategy_one_rate_of_return, 
            contribution
        )

        strategy_three_current_balance_bonds = calculate_bonds(
            (1 - stategy_three_equity_percent) * strategy_three_previous_balance, 
            strategy_two_rate_of_return, 
            contribution
        )
        strategy_three_curr_balance = calculate_lifecycle_investment_balance(
            strategy_three_current_balance_equities, 
            strategy_three_current_balance_bonds, 
            contribution
        )

        strategy_balances.append(
            f"{curr_date},{strategy_one_curr_balance:.2f},{strategy_two_curr_balance:.2f},"
            f"{strategy_three_curr_balance:.2f}\n"
        )
        # Update current date and adjust contribution if it's January
        curr_date = compute_adjacent_month(curr_date, "next")
        if is_january(curr_date):
            contribution, stategy_three_equity_percent = update_January_based_parameters(
                contribution, 
                stategy_three_equity_percent
            )
            
        # Update previous balances 
        strategy_one_previous_balance = strategy_one_curr_balance
        strategy_two_previous_balance = strategy_two_curr_balance
        strategy_three_previous_balance = strategy_three_curr_balance
    
    return strategy_balances


def retirement(start_date, end_date, sp_data_dict, bonds_data_dict):
    """
    Perform retirement planning based on investment data and generate a portfolio file.

    This function performs retirement planning based on the provided investment data and generates
    a portfolio file that contains information about various investment strategies over time.

    :param start_date: The start date of retirement planning.
    :param end_date: The end date of retirement planning.
    :param sp_data_dict: A dictionary containing S&P investment data.
    :param bonds_data_dict: A dictionary containing bond investment data.

    :return: This function does not return any value.
    """
    # validate every line in sp_data
    for sp_date, value in sp_data_dict.items():
        index_level, dividend = value
        sp_line = "{},{},{}".format(sp_date, index_level, dividend)
        validate_sp_data(sp_line)
    # validate every line in bonds_data
    for bonds_date, percentage_rate in bonds_data_dict.items():
        bonds_line = "{},{}".format(bonds_date, percentage_rate)
        validate_bond_data(bonds_line)
    # Get a list of the info to write and write it to portfolio.csv 
    strategy_balances = get_retirement_info(start_date, end_date, sp_data_dict, bonds_data_dict)
    write_info_to_file(start_date, 100, strategy_balances)


if __name__ == "__main__":
    if len(sys.argv) != 5:
        call_exit("command_line", "Invalid number of arguments")

    sp_data_dict = parse_sp_data(sys.argv[1])
    bond_data_dict = parse_bond_data(sys.argv[2])
    start_date = sys.argv[3]
    end_date = sys.argv[4]
    validate_date(start_date, "command_line")
    validate_date(end_date, "command_line")
    # Make sure start date isn't later than end date
    compare_date = compare_dates(start_date, end_date)
    if compare_date > 0:
        call_exit("command_line", "Start Date must not be later than End Date")

    retirement(start_date, end_date, sp_data_dict, bond_data_dict)

   
    