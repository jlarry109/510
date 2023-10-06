import sys

import os

 

 

def du_helper (filename):

    # if not os.path.isdir(filename) or not os.listdir(filename):

    # If filename is not a directory, the call to os.listdir(filename) can raise a NotADirectoryError.

    # So, if filename is not a directory, you'll never get to the second condition because the error would halt the execution.

    if (not os.path.isdir(filename)) : # The base case

        try:

            filesize_bytes = os.path.getsize(filename)

            print("{}\t{}".format(filesize_bytes, filename))

            return filesize_bytes

        except Exception as e:

            print("Couldn't get file size in Bytes:", str(e))

 

    else:
        filesize_bytes = os.path.getsize(filename)
        subfiles = os.listdir(filename)
        for subfile in subfiles:
            subfilename = os.path.join(filename, subfile)
            filesize_bytes += du_helper(subfilename)
        print("{}\t{}".format(filesize_bytes, filename))

        return filesize_bytes

 

def du(file):

    """
    From the given directory produce output similar to the linux command: du -ac
    However rather than the number of blocks the size of the files and directories
    should be printed
    returns: size of the given directory and all of its subdirectories/files

    """

    total = du_helper(file)

    print("{}\t{}".format(total, "total"))

    return total

#get path to parent directory of current file = os.path.getsize(os.path.abspath(os.path.join(curr_file, os.pardir)))
 
if __name__ == "__main__":

    if len(sys.argv) != 2:

        print("Usage: python du.py directory")

        sys.exit(2)

    total_size = du(sys.argv[1])

 

    # print the total line
