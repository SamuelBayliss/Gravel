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
#include <boost/shared_ptr.hpp>

#include <gravel/private/Definitions.h>

#include <gravel/private/Actor.h>

#include "GraphNode.h"

namespace Gravel { 
    /* Actors can be Symbols or Expressions */
    /* Symbols with only an output are constants */
    /* Symbols with input and output can be registered */


  
 
    
    
     namespace Exception { 
         class GraphNodeNotFound : public std::exception { 
             
         };
     }
     
    namespace Interface { 
        
    class Actor { 
       public:
      //  std::set<Gravel::GraphNode> getInputs();
       virtual Gravel::Pointer::GraphNode getOutput() const = 0;
       virtual Gravel::Collection::GraphNode getInputs() const = 0;

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
              Gravel::Collection::GraphNode getInputs() const;
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

