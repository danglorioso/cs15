#include <iostream>
#include <vector>

#include "Datum.h"

using namespace std;

int main(int argc, char *argv[])
{
        (void) argc;  // Tell compiler purposely not using argc: avoid warning

        string program_name = argv[0];
        // Cannot do the following, which requires the default constructor
        // but there isn't one
        // Datum d;

        // The following all work fine
        Datum int_datum(3);
        Datum bool_datum(false);
        Datum rstring_datum("Iron Butterfly");

        // Interestingly, C++ vectors can work fine with Datum instances
        vector<Datum> datum_vector;

        datum_vector.push_back(int_datum);
        datum_vector.push_back(bool_datum);
        datum_vector.push_back(rstring_datum);
        datum_vector.push_back(Datum("{ " + program_name + " }"));

        cout << "[ ";
        for (Datum d : datum_vector)
                cout << d.toString() << ' ';
        cout << ']' << endl;

        return 0;
}
