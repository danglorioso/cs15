/*
 * got_int.cpp
 *
 * Author:  Mark A. Sheldon, Tufts University, Fall 2016
 *
 * A function that will tell you whether a string can be interpreted
 * as a integer number, and, if so, give the
 * value.  
 *
 * There is a simple main program to illustrate the use of the
 * got_int() function.
 *
 * To use the function, you must include "cstdio" as shown.
 * Because the function uses C++ strings, you must include
 * "string" or something that includes "string", like "iostream".
 *
 * The got_int() function illustrates an interesting technique.  The
 * function needs to return two values, but in C/C++ a function can
 * only return one value.  What to do?  There are two choices:
 *
 *      a) Return a struct with two things in it.  We're not doing
 *         that here.
 *      b) Return one item via the normal return value, and get the
 *         other item to the caller by using call-by-reference (CBR).
 *         In C++, arguments to functions are generally passed by
 *         value, i. e., the argument value is *copied* into the
 *         parameter before the function body is run.  
 *         With call-by-reference, the callee and caller actually
 *         share the same variable, which allows the called function
 *         to modify a variable in the caller.
 *
 *         CBR can be done in two ways in C++, but, because we're
 *         practicing with pointers, I'm doing it with pointers here.
 *         Also, when you program in C, this is what you'll have to do. 
 *
 * It is VERY important that you be able to draw an accurate stack
 * diagram that illustrates how this function works.  You don't have
 * to understand sscanf() beyond what is explained below.  If you have
 * any questions, please come talk to one of us.
 *
 * A more native C++ technique would use stringstreams, which is also
 * interesting.  This was what I wrote first.
 *
 **************************************************************************
 * Change log:
 *     2017-fall   [Aubrey Anderson] edits to comments
 *     2020-02-21  [MAS] 
 *                 - made got_int return false if extra
 *                   non-whitespace characters are provided after
 *                   digits
 *                 - made output cleaner by computing field width for
 *                   test cases
 **************************************************************************
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

size_t max_length(char *c_strs[], int len);

/*
 * Return true if the string s can be interpreted as an integer
 * number, placing the associated integer into the location pointed to by
 * resultp.
 *
 * Return false if s cannot be interpreted as an integer leaving the
 * location pointed to by resultp unmodified.
 *
 * The input string can be interpreted as an iteger if it has an
 * optional sign and then a sequence of decimal digits with no
 * following characters, except for white space.
 *
 * Examples:  
 *      "135"      will yield an integer
 *      "-94"      will yield an integer
 *      "-12 "     will yield an integer (trainling whitespace is allowed)
 *      "banana"   will not yield an integer
 *      "4flowers" will not yield an integer (non-whitespace after integer)
 *      "18 x"     will not yield an integer (non-whitespace after integer)
 *
 * Implementation note to students:
 *
 *     sscanf() reads characters from the first C string it's given
 *     trying to match them against the "format specifiers" in the
 *     second C string.  In the case below, "%d" means "decimal,"
 *     which is the format for base 10 integers.  "%c" means
 *     "character".  The "%d %c" means "try to match a decimal
 *     integer, any amount of white space (including none) and then a
 *     single character.  We don't want any non-whitespace characters
 *     after the decimal digits.
 *
 *     sscanf() returns the number of successful matches, and stores
 *     the converted values in the locations pointed to by the
 *     remaining arguments.  In this case, if the C string from s can
 *     be interpreted as representing an integer, the integer value is
 *     placed in the location pointed to by resultp.  If there are 1
 *     or more non-whitespace characters after the integer, then the
 *     first such character is store in extra.  If only the integer
 *     matches, sscanf() returns 1, which causes got_int() to return
 *     true.  If sscanf() does not get a successful match, it will
 *     return 0.  If it matches both, it will return 2, which will
 *     cause got_int() to return false.
 *     Interesting case:  if the first match fails, sscanf()
 *     returns 0, which presumably means it doesn't try the second
 *     conversion. 
 */
bool got_int(string s, int *resultp)
{
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * This main function illustrates a way to use got_int() above.
 * If you compile this file and run the result, you can use the
 * program like this:
 * 
 *    $ ./got_int 1 -35 894 hi_mom 99999999999 3birds "-2  " "18 x" b1 \
 *                "c 8" "xy z"
 *    "1"            is an int with value 1
 *    "-35"          is an int with value -35
 *    "894"          is an int with value 894
 *    "hi_mom"       is not an int :-(
 *    "99999999999"  is an int with value 1215752191
 *    "3birds"       is not an int :-(
 *    "-2  "         is an int with value -2
 *    "18 x"         is not an int :-(
 *    "b1"           is not an int :-(
 *    "c 8"          is not an int :-(
 *    "xy z"         is not an int :-(
 *    "   55"        is an int with value 55
 *    " -4  "        is an int with value -4
 *    " 3 x"         is not an int :-(
 *    $ 
 *
 * Take note of the technique of using command line arguments to test
 * something.  It's very handy, because you can test the function on a
 * variety of inputs without recompiling or having to feed it inputs
 * from the keyboard.  
 *
 * This was how I actually tested the function, though there were
 * quite a few tests before the one illustrated above.  The tests
 * above show numbers positive and negative numbers, non-numbers of 
 * length 1 and 6, and zero.
 */

int main(int argc, char *argv[])
{
        int value, test_field_width;

        if (argc < 2)       // quit with no error
                return 0;   // if nothing to do
        
        // accommodate longest test string from command line
        // leaving room for two double quotes and two spaces
        test_field_width = max_length(&argv[1], argc - 1) + 4;

        for (int i = 1; i < argc; ++i) {
                cout << setw(test_field_width) << left
                     << ('"' + string(argv[i]) + '"');
                if (got_int(argv[i], &value))
                        cout << "is an int with value " << value;
                else
                        cout << "is not an int :-(";

                cout << endl;
        }
        return 0;
}

/*
 * Return length of longest C-style string in the array of C strings.
 *
 * NOTE:  Requires len > 0:   it is an unchecked error for len <= 0
 */
size_t max_length(char *c_strs[], int len)
{
        size_t max_so_far = strlen(c_strs[0]);

        for (int i = 1; i < len; ++i)
                max_so_far = max(max_so_far, strlen(c_strs[i]));
        return max_so_far;
}
