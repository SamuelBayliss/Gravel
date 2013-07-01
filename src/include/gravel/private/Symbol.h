/* 
 * File:   Symbol.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 5:18 PM
 */

#ifndef SYMBOLIMPLEMENTATION_H
#define	SYMBOLIMPLEMENTATION_H

#include <gravel/private/Actor.h>

namespace Gravel { 
    
    namespace Implementation { 
   class Symbol : public Gravel::Actor {         
private:
    std::string name;
    Interface::Symbol::Direction direction;
protected:
    Symbol();
    
public:
    Symbol(const std::string&);
  
     const std::string getName() const;
     virtual Gravel::Interface::Symbol::Type getType() const;
     const Interface::Symbol::Direction getDirection() const;
     void setDirection(const Interface::Symbol::Direction& );
     std::ostream& emit(std::ostream&);
};

class RegisteredSymbol : public Gravel::Implementation::Symbol { 
public : 
    RegisteredSymbol(const std::string&);
    Gravel::Interface::Symbol::Type getType() const;
};

};

};

#endif	/* SYMBOL_H */

