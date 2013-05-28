
#include <potholes/codegen/Module.h>
#include <potholes/codegen/Generator.h>

Potholes::Generator::Module::Module(clast_stmt* stmt) : Gravel::ModuleImplementation(Potholes::Generator::create_unique_module_name(stmt)){ 
  
    
}