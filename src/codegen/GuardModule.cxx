

#include <potholes/codegen/GuardModule.h>



Potholes::Generator::GuardModule::GuardModule(clast_stmt * stmt) : Potholes::Generator::Module(stmt) {
    
       std::cout << "Guard" << "\n";
    
}

         void Potholes::Generator::GuardModule::register_symbols() {
                
            }
            void Potholes::Generator::GuardModule::build_chain() {
                
            }