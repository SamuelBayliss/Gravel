
#include <potholes/codegen/Module.h>
#include <potholes/codegen/Generator.h>

Potholes::Generator::Module::Module(clast_stmt* stmt) : Gravel::ModuleImplementation(Potholes::Generator::create_unique_module_name(stmt)){ 
  
    
}

      void Potholes::Generator::Module::register_symbols() {
          
         // Gravel::Context * ctx = Gravel::Context::getInstance();
          
          Gravel::Module mod = Gravel::Context::getPointer(this);
          
          // register the control path symbols
          
           Gravel::Symbol clk("clk");
        mod << clk;
        Gravel::Symbol reset("reset");
        mod << reset;
          
          Gravel::Symbol guard_in("guard_in");
          mod << guard_in;
          Gravel::Symbol guard_out("guard_out");
          mod >> guard_out;
          Gravel::Symbol update_in("update_in");
          mod << update_in;
          Gravel::Symbol update_out("update_out");
          mod >> update_out;
     
        }
        void Potholes::Generator::Module::build_chain() { 
            
        }

    
          