/* 
 * File:   Context.h
 * Author: sb1708
 *
 * Created on March 25, 2013, 11:19 AM
 */

#ifndef CONTEXT_H
#define	CONTEXT_H

#include <map>
#include <vector>
#include <set>

#include <gravel/Symbol.h>
#include <gravel/private/Symbol.h>

#include <gravel/Module.h>
#include <gravel/Expression.h>
#include <gravel/Assignment.h>



namespace Gravel { 

    class InstantiatedModule;
    class ModuleImplementation;
    
    namespace Exception { 
        class OwnerNotFound : public std::exception { 
            
        };
        

        class ActorNotFound : public std::exception { 
 
        };

        
    };
    
    namespace Pointer { 
      typedef boost::shared_ptr<Gravel::Edge> Edge;
    };
    namespace Collection { 
      typedef std::set<Gravel::Pointer::Edge> Edge;
    };
    
typedef std::map<Gravel::InstantiatedModule, Gravel::Module> ModuleInstantiationMap;
typedef std::set<Gravel::Pointer::Module> ModuleSet;
typedef std::map<Gravel::Pointer::Symbol, Gravel::Pointer::Symbol> RegisteredSymbolMap;
typedef std::set<Gravel::Symbol> SymbolSet;

typedef std::set<Gravel::Pointer::Actor> ActorSet;
typedef std::map<Gravel::Pointer::Actor, Gravel::Pointer::Module> ActorMap;

typedef std::set<Gravel::Pointer::Assignment> AssignmentSet;

typedef const std::set<Gravel::Module> ConstModuleList;
typedef const std::set<Gravel::Symbol> ConstSymbolList;
typedef const std::set<Gravel::Expression> ConstExpressionList;
typedef const std::set<Gravel::Assignment> ConstAssignmentList;

typedef std::vector<Gravel::Symbol> SymbolVector;

typedef std::map<Gravel::Symbol, Gravel::SymbolVector> SymbolVectorMap;

// Module : Direction (Key for Multimap)


// Symbol (Value)



typedef std::pair<SymbolMap::iterator, SymbolMap::iterator> SymbolRange;
typedef std::pair<ConstSymbolMapIterator, ConstSymbolMapIterator> ConstSymbolRange;

typedef std::map<Gravel::Expression, Gravel::Module> ExpressionMap;
typedef ExpressionMap::iterator ExpressionMapIterator;
typedef ExpressionMap::const_iterator ConstExpressionMapIterator;

typedef std::vector<Gravel::Symbol> SymbolVector;


class Context { 
   private : 
    	static Gravel::Context * pInstance;
        ModuleSet ml;
        
        /* Should map Symbol:Module pairs to direction */
       // SymbolMap  sm;
        
        ActorSet as; // list of all unmapped actors
        ActorMap am; // map of actors to modules
        
        AssignmentSet al;
        
        RegisteredSymbolMap rm;
        //SymbolVectorMap svm;
                
        Gravel::ModuleInstantiationMap mm;
        unsigned tempIdentifier;
        
        unsigned add_edges(const Gravel::Pointer::Module& );
             // void print_actor_module_table(std::ostream& os);
             // void printSymbols(std::ostream&); // does a dump of all symbols
   protected :
	Context(); 
        
   public : 
    	static Context * getInstance();
        
        /* These are bad... remove them */
        
        //static Gravel::Module getPointer(Gravel::ModuleImplementation *);
        //static Gravel::Module getPointer(const Gravel::ModuleImplementation *);
        
        void reset(); // should clear all context without memory leaks
      
        Gravel::Collection::EdgeAnnotation getEdgeAnnotations(Gravel::Edge) const;
        Gravel::Collection::EdgeAnnotation getEdgeAnnotations(Gravel::Pointer::Module) const;
        
        Gravel::Collection::Actor getActors(Gravel::Pointer::Module module) const;
        
        Gravel::Collection::Symbol getSymbols(const Gravel::Pointer::Module&) const ;
        Gravel::Collection::Symbol getSymbols(Gravel::Pointer::Module module, Symbol::Direction direction) const;
    
    
        
        Gravel::SymbolVector getDelayedSymbols(const Gravel::Symbol&);

        Gravel::Pointer::Symbol getRegisteredSymbol(const Gravel::Pointer::Symbol& symbol );
        //ConstExpressionList getExpressions(const Gravel::Module&) const ;
        
        AssignmentSet getAssignments(const Gravel::Module&) const;
        
        std::string getUniqueIdentifier();
        
       
        Gravel::Pointer::Actor getParent(Gravel::Pointer::GraphNode);
        
        Gravel::ModuleSet getModules() const;
        
        // Registers an instantiated module against it's parent module
        // void insert(const Gravel::Module&, Gravel::InstantiatedModule);
        // Registers a 'reg' symbol
        // void insert(const Gravel::Symbol, Gravel::RegisteredSymbol); 
        // Registers a sequence of 'wire' nodes associated with an assignment (with delay > 1)
        //void insert(const Gravel::Pointer::Symbol, Gravel::SymbolVector); 
        // Registers a module
        void insert(const Gravel::Pointer::Module&);
        bool exists(const Gravel::Pointer::Module&);
         // Registers a symbol with associated module and direction
        //void insert(Gravel::Pointer::Module&, Gravel::Pointer::Symbol, const Gravel::Interface::Symbol::Direction&);
       // bool exists(const Gravel::Pointer::Module&, const Gravel::Pointer::Symbol, const Gravel::Interface::Symbol::Direction&);
        bool exists(const Gravel::Pointer::Module&, const std::string& );
        /* Inserts an actor into the actor set*/
        void insert(Gravel::Pointer::Actor actor);
        void insert(Gravel::Pointer::Actor actor, Gravel::Pointer::Module);
        void insert(const Gravel::Pointer::Assignment&);
         /* Probably Obsolete*/
        //void insert(Gravel::Pointer::Actor actor, Gravel::Pointer::GraphNode);
        /* Adds a actor into the actor map*/

        Gravel::Pointer::Module owner(const Gravel::Pointer::Actor& actor);
        bool isOwned(const Gravel::Pointer::Actor& actor);
       // Gravel::Module owner(const Gravel::Pointer::Actor& actor);
  
        

        Gravel::Module getModule(const std::string&) const;
        
        void emit(std::ostream& os);
        
        bool elaborate();
        void propagate();
        
};


};

#endif	/* CONTEXT_H */

