# Date: 2013-05-12
# Author: Karsten Ahnert (karsten.ahnert@gmx.de)

project ( PROJECT )
cmake_minimum_required ( VERSION 2.6 )

# Add path for custom modules
set( CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules
  )

  
find_package ( Boost REQUIRED )

# include_directories ( gtest gtest/include gmock gmock/include )

# add_library ( test_lib gtest/src/gtest-all.cc gtest/src/gtest_main.cc gmock/src/gmock-all.cc )
# target_link_libraries ( test_lib pthread )

set ( CMAKE_CXX_FLAGS "-std=c++11" )
set ( CMAKE_CXX_COMPILER "g++-4.8" )


include_directories ( ${Boost_INCLUDE_DIRS} )


add_executable ( main main.cpp )

enable_testing ()
# add_executable ( test_shared test_shared.cpp )
# target_link_libraries ( test_shared test_lib )
# add_test ( NAME test_shared COMMAND test_shared )