/*
 * test_shared.cpp
 * Date: 2013-05-16
 * Author: Karsten Ahnert (karsten.ahnert@gmx.de)
 */

#include "condition.h"
#include "shared_memory_model.h"


#include <sstream>

#include <gtest/gtest.h>

#define TestName test_shared

using namespace std;

typedef condition< shared_memory_model_tag > con;

TEST( TestName , test_default_construct )
{
    con c;
}

