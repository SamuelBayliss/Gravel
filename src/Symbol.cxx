
#include <gravel/Symbol.h>
#include <gravel/private/Symbol.h>

 Gravel::Symbol::Symbol() {
     
 }

 Gravel::Symbol::Symbol(const std::string& name_) : symbol(new Gravel::SymbolImplementation(name_)) {
     
 }
    const std::string Gravel::Symbol::getName() const {
        return symbol->getName();
    }
    
    
 Gravel::SymbolImplementation::SymbolImplementation(const std::string& name_) : name(name_) { 
     
 }
 
const std::string Gravel::SymbolImplementation::getName() const {
    return name;
}

bool Gravel::Symbol::operator==(const Gravel::Symbol& sm) const {
    return (getName() == sm.getName());
    
}

std::ostream& Gravel::operator<< (std::ostream& os, const Gravel::Symbol& s) {
    os << s.getName();
}