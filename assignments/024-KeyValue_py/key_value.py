import sys
from sys import argv

def read_key_values(filename):
    """
    Reads a key-value delimited file (separated by first =) into a dictionary

    Args:
    filename(str): name of the file to read
    
    Returns:
    dictionary of the read items
    """
    key_val =  {}
    try:
        file = open(filename, "r")
    except Exception as e:
        print("Unable to open key_values file:", str(e))
        return
    for line in file:
        line = line.strip()
        line_list = line.split("=", 1) #split line by the first equal sign
        key_val[line_list[0]] = line_list[1]
    file.close()
    return key_val

def create_output_filename(name):
    """
    create the output file name.  Given an input filename such as "input.txt",
    return "input.txt.counts"
    """
    return name + ".counts"
    

def process_key_file(filename,key_values):
    """
    Loads in a key file and produces a dictionary of the count of the values 
    If a key is not found in key_values use "<unknown>"

    Args:
    filename(str): file containing keys to process
    key_values(dict): existing keys to load
    """
    key_count = {}
    try:
        file = open(filename, "r")
    except Exception as e:
        print("Unable to open key_file file: ", str(e))
        return
    for line in file:
        line = line.strip()
        if key_values.get(line) != None:
            value_to_key = key_values[line]
            key_count[value_to_key] = key_count.get(value_to_key, 0) + 1
        else:
            key_count["<unknown>"] = key_count.get("<unknown>", 0) + 1
    file.close()
    return key_count

def write_output(filename,counts):
    """
    Sort the output value the highest count descending. If two values are
    equal, arbitrarily choose 1
    """
    
    sorted_counts = sorted(counts.items(), key=lambda x: x[1], reverse=True)
    try:
        file = open(filename, "w")
        for key, value in sorted_counts:
            file.write("{}: {}\n".format(key, value))
    except Exception as e:
        print("Unable to open.count file for write:", str(e))
    file.close()
    
def process(args):
    """
    Implement your algorithm in this function
    foreach of the 2nd type of input files, output a count file
Algorithm: (this is largely the contents/outline of "process")

get the filename of first argument
load the contents in a dictionary
for each of the remaining files
create a new dictionary to store the "value" and number of occurrences (i.,e "counts" dictionary)
read the file
foreach line
get the corresponding value from the first dictionary
update the counts dictionary
output counts file
    """
    # print(args)   #Uncomment if you want to validate/see the command-line arguments
    filename1 = args[1]
    key_values = read_key_values(filename1)
    for i in range(2,len(args)):
        key_count = process_key_file(args[i], key_values)
        output_filename = create_output_filename(args[i])
        write_output(output_filename, key_count)
        
# __name__ == "__main__" and argv explained in the "modules" notebook
if __name__ == "__main__":
    if len(argv) < 3:
        print("Usage: python3 key_value.py file1_name file2_name ...")
        sys.exit(-1)
    #print("argv[0] is" + argv[1])
    process(argv)
