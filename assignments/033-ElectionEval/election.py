from sys import argv
import sys


def parse_state_information(filename):
    """
    Opens the state information file, loads the data, and returns it as a dictionary.

    Args:
        filename (str): The name of the state information file.

    Returns:
        dict: A dictionary containing state information with state names as keys and tuples of 
        population and electoral votes as values.
    """
    try:
        # Process the file contents here
        file = open(filename, "r")
        state_info = {}
        for line in file:
            line = line.strip()
            state_name, population, electoral_votes = line.split(":")
            state_info[state_name] = (int(population), int(electoral_votes))
    except FileNotFoundError:
        print(f"The file {filename} does not exist.")
    except PermissionError:
        print("Permission denied. You don't have access to this file.")
    except Exception as e:
        print(f"An error occurred: {e}")
    file.close()
    return state_info


def print_state_information(state_info):
    """
    Prints state information in alphabetical order.

    Args:
        state_info (dict): A dictionary containing state information.

    Prints:
        str: State information in the format: "State: Population - PopulationValue, Electoral Votes: ElectoralVotesValue".
    """
    sorted_states = sorted(state_info.keys())
    for state in sorted_states:
        population, electoral_votes = state_info[state]
        print("{}: Population - {:,d}, Electoral Votes: {:d}".format(state, population, electoral_votes))


def parse_vote_information(filename):
    """
    Opens the vote information file, loads the data, and returns it as a dictionary.

    Args:
        filename (str): The name of the vote information file.

    Returns:
        dict: A dictionary containing vote information with state names as keys and vote counts as values.
    """
    votes_info = {}
    try:
        file = open(filename, "r")
        for line in file:
            line = line.strip()
            state_name, vote_count = line.split(":")
            votes_info[state_name] = int(vote_count)
    except FileNotFoundError:
        print(f"The file {filename} does not exist.")
    except PermissionError:
        print("Permission denied. You don't have access to this file.")
    except Exception as e:
        print(f"An error occurred: {e}")

    file.close()
    return votes_info


def count_electoral_votes(state_info, vote_info):
    
    """
        Counts and returns the number of electoral votes received by Candidate A in the election.

        Args:
            state_info (dict): A dictionary containing state information.
            vote_info (dict): A dictionary containing vote information.

        Returns:
            int: The total electoral votes received by Candidate A.
    """
    electoral_votes = 0
    for state in vote_info.keys():
        if (vote_info[state] / state_info[state][0] > 0.5):
            electoral_votes += state_info[state][1]
    return electoral_votes


def determine_num_winning_votes(state_info, vote_info):
    
    """
        Determines the total electoral votes won by Candidate A and Candidate B.

        Args:
            state_info (dict): A dictionary containing state information.
            vote_info (dict): A dictionary containing vote information.

        Returns:
            int: The total electoral votes won by Candidate A.
            int: The total electoral votes won by Candidate B.
            None: if there is their electoral votes are equal.
    """
    
    # Compute country's total electoral votes by summing electoral votes across states
    total_electoral_votes = sum(value[1] for value in state_info.values())
    # Compute candidate A's total electoral votes
    candidate_a_electoral_votes_total = count_electoral_votes(state_info, vote_info)
    # Compute candidate B's total electoral vote
    candidate_b_electoral_votes_total = total_electoral_votes - candidate_a_electoral_votes_total
    if candidate_a_electoral_votes_total > candidate_b_electoral_votes_total:
        return candidate_a_electoral_votes_total
    elif candidate_a_electoral_votes_total < candidate_b_electoral_votes_total:
        return candidate_b_electoral_votes_total
    else:
        None


def determine_winner(state_info, candidate_a_electoral_votes):
    """
    Determines the election winner based on electoral votes.

    Args:
        state_info (dict): A dictionary containing state information.
        candidate_a_electoral_votes (int): The total electoral votes won by Candidate A.

    Returns:
        str: "A" if Candidate A wins, "B" if Candidate B wins, or None if it's a tie.
    """
    
    # Get total electoral votes by summing electoral votes across states
    total_electoral_votes = sum(value[1] for value in state_info.values())
    candidate_a_electoral_votes_total = count_electoral_votes(state_info, candidate_a_electoral_votes)
    candidate_b_electoral_votes_total = total_electoral_votes - candidate_a_electoral_votes_total
    if candidate_a_electoral_votes_total > candidate_b_electoral_votes_total:
        return "A"
    elif candidate_a_electoral_votes_total < candidate_b_electoral_votes_total:
        return "B"
    else:
        None


def print_winner(winner_name, number_of_votes):
    """
    Prints the election winner or a tie message.

    Args:
        winner_name (str): The winner's name ("A" or "B") or None if it's a tie.
        number_of_votes (int): The total electoral votes won by the winner.

    Prints:
        str: The winner or tie message.
    """
    if winner_name:
        print("Candidate {} wins the election with {:d} votes".format(winner_name, number_of_votes))
    else: 
        print("It's a tie in the Electoral College.")


def determine_recounts(state_info, vote_info):
    """
    Finds states that require a recount and returns a list of strings with recount information.

    Recounts are required when Candidate A is within +/- 0.5% of 50% of the votes.
    For each state that requires a recount, include a line of the form:
    "{} requires a recount (Candidate A has {:.2f}% of the vote)".
    
    Args:
        state_info (dict): A dictionary containing state information with state names as keys and tuples of total votes 
        and electoral votes as values.
        vote_info (dict): A dictionary containing vote information with state names as keys and vote counts as values.

    Returns:
        list of str: A list of recount information for states that require a recount.
    """
    states_requiring_recount = []
    for state, (total_votes, electoral_votes) in state_info.items():
        candidate_a_percentage = (vote_info[state] / total_votes) * 100
        if 49.50 <= candidate_a_percentage <= 50.50:
            states_requiring_recount.append("{} requires a recount (Candidate A has {:.2f}% of the vote)".
                                            format(state, candidate_a_percentage))
    return states_requiring_recount


def save_recounts(recount_list):
    """
    Saves recount information to a file named "recounts.txt". Entries are printed in alphabetical order.

    Args:
        recount_list (list of str): A list of recount information to be saved to the file.
    """
    recount_list = sorted(recount_list)
    file_name = "recounts.txt"
    try:
        file = open(file_name, "w")
        for line in recount_list:
            file.write(line + "\n")
        file.close()
    except FileNotFoundError:
        print(f"The file {file_name} does not exist.")
    except PermissionError:
        print("Permission denied. You don't have access to this file.")
    except Exception as e:
        print(f"An error occurred: {e}")


def determine_largest_win(state_info, vote_info):
    """
    Determines in which state Candidate A won the largest percentage of the vote.

    Returns a string with the following format:
    "Candidate A won {} with {:.2f}% of the vote"

    None is returned if candidate A did not win a state.

    Args:
        state_info (dict): A dictionary containing state information with state names 
        as keys and tuples of total votes and electoral votes as values.
        vote_info (dict): A dictionary containing vote information with state names 
        as keys and vote counts as values.

    Returns:
        str or None: A string indicating the state where Candidate A had the largest win, or None if there was no win.
    """
    largest_win_state = None
    largest_win_percentage = 0
    
    for state in vote_info.keys():
        # Compute Candidate A's percentage votes for the current state
        curr_percent_votes = 100 * (vote_info[state] / state_info[state][0])
        if curr_percent_votes > largest_win_percentage:
            largest_win_percentage, largest_win_state = curr_percent_votes, state
    if (largest_win_percentage <= 50):
        return None
    return "Candidate A won {} with {:.2f}% of the vote".format(largest_win_state, largest_win_percentage)


def process(state_info_filename, voter_info_filename):
    """
    Implements the steps for processing election information:

    1. Load and process a state information file.
    2. Print state information.
    3. Load and process the vote information file.
    4. Determine who won the election.
    5. Print the winner to the console.
    6. Determine which states require a recount.
    7. Save the recount information to a file.
    8. Determine in which state Candidate A had the largest win.
    9. Print the largest win to the console.

    Args:
        state_info_filename (str): The filename of the state information file.
        voter_info_filename (str): The filename of the vote information file.
    """
    state_info = parse_state_information(state_info_filename)
    print_state_information(state_info)
    vote_info = parse_vote_information(voter_info_filename)
    winner = determine_winner(state_info, vote_info)
    num_win_votes = determine_num_winning_votes(state_info, vote_info)
    print_winner(winner, num_win_votes)
    recount_states = determine_recounts(state_info, vote_info)
    save_recounts(recount_states)
    largest_win_info = determine_largest_win(state_info, vote_info)
    if largest_win_info:
        print(largest_win_info)
    else:
        print("None")

if __name__ == "__main__":
    """Implement checking command line arguments, call process()
    """
    if len(sys.argv) != 3:
        print("Invalid number of arguments supplied")
        exit(101)
    process(argv[1], argv[2])
