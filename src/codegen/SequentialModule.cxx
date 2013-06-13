#include <potholes/codegen/SequentialModule.h>

Potholes::Generator::SequentialModule::SequentialModule(clast_stmt * stmt) : Potholes::Generator::Module(stmt) {
 
    std::cout << "Seq" << "\n";
    
}

       void Potholes::Generator::SequentialModule::register_symbols() {
                
            }
            void Potholes::Generator::SequentialModule::build_chain() {
                
            }