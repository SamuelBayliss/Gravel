/* 
 * File:   Actor.h
 * Author: sb1708
 *
 * Created on March 26, 2013, 11:40 AM
 */

#ifndef ACTOR_H
#define	ACTOR_H

#include <map>
#include <set>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>



namespace Gravel { 
    /* Actors can be Symbols or Expressions */
    /* Symbols with only an output are constants */
    /* Symbols with input and output can be registered */
    typedef enum GraphEdgeDirection {Input, Output};
    
    class Actor;
    class Symbol;
    class Module;
    class GraphNode;
    class ModuleImplementation;
    
    
    namespace Interface{
        class Actor;
    };
   
    namespace Pointer{
        typedef boost::shared_ptr<Gravel::Actor> Actor; 
        typedef boost::shared_ptr<Gravel::GraphNode> GraphNode;
        typedef boost::shared_ptr<Gravel::ModuleImplementation> Module;
       
    };
    namespace WeakPointer { 
        typedef boost::weak_ptr<Gravel::GraphNode> GraphNode;
    }
    

    
    class GraphNode { 
   
    public :     
        
          typedef std::multimap<GraphEdgeDirection, Gravel::Pointer::GraphNode > NodeMap;
          typedef std::pair<GraphEdgeDirection, Gravel::Pointer::GraphNode > NodePair;
          typedef NodeMap::const_iterator ConstNodeIterator;
           typedef NodeMap::iterator NodeIterator;
       
          typedef std::pair<NodeIterator, NodeIterator> NodeRange;
          typedef std::pair<ConstNodeIterator, ConstNodeIterator> ConstNodeRange;
          
          
          
          typedef std::map<Gravel::WeakPointer::GraphNode, Gravel::WeakPointer::GraphNode> BackMap;
           typedef std::pair<Gravel::WeakPointer::GraphNode, Gravel::WeakPointer::GraphNode> BackMapPair;
          typedef BackMap::iterator BackMapIterator;
          typedef std::pair<BackMapIterator, BackMapIterator> BackMapRange;
         
          typedef std::map<Gravel::WeakPointer::GraphNode, Gravel::Pointer::Actor> ParentMap;
        
        // Destructor
        ~GraphNode();
        
        // points to implementation (which is an actor)

        static Gravel::Pointer::Actor getParent(Gravel::Pointer::GraphNode);
        static Gravel::Pointer::Actor getParent(Gravel::GraphNode::ConstNodeIterator);
         
     
         
         static BackMapRange getConnections(Gravel::Pointer::GraphNode);
         
        // Graph Node destructor removes back-link and removes from ring
        static void connect(Gravel::Pointer::GraphNode, Gravel::Pointer::GraphNode);
        unsigned getWidth();
        // Default Constructor
        static Gravel::Pointer::GraphNode Create(Gravel::GraphNode::NodeMap&, const Gravel::GraphEdgeDirection&);
         private: 
                 GraphNode();
        unsigned width;
        
        static BackMap back;
        
       
        
        
        // Copy Constructor is declared but not implemented
        
        // Equality Assignment is declared but not implemented
    };
    
     namespace Collection { 
        typedef std::pair<Gravel::GraphNode::ConstNodeIterator, Gravel::GraphNode::ConstNodeIterator> GraphNodeRange;
        typedef std::set<Gravel::Pointer::Actor> Actor;
    }
    
    
     namespace Exception { 
         class GraphNodeNotFound : public std::exception { 
             
         };
     }
     
    namespace Interface { 
        
    class Actor { 
       public:
      //  std::set<Gravel::GraphNode> getInputs();
       virtual Gravel::Pointer::GraphNode getOutput() const = 0;
       virtual GraphNode::ConstNodeRange getInputs() const = 0;

      // set width
       virtual void setWidth(Gravel::Pointer::GraphNode, unsigned) = 0;
    };
    
    class ActorHandle { 
       virtual void attach(const Gravel::Pointer::Module&) const = 0 ;
       virtual Gravel::Module getOwner() const = 0;
    };
  
    
    };
    
    class Actor : public virtual Gravel::Interface::Actor {   
        public:
              Actor();
              /* Graph Connectivity */
              GraphNode::ConstNodeRange getInputs() const;
              Gravel::Pointer::GraphNode getOutput() const;
              /* Width Selection */
              void setWidth(Gravel::Pointer::GraphNode, unsigned);
              /* Lifetime Management */
              void initialize(Gravel::Pointer::Actor);
         protected:
   
        bool initialized;
        // All nodes are owned by a particular actor which creates them
        // Deletion of an actor means their nodes are deleted and dangling `back' nodes and next 
        // nodes are amended
        GraphNode::NodeMap nodes;
    };
    
};


#endif	/* ACTOR_H */

