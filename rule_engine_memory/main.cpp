/*
 * main.cpp
 * Date: 2013-05-12
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#include "condition.h"
#include "shared_memory_model.h"
#include "clone_memory_model.h"
#include "unique_memory_model.h"

#include <iostream>

#define tab "    "

using namespace std;

struct test_class
{
    int value;
    
    test_class( int v ) : value( v ) { cout << "[test class] type ctor( " << v << " ) " << this << endl; }
    test_class( void ) : value( 0 ) { cout << "[test class] default ctor " << this << endl; }
    ~test_class( void ) { cout << "[test class] dtor " << this << endl; }
    test_class( const test_class &t ) : value( t.value ) { cout << "[test class] copy ctor " << this << " from " << &t << endl; }
    test_class( test_class &&t ) : value( std::move( t.value ) ) { cout << "[test class] move ctor " << this << " from " << &t << endl; }
    test_class operator=( const test_class &t ) { value = t.value; cout << "[test class] copy " << this << " from " << &t << endl; }
    test_class operator=( test_class &&t ) { value = std::move( t.value ); cout << "[test class] move " << this << " from " << &t << endl; }
};

std::ostream& operator<<( std::ostream &out , const test_class &t )
{
    out << "test_class with value " << t.value;
}



int main( int argc , char *argv[] )
{
    int context = 23;

    cout << "Testing shared memory model" << endl;
    {
        test_class t( 151 );

        condition< shared_memory_model_tag > cond1( t );
        condition< shared_memory_model_tag > cond2( cond1 );
        condition< shared_memory_model_tag > cond3( test_class( 12 ) );
        
//         cond2 = cond1;
//         cond2 = test_class( 23 );
        
//         cond1.eval( context );
//         cond2.eval( context );
        cond3.eval( context );
    }
    cout << "Finished test shared memory model" << endl << endl;
    
    
    
//     cout << "Testing cloning memory model" << endl;
//     {
//         test_class t( 151 );
// 
//         condition< clone_memory_model_tag > cond1( t );
//         condition< clone_memory_model_tag > cond2( cond1 );
//         condition< clone_memory_model_tag > cond3( test_class( 12 ) );
//         
//         cond2 = cond1;
//         cond2 = test_class( 23 );
//         
//         cond1.eval( context );
//         cond2.eval( context );
//         cond3.eval( context );
//     }
//     cout << "Finished test clone memory model" << endl << endl;
//     
//     
//     
//     
//     cout << "Testing unique memory model!" << endl;
//     {
//         test_class t( 151 );
//         
//         condition< unique_memory_model_tag > cond1( t );
//         condition< unique_memory_model_tag > cond2;
//         
//         cond1.eval( context );
//     }
//     cout << "Finished test unique memory model" << endl << endl;
//     
    
    
//     condition< copy_memory_model_tag > cond2;
//     condition< unique_memory_model_tag > cond3;
    
    
    return 0;
}
