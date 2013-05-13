


#include <boost/test/unit_test.hpp>

#include <gravel/Context.h>
#include <gravel/Module.h>

#include <gravel/Symbol.h>
#include <gravel/Context.h>

#include <gravel/Module.h>

#include <gravel/private/Module.h>

#include <cassert>

#include "gravel/Context.h"

BOOST_AUTO_TEST_SUITE ( ModuleTest )

BOOST_AUTO_TEST_CASE( module_constructor_test)
{
    const std::string name = "MyModule";
    Gravel::Module module(name);
    
    BOOST_CHECK(module.getName() == name);    
}


/*
BOOST_AUTO_TEST_CASE ( module_emit_mixed_separator_test) {
    
    
}
*/

BOOST_AUTO_TEST_CASE ( module_add_symbol_test ) {
    
    const std::string name = "MyModule";
    Gravel::Context * ctx;
    ctx = Gravel::Context::getInstance();
    BOOST_CHECK( ctx != NULL );
    BOOST_CHECK_EQUAL(ctx->getModules().size(), 0);
    
    {
    
        Gravel::Module module(name);
        const std::string input_name = "Input";
        Gravel::Symbol in("Input");
        BOOST_CHECK_EQUAL(in.getName(),input_name);
     
         const std::string output_name = "Output";
           Gravel::Symbol out(output_name);
        BOOST_CHECK_EQUAL(out.getName(),output_name);
            BOOST_CHECK_EQUAL(ctx->getModules().size(), 0);
        module << in;
           BOOST_CHECK_EQUAL(ctx->getModules().size(), 1);
        module >> out;
    }
        

    ctx = Gravel::Context::getInstance();
    BOOST_CHECK( ctx != NULL );
    
    BOOST_CHECK_EQUAL(ctx->getModules().size(), 1);
 
    try {
        Gravel::Module module = ctx->getModule(name);
        std::stringstream ss;
        module.emit(ss);
        
    } catch (Gravel::ModuleNotFound& e) { 
        
    }

   
   // ctx->emit(std::cout);
    
/*
          const std::vector<const Gravel::Symbol> inputs =  module.getSymbols(SymbolDirection::Input);
    const std::vector<const Gravel::Symbol> outputs = module.getSymbols(SymbolDirection::Output);
    const std::vector<const Gravel::Symbol> locals = module.getSymbols(SymbolDirection::Local);
    
    BOOST_CHECK_EQUAL(inputs.size(), 1);
    BOOST_CHECK_EQUAL(outputs.size(), 1);
    BOOST_CHECK_EQUAL(locals.size(), 0);
 */
}


BOOST_AUTO_TEST_CASE ( module_emit_symbol_test ) {
    
    const std::string name = "ModuleEmitSymbolTest";
    Gravel::Context * ctx;
    ctx = Gravel::Context::getInstance();
    {
        Gravel::Module mymodule(name);
          const std::string input_name = "Input";
          Gravel::Symbol in(input_name);
          const std::string output_name = "Output";
          Gravel::Symbol out(output_name);
          mymodule << in;
          mymodule >> out;
          std::stringstream ss;
          mymodule.emit(ss);
          
       
           BOOST_CHECK_EQUAL ( ss.str(), "module " + name + "(" + output_name + ");\nendmodule\n");
  
    }
}

bool no_check( Gravel::MixedSeparatorException const& ex ) { return true; }
    
BOOST_AUTO_TEST_CASE ( formatted_list_fail_test ) {
    
    const std::string name = "ModuleEmitSymbolTest";
    Gravel::Context * ctx;
    ctx = Gravel::Context::getInstance();
    Gravel::Module mod = ctx->getModule(name);
  
       Gravel::ConstSymbolRange si = ctx->getSymbols(mod, Gravel::Symbol::Input);
       Gravel::ConstSymbolRange so = ctx->getSymbols(mod, Gravel::Symbol::Output);
      
       std::stringstream ss;
      

       BOOST_CHECK_EXCEPTION(ss  << "(" << Gravel::FormattedList<Gravel::Comma>(si.first, si.second) << Gravel::FormattedList<Gravel::Semicolon>(so.first, so.second);, Gravel::MixedSeparatorException, no_check);
       
     
    
    
}


BOOST_AUTO_TEST_CASE ( formatted_list_succeed_test ) {
    const std::string name = "ModuleEmitSymbolTest";
    Gravel::Context * ctx;
    ctx = Gravel::Context::getInstance();
    Gravel::Module mod = ctx->getModule(name);
  
       Gravel::ConstSymbolRange si = ctx->getSymbols(mod, Gravel::Symbol::Input);
       BOOST_CHECK(si.first != si.second);
       Gravel::ConstSymbolRange so = ctx->getSymbols(mod, Gravel::Symbol::Output);
       BOOST_CHECK(so.first != so.second);
       std::stringstream ss;
       
       ss  << "(" << Gravel::FormattedList<Gravel::Comma>(si.first, si.second) << Gravel::FormattedList<Gravel::Comma>(so.first, so.second) << ")";
     
}

BOOST_AUTO_TEST_SUITE_END()