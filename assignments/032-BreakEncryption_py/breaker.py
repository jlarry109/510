from curses.ascii import isalpha
import sys
from sys import argv
import os

def build_histogram(freq, file):
    while True:
        c = file.read(1)
        if not c: break     

        if c.isalpha():
            c = c.lower()
            c = ord(c)
            c -= ord('a')
            freq[c] += 1
            
    return freq
def is_max_frequency(freq):
    max_freq = max(freq)
    count = freq.count(max_freq)
    if (count > 1):
        print("No char with max Frequency")
        sys.exit(1)

def get_highest_freq(freq):
    maxfreq = 0
    maxchar = 0
    for i in range(26): 
        if (freq[i] >= maxfreq):
            maxfreq = freq[i]
            maxchar = i
    if (maxfreq == 0):
        return -1
    else:
        return maxchar
    
if __name__ == "__main__":
    if len(argv) != 2:
        print("Usage: python3 breaker.py input_file_name")
        sys.exit(1)
    freq =  []
    for i in range(26):
        freq.append(0)
    try:
        file = open(argv[1], "r")
        build_histogram(freq, file)
        is_max_frequency(freq)
        heighest = get_highest_freq(freq)
        if (heighest < 0):
            print("Empty File")
            sys.exit(1)
        print((heighest + 26 - 4) % 26)
    except FileNotFoundError:
        print(f"The file {argv[1]} does not exist.")
        sys.exit(1)
    except PermissionError:
        print("Permission denied. You don't have access to this file.")
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred: {e}")
        sys.exit(1)