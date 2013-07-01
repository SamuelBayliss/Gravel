/* 
 * File:   Assignment.h
 * Author: sb1708
 *
 * Created on May 29, 2013, 9:20 PM
 */

#ifndef ASSIGNMENT_H
#define	ASSIGNMENT_H

//#include <gravel/Expression.h>
//#include <gravel/Symbol.h>

namespace Gravel { 
    
    class Expression;
    class Symbol;
   
    
    namespace Implementation {
        class Symbol;
        class Constant;
        class Expression;
    };

     namespace Pointer{
        typedef boost::shared_ptr<Gravel::Implementation::Symbol> Symbol;
        typedef boost::shared_ptr<Gravel::Implementation::Constant> Constant;
        typedef boost::shared_ptr<Gravel::Implementation::Expression> Expression;
    };
    
     namespace Collection { 
        typedef std::set<Gravel::Pointer::Symbol> Symbol;
    };
    
    
};


namespace Gravel { 
    
    namespace Interface { 
        class Assignment { 
                  virtual void emit(std::ostream& os) = 0;
                  virtual Gravel::Collection::Symbol get_assigned_symbols() const = 0;
                  
        };
    };
    
    namespace Implementation { 
      class Assignment;  
    };
    
    namespace Pointer { 
        typedef boost::shared_ptr<Gravel::Implementation::Assignment> Assignment;
    }
    
    class Assignment {
    public:
  
         static Gravel::Assignment Create(const Gravel::Symbol&, const Gravel::Expression&, unsigned delay = 0);
         
         typedef std::map<Gravel::Pointer::Symbol, Gravel::Pointer::Expression> AssignmentMap;
         typedef std::pair<Gravel::Pointer::Symbol, Gravel::Pointer::Expression> AssignmentPair;
    private:
        Gravel::Pointer::Assignment assignment;
    public:
        bool operator<(const Gravel::Assignment&) const;
        virtual void emit(std::ostream& os);
         Gravel::Collection::Symbol get_assigned_symbols() const;
         void set_delay(unsigned);
        Assignment(Gravel::Pointer::Assignment);
        
    };
    
    namespace Implementation { 
        
        class Assignment : public Gravel::Interface::Assignment { 
        private : 
             unsigned delay;
             Gravel::Assignment::AssignmentMap normal;
             Gravel::Assignment::AssignmentMap reset; 
        public:
          virtual void emit(std::ostream& os);
          Gravel::Collection::Symbol get_assigned_symbols() const;
          void set_delay(unsigned);
          void propagate();
          Assignment(Gravel::Pointer::Symbol&, Gravel::Pointer::Expression&, unsigned delay);
        };
        
        class CompoundAssignment : public Gravel::Assignment {
    public : 
        CompoundAssignment(unsigned delay = 0);
        void insert(Gravel::Symbol, Gravel::Expression);
        virtual void emit(std::ostream& os);
    private : 
        
    };
    
    class ConditionalAssignment : public Gravel::Assignment {
    public:
         virtual void emit(std::ostream& os);
    private : 
        Gravel::Pointer::Expression condition;
    };
      
    };
    
};


#endif	/* ASSIGNMENT_H */

