

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


Gravel::ModuleNotFound::ModuleNotFound(std::string _name) : name(_name) {};

const char * Gravel::ModuleNotFound::what() const throw() { 
    std::stringstream ss;
    ss << "Module (\"" << name << "\") Not Found ";
    return ss.str().c_str();
}

Gravel::ModuleNotFound::~ModuleNotFound()  throw() { 
    
}

 

   Gravel::Module::Module(){
       
   }
   
   Gravel::Module::Module(const std::string& name) : module(ModulePtr(new ModuleImplementation(name))) { 
    
       
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
       
       Gravel::ConstSymbolRange si = ctx->getSymbols(*this, Gravel::Symbol::Input);
       Gravel::ConstSymbolRange so = ctx->getSymbols(*this, Gravel::Symbol::Output);
      
  
        os  << "(" << FormattedList<Comma>(si.first, si.second) << FormattedList<Comma>(so.first, so.second) << ");" << "\n";
      
        Gravel::ConstSymbolMapIterator it;
        
        for (it = si.first ; it != si.second ; it++) {
            Gravel::SymbolDeclaration decl(it->second);
            os << decl << "\n";
      
        }
        
        for (it = so.first ; it != so.second ; it++) {
            Gravel::SymbolDeclaration decl(it->second);
            os << decl << "\n";
        }
        Gravel::ConstExpressionList el = ctx->getExpressions(*this);

        Gravel::ConstExpressionList::iterator elit;
        
        for (elit = el.begin() ; elit != el.end() ; elit++) {
            Gravel::Expression expression = *elit;
            os << expression << "\n";
        }
        
       os << "endmodule" << "\n";
       return os;
   }
   
   const std::string Gravel::Module::getName() const { 
       return module->getName();
   }
   
   void Gravel::Module::operator>>(Symbol& gs) {
       
          // lookup context
       Gravel::Context * context = Gravel::Context::getInstance();
       // register a copy of the shared_ptr 
       if (!context->exists(*this)) { 
        context->insert(*this);
       }
       context->insert(*this, gs, Gravel::Interface::Symbol::Output);
       
   }
   void Gravel::Module::operator<<(Symbol& gs){
       Gravel::Context * context = Gravel::Context::getInstance();
       // register a copy of the shared_ptr 
       if (!context->exists(*this)) { 
        context->insert(*this);
       }
         context->insert(*this, gs, Gravel::Interface::Symbol::Input);
   }
   
   bool Gravel::Module::operator<(const Module & rhs) const {
    if (this->getName() < rhs.getName()) { 
        return true;
    } else if (this->getName() == rhs.getName()) {
        return (module.get() < rhs.module.get());
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
   
   
   /*
    Module Implementation
    */
   
   Gravel::ModuleInstantiation::ModuleInstantiation(const std::string& name, const Gravel::Module module, const InputMap inputs) : 
   name(name), module(module), inputs(inputs) { 
       
   }
   
   
  
   Gravel::ModuleImplementation::ModuleImplementation() { 
     assert(false);  
   }
 
   Gravel::ModuleImplementation::ModuleImplementation(const std::string& name_) : name(name_) { 
     
   }
   
     const std::string Gravel::ModuleImplementation::getName() { 
       return name;
   }
   