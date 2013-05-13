#include <boost/test/unit_test.hpp>

#include <gravel/test/SimulateFixture.h>

BOOST_FIXTURE_TEST_SUITE ( SimulateTest , SimulateFixture ) 

BOOST_AUTO_TEST_CASE( simulate_constructor_test )
{
    
    std::string rtl_filename = "/tmp/top.v";
    
    bool success = this->CompileSimulation(rtl_filename);
    BOOST_CHECK(success);
            
}

BOOST_AUTO_TEST_SUITE_END()
        
/*
 
 * Use a pre-built shim to connect into testbench
 
 
 
 */