def print_triangle(size):
    """
    prints a triangle of a specific height and width
    
    args:
    size(int): height and width of the triangle
 
    returns:
    number of asterisks printed 
    """
    # start with star_count being 0
    star_count = 0
    # count from 0 (inclusive) to size (exclusive), for each number i that you count
    for i in range (size):
        # count from 0 (inclusive) to i (inclusive), for each number j that you count
        for j in range(i + 1):
            # print a "*"
            print("*", end="")
            # increment star_count
            star_count += 1
        # when you finish counting on j, print a new line
        print("")
    # when you finish counting on i, your answer is star_count
    return star_count


print("Here is a triangle with height 4")
num_stars = print_triangle(4)
print("That triangle had {:d} total stars".format(num_stars))

# now print "Here is a triangle with height 7"
# then call print_triangle, passing in 7, and assign the result to num_stars
# finally, print "That triangle had {:d} total stars", such that the {:d} 
# prints the value of numStars
print("Here is a triangle with height 7")
num_stars = print_triangle(7)
print("That triangle had {:d} total stars".format(num_stars))


