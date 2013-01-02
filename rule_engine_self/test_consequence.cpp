/*
 * test_consequence.cpp
 * Date: 2012-11-27
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#include "consequence.h"

#include <iostream>

#define tab "\t"

using namespace std;


struct my_context { };

struct crazy_consequence { };

template< class Context >
struct run_impl< crazy_consequence , Context >
{
    static void  run( crazy_consequence &c , Context &context ) 
    {
        cout << "Crazy consequence" << endl;
    }
};


int main( int argc , char *argv[] )
{
    cout << "Hello world!" << endl;

    my_context context;
    consequence< my_context > c;
    c = crazy_consequence();

    c.run( context );

    return 0;
}
