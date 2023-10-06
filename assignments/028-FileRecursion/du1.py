import sys
import os

def du_helper (filename, total):
    
    if not os.path.isdir(filename) or not os.listdir(filename):
        try:
            filesize_bytes = os.path.getsize(filename)
            total += filesize_bytes
            print("{}\t{}".format(filesize_bytes, filename))
            return total
        except Exception as e:
            print("Couldn't get file size in Bytes:", str(e))
    
    else:
        subfiles = os.listdir(filename)
        for subfile in subfiles:
            subfilename = os.path.join(filename, subfile) 
            total = du_helper(subfilename, total)
        return total
    
def du(file):
    """
    From the given directory produce output similar to the linux command: du -ac
    However rather than the number of blocks the size of the files and directories
    should be printed
    
    returns: size of the given directory and all of its subdirectories/files
    """
    total = 0 
    total = du_helper(file, total)
    print("{}\t{}".format(total, "total"))
    
#get path to parent directory of current file = os.path.getsize(os.path.abspath(os.path.join(curr_file, os.pardir)))

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python du.py directory")
        sys.exit(2)
    total_size = du(sys.argv[1])
    # print the total line

