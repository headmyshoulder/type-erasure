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
    out << "test_class " << &t << " with value " << t.value;
}



int main( int argc , char *argv[] )
{
    int context = 23;
    
    cout << endl;


    
    cout << "[TESTING SHARED DEFAULT CONSTRUCTOR]" << endl;
    {
        condition< shared_memory_model_tag > cond;
    }
    cout << "[TESTING SHARED DEFAULT CONSTRUCTOR - FINISHED]" << endl << endl;

    
    cout << "[TESTING SHARED TYPE COPY CONSTRUCTOR]" << endl;
    {
        test_class t( 151 );
        condition< shared_memory_model_tag > cond( t );
        cond.eval( context );
    }
    cout << "[TESTING SHARED TYPE COPY CONSTRUCTOR - FINISHED]" << endl << endl;

    cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR]" << endl;
    {
        test_class t( 151 );
        condition< shared_memory_model_tag > cond( std::move( t ) );
        cond.eval( context );
    }
    cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR - FINISHED]" << endl << endl;
 
    cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR II]" << endl;
    {
        condition< shared_memory_model_tag > cond( test_class( 152 ) );
        cond.eval( context );
    }
    cout << "[TESTING SHARED TYPE MOVE CONSTRUCTOR II - FINISHED]" << endl << endl;

    cout << "[TESTING SHARED COPY CONSTRUCTOR]" << endl;
    {
        condition< shared_memory_model_tag > cond1( test_class( 152 ) );
        condition< shared_memory_model_tag > cond2( cond1 );
        cond1.eval( context );
        cond2.eval( context );
    }
    cout << "[TESTING SHARED COPY CONSTRUCTOR - FINISHED]" << endl << endl;

    cout << "[TESTING SHARED MOVE CONSTRUCTOR]" << endl;
    {
        condition< shared_memory_model_tag > cond1( test_class( 152 ) );
        condition< shared_memory_model_tag > cond2( std::move( cond1 ) );
        cond1.eval( context );
        cond2.eval( context );
    }
    cout << "[TESTING SHARED MOVE CONSTRUCTOR - FINISHED]" << endl << endl;



    cout << "[TESTING SHARED COPY ASSIGNMENT]" << endl;
    {
        condition< shared_memory_model_tag > cond1( test_class( 11 ) );
        condition< shared_memory_model_tag > cond2;
        cond2 = cond1;
    }
    cout << "[TESTING SHARED COPY ASSIGNMENT - FINISHED]" << endl << endl;
    
    cout << "[TESTING SHARED MOVE ASSIGNMENT]" << endl;
    {
        condition< shared_memory_model_tag > cond1( test_class( 11 ) );
        condition< shared_memory_model_tag > cond2;
        cond2 = std::move( cond1 );
    }
    cout << "[TESTING SHARED MOVE ASSIGNMENT - FINISHED]" << endl << endl;
    
    cout << "[TESTING SHARED MOVE ASSIGNMENT II]" << endl;
    {
        condition< shared_memory_model_tag > cond;
        cond = condition< shared_memory_model_tag >( test_class( 12 ) );
    }
    cout << "[TESTING SHARED MOVE ASSIGNMENT II - FINISHED]" << endl << endl;

    
    cout << "[TESTING SHARED COPY TYPE ASSIGNMENT]" << endl;
    {
        condition< shared_memory_model_tag > cond;
        test_class t( 99 );
        cond = t;
    }
    cout << "[TESTING SHARED COPY TYPE ASSIGNMENT - FINISHED]" << endl << endl;
    
    cout << "[TESTING SHARED MOVE TYPE ASSIGNMENT]" << endl;
    {
        condition< shared_memory_model_tag > cond;
        test_class t( 99 );
        cond = std::move( t );
    }
    cout << "[TESTING SHARED MOVE TYPE ASSIGNMENT - FINISHED]" << endl;



    
    return 0;
}
