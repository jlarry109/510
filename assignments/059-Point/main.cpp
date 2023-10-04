#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include "point.hpp"

using namespace std;

/**
 * @brief moves a particular point by an adjustment value
 *  Point object updated in place.
 *  
 * @param reference to a vector of Point objects
 * @param arguments, string of number that function as the
 *        identifier for the point(an int) and the dx,dy
 *        offset (doubles) to move the point. If
 *        additional / wrong arguments specified, no action
 *        is taken except a message sent to cerr  
 */
void doMove(vector<Point> &points, string arguments) {
    stringstream sinput(arguments);

    size_t point_num = std::numeric_limits<unsigned>::max();;
    double dx = 0.0; 
    double dy = 0.0;

    if (not (sinput >> point_num >> dx >> dy)) {
        cerr << "Incorrect arguments for move: " << arguments << endl;
        return;
    }
    if (not (sinput.peek() == EOF)) {
        cerr << "Extraneous input on line: " << arguments << endl;
        return;
    }
    if ( point_num >= points.size()) {
        cerr << "Invalid valid value for point #: " << point_num << endl;
    }
    points[point_num].move(dx, dy);
}

/**
 * @brief computes the distances between two points using the Pythagorean Theorem
 *        Messsage written to standard out (cout)
 * 
 * @param reference to a vector of Point objects
 * @param arguments string containing two integer numbes that specify the two
 *        points to compute the distance between them. If
 *        additional / wrong arguments specified, no action
 *        is taken except a message sent to cerr
 */
void doDistance(vector<Point> points, string arguments) {
    stringstream sinput(arguments);

    size_t p1 = std::numeric_limits<unsigned>::max();;
    size_t p2 = std::numeric_limits<unsigned>::max();;

    if ( not (sinput >> p1 >> p2)) {
        cerr << "Incorrect arguments for distance: " << arguments << endl;
        return;
    }
    if (not (sinput.peek() == EOF)) {
        cerr << "Extraneous input on line: " << arguments << endl;
        return;
    }
    if (p1 >= points.size()) {
        cerr << "Invalide valid value for point #1: "<< p1 << endl;
        return;
    }
    if (p2 >= points.size()) {
        cerr << "Invalide valid value for point #2: "<< p2 << endl;
        return;
    }

    double d = points[p1].distanceFrom(points[p2]);
    cout << "Distance from p" << p1 << " to p" << p2 << ": " << fixed << setprecision(2) << setw(5) << d << endl;
}


/**
 * @brief Converts a string to an integer
 *        
 * Will output messages to stderr on bad conversions
 * 
 * @returns converted integer value, UINT_MAX on error 
 */
unsigned int convertStringToUnsignedInt(const string &input) {
    try {
        unsigned long result = std::stoul(input);
        if (result > std::numeric_limits<unsigned>::max()) {
            throw std::out_of_range("stou");
        }
        return result;
    }
    catch (exception &err) {
        cerr << "Conversion failure: " << input << endl;
        std::cerr << "Error occurred: " << err.what() << std::endl;
        return std::numeric_limits<unsigned>::max();
    }
}

// trim functions
// source https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
/**
 * @brief removes any whitespace from the left-side of a string. performed in-place 
 */
string& ltrim(string& s, const char* t = " \t\n\r\f\v") {
    s.erase(0, s.find_first_not_of(t));
    return s;
}

/**
 * @brief removes any whitespace from the right-side of a string. performed in-place 
 */
string& rtrim(string& s, const char* t = " \t\n\r\f\v") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

/**
 * @brief removes any whitespace from the left and side of a string. performed in-place 
 */
string& trim(string& s, const char* t = " \t\n\r\f\v") {
    return ltrim(rtrim(s, t), t);
}


/**
 * @brief uses the point class
 * 
 * input: 
 *   numpoints  (an int)
 *   0 or more commands:
 *     m pnum dx dy    move point pnum by (dx,dy)
 *     d p1 p2         print the distance between points p1 and p2
 */
int main(void) {
    string line = "";
    size_t npoints = 0;

    cout << "Enter the number of points to create: ";
    if (getline(cin,line)) {
        npoints = convertStringToUnsignedInt(line);
    }
    if (npoints <= 0 || npoints == std::numeric_limits<unsigned>::max()) {
        cerr << "Number of points must be an integer >= 0\n" << "Received: " << line << endl;
        return EXIT_FAILURE;
    }
    cout << npoints << endl;

    vector<Point> points(npoints);
    while (getline(cin, line)) {
        line = trim(line);
        if (line.length() == 0) {
            continue;
        }
        switch (line[0]) {
            case 'm': doMove(points, line.substr(1));
                    break;
            case 'd': doDistance(points, line.substr(1));
                    break;
            default: cerr <<  "Unrecognized command: " << line << endl;
        }  
    }

    return EXIT_SUCCESS;
}
