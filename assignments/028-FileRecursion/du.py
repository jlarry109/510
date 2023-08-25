import sys
import os


def du(file):
    """
    From the given directory produce output similar to the linux command: du -ac
    However rather than the number of blocks the size of the files and directories
    should be printed
    
    returns: size of the given directory and all of its subdirectories/files
    """


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python du.py directory")
        sys.exit(2)
    total_size = du(sys.argv[1])
    # print the total line

