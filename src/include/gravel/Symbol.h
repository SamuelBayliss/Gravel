/* 
 * File:   Symbol.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 4:53 PM
 */

#ifndef SYMBOL_H
#define	SYMBOL_H

#include <map>
#include <set>

#include <boost/shared_ptr.hpp>



namespace Gravel { 
    
    class Expression;
    class TermExpression;
    class BinaryExpression;
    class Module;
    class Assignment;
    class Symbol;
   
    
    namespace Implementation {
        class Symbol;
        class Constant;
    };

     namespace Pointer{
        typedef boost::shared_ptr<Gravel::Implementation::Symbol> Symbol;
        typedef boost::shared_ptr<Gravel::Implementation::Constant> Constant;
    };
    
     namespace Collection { 
        typedef std::set<Gravel::Pointer::Symbol> Symbol;
    };
    
    
};

    #include <gravel/private/Actor.h>
    #include <gravel/Assignment.h>

namespace Gravel { 

    namespace Interface { 
        class Symbol : public virtual Gravel::Interface::Actor { 
        
        public : 
            typedef enum Direction {Input, Output, Local};
            typedef enum Type {Wire, Reg};
            
            virtual const std::string getName() const = 0;
            // This function allows you to get the direction of a symbol
            virtual Type getType() const = 0;
            // These functions allow you to get the direction of a symbol
            virtual const Gravel::Interface::Symbol::Direction getDirection() const = 0;
       
        protected:
    
        };
        
    
        
    };
    
     
  
     
    



namespace Implementation { 
  class Constant : public virtual Gravel::Actor {
  public:
      Constant(int);
         Gravel::Pointer::GraphNode getOutput() const;
         Gravel::Collection::GraphNode getInputs() const;
      // set width
         void setWidth(Gravel::Pointer::GraphNode, unsigned);
  protected:
      int value;
  };
  
};
  
  class SymbolNotFoundException : std::exception { 
      
  };
  

  
    class Symbol : public Interface::Symbol, public Interface::ActorHandle { 
    private : 
        Gravel::Pointer::Symbol symbol;
        void setDirection(const Direction& );
    protected : 
        Symbol();
        
      
    public : 
       Symbol(const std::string&);
        Symbol(Gravel::Pointer::Actor);
        Symbol(Gravel::Pointer::Symbol);
        ~Symbol();
       const std::string getName() const;
          Interface::Symbol::Type getType() const;
       
          static Gravel::Pointer::Symbol Create(const std::string&);
           
       static unsigned getSymbolWidth(const Gravel::Symbol&);
       
       static bool Owned(const Gravel::Symbol&);    
       
       //static void Attach(const Gravel::Symbol&, const Gravel::Module&, const Gravel::Interface::Symbol::Direction&); 
   
       void attach(const Gravel::Pointer::Module&) const;
       void attach(Gravel::Pointer::Module&, const Gravel::Interface::Symbol::Direction&)  ;
       Gravel::Module getOwner() const;
       const Interface::Symbol::Direction getDirection() const;
       
       bool operator==(const Gravel::Symbol&) const;
        operator const Gravel::Expression() const;
  
         Gravel::Pointer::GraphNode getOutput() const;
         Gravel::Pointer::GraphNode getInput() const; // Throws Exception if there is no input, or there is > 1
        Gravel::Collection::GraphNode getInputs() const;
        
        void setWidth(Gravel::Pointer::GraphNode, unsigned);
                  
       
       Gravel::Assignment operator=(const Gravel::Expression&);
       bool operator<(const Gravel::Symbol&) const;
       Gravel::Edge operator<<(const Gravel::Symbol&) const;
       friend Gravel::Assignment Assignment::Create(const Gravel::Symbol&, const Gravel::Expression&, unsigned delay);
    };
 
   class RegisteredSymbol : public Gravel::Symbol {
   public:
        static Gravel::Pointer::Symbol Create(const std::string&);
        
        RegisteredSymbol(Gravel::Pointer::Symbol);
    };

    
    class TemporarySymbol : public Gravel::Symbol { 
    public:
        static Gravel::Pointer::Symbol Create();
        TemporarySymbol();
    };
    
    class SymbolDeclaration {
    public:
        SymbolDeclaration(const Gravel::Symbol&m, Gravel::Symbol::Direction direction);
             //   SymbolInterface::Type getType() const ;
        //const std::string getName() const;
        const Gravel::Symbol getSymbol() const;
        const Gravel::Symbol::Direction getDirection() const;
    private:
        Gravel::Symbol symbol;
        Gravel::Symbol::Direction direction;
    };
    
    typedef std::pair<Gravel::Pointer::Module, Gravel::Pointer::Symbol> SymbolKey;
    typedef std::multimap<SymbolKey, Gravel::Symbol::Direction> SymbolMap;

    
    typedef std::set<Gravel::Symbol> SymbolSet;
 
    typedef SymbolMap::const_iterator ConstSymbolMapIterator;
    std::ostream& operator<< (std::ostream& os, const Gravel::Symbol& s);
    std::ostream& operator<< (std::ostream& os, const Gravel::SymbolDeclaration& s);
    
    
    
};


#endif	/* SYMBOL_H */

