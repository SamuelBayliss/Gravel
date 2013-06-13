

#include <gravel/Module.h>
#include <gravel/private/Module.h>
#include <gravel/Context.h>

#include <cassert>
#include <sstream>
#include <set>

#include <boost/static_assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
   /* 
    
    Module Definition
    
    */


Gravel::Exception::ModuleNotFound::ModuleNotFound(std::string _name) : name(_name) {};

const char * Gravel::Exception::ModuleNotFound::what() const throw() { 
    std::stringstream ss;
    ss << "Module (\"" << name << "\") Not Found ";
    return ss.str().c_str();
}

Gravel::Exception::ModuleNotFound::~ModuleNotFound()  throw() { 
    
}

 /*  Gravel::Module::Module(){
       
   }
   */

  
   Gravel::Module::Module(const std::string& name) : module(Pointer::Module(new ModuleImplementation(name))) { 
    
      
       
       
   }
  
/*     Gravel::Module::Module(const Module & m) : module(m.module) {
        
    }
  */ 
     Gravel::Module::Module(Pointer::Module m ) : module(m) { 
      
     }
  
 /*  template<class T>
   class FormattedBuffer : public std::streambuf, SeparatorInterface {
   public : 
       explicit FormattedBuffer(std::ostream& sink, std::size_t buff_sz = 1);
   private:
       int_type overflow(int_type ch);
       int sync();
       
       FormattedBuffer(const FormattedBuffer &);
       FormattedBuffer & operator= (const FormattedBuffer &);
   
       
       
       std::ostream &sink_;
       std::vector<char> buffer_;
      
   };
   */
 

   
   
   /*template < class T, class S > 
   class FormattedStream {
       FormattedStream();
   };*/
   
   
   //openformattedstream -> ostream << formattedlist
   
   //openformattedstream -> openformattedstream << formattedlist 
   
   //closedformattedstream
           
  /* template <class T, class S > 
   FormattedStream<T,S> operator<< (std::ostream& os, FormattedList<T, S> fl) {
       
       return FormattedStream<T,S>(os, fl);
   }
   */
   /*
   template <class T, class S > 
   FormattedStream<T,S> operator<< (const FormattedStream<T, S> & fs, const FormattedList<T, S> & fr) {
       std::cout << "concatenated streams" << std::endl;
       return fs;
   }
   */
//   OpenFormattedList operator<<(std::ostream&,const FormattedList) {
       
//   }
   
   //operator<<()
   
   std::ostream& Gravel::Module::emit(std::ostream& os) const {
    

       os << "module " << this->getName();
       Gravel::Context * ctx = Gravel::Context::getInstance();

       
       Gravel::SymbolSet si = ctx->getSymbols(module, Gravel::Symbol::Input);
       Gravel::SymbolSet so = ctx->getSymbols(module, Gravel::Symbol::Output);
      
  
        os  << "(" << FormattedList<Comma>(si.begin(), si.end()) << FormattedList<Comma>(so.begin(), so.end()) << ");" << "\n";
      
        Gravel::SymbolSet::iterator it;
        
        for (it = si.begin() ; it != si.end() ; it++) {
            Gravel::SymbolDeclaration decl(*it);
            os << decl << "\n";
      
        }
        
        for (it = so.begin() ; it != so.end() ; it++) {
            Gravel::SymbolDeclaration decl(*it);
            os << decl << "\n";
        }
        Gravel::AssignmentSet el = ctx->getAssignments(module);

        Gravel::AssignmentSet::iterator elit;

        for (elit = el.begin() ; elit != el.end() ; elit++) {
            Gravel::Assignment assignment = *elit;
            assignment.emit(os);
        }
        
       os << "endmodule" << "\n";
       return os;
       
   }
   
    
   
   
   
   const std::string Gravel::Module::getName() const { 
       return module->getName();
   }
   
   void Gravel::Module::operator>>(Symbol& symbol) {
       
          // lookup context
       Gravel::Context * context = Gravel::Context::getInstance();
       // register a copy of the shared_ptr 
       if (!context->exists(module)) { 
        context->insert(module);
       }
       symbol.attach(module, Gravel::Interface::Symbol::Output); 
   }
   
   
   void Gravel::Module::operator<<(Symbol& symbol){
       Gravel::Context * context = Gravel::Context::getInstance();
       // register a copy of the shared_ptr 
       if (!context->exists(module)) { 
        context->insert(module);
       }
       symbol.attach(module, Gravel::Interface::Symbol::Input);
   }
   
   bool Gravel::Module::operator<(const Module & rhs) const {
    if (this->getName() < rhs.getName()) { 
        return true;
    } else if (this->getName() == rhs.getName()) {
        return (module.get() < rhs.module.get());
    }
    return false;
    
   }
   
   bool Gravel::ModuleImplementation::operator<(const ModuleImplementation & rhs) const {
    if (getName() < rhs.getName()) { 
        return true;
    } 
    return false;
   }
   
   bool Gravel::Module::operator!=(const Module & m) const {
        if (m.module == module) {
            return false;
        }
        return true;
   }
   
   bool Gravel::Module::operator==(const Module & m) const {
       if (m.module == module) { 
           return true;
       }
       return false;
   }
   
  /* Gravel::Module & Gravel::Module::operator=(const Gravel::Module & rhs) {
       if (this = &rhs) {
           return *this;
       }
       module = rhs.module;
       return *this;
   }
   */
   /*
    Module Implementation
    */
   
   Gravel::InstantiatedModule::InstantiatedModule(const std::string& name, const Gravel::Module module, const SymbolMap connections) : 
   name(name), module(module), connections(connections) { 
       
   }
   
 
   Gravel::ModuleImplementation::ModuleImplementation() { 
     assert(false);  
   }
 
   Gravel::ModuleImplementation::ModuleImplementation(const std::string& name_) : name(name_) { 
       
    
       
   }
   
     const std::string Gravel::ModuleImplementation::getName() const { 
       return name;
   }
   