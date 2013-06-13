#include <boost/test/unit_test.hpp>

#include <potholes/codegen/Generator.h>
#include <potholes/codegen/GraphUtilities.h>
#include <gravel/Context.h>

#include <cloog/cloog.h>

#include <utility>
namespace PG =  Potholes::Generator;

BOOST_AUTO_TEST_SUITE ( CodegenTest ) 

BOOST_AUTO_TEST_CASE( codegen_constructor_test)
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");


}

BOOST_AUTO_TEST_CASE( codegen_print_code )
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");

    gen.generate(PG::C);
    gen.emit(PG::C, std::cout);
}

BOOST_AUTO_TEST_CASE( codegen_print_verilog )
{
    PG::Generator gen("/Users/sb1708/Work/shared-tools/Gravel/test/input/mmm.scop");

    gen.generate(PG::Verilog);
    gen.emit(PG::Verilog,std::cout);
}


BOOST_AUTO_TEST_SUITE_END()
        
