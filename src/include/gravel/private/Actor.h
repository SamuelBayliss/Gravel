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


namespace Gravel { 
    /* Actors can be Symbols or Expressions */
    /* Symbols with only an output are constants */
    /* Symbols with input and output can be registered */
    typedef enum GraphEdgeDirection {Input, Output};
    
    class Actor;
    class Symbol;
    namespace Interface{
        
        class Actor;
    }
   
    namespace Pointer{

    typedef boost::shared_ptr<Gravel::Actor> Actor; 
    };
    
    class GraphNode { 
   
    public :     
        
          typedef std::multimap<GraphEdgeDirection, boost::shared_ptr<GraphNode> > NodeMap;
          typedef NodeMap::const_iterator ConstNodeIterator;
           typedef NodeMap::iterator NodeIterator;
          typedef std::pair<GraphEdgeDirection, boost::shared_ptr<GraphNode> > NodePair;
          typedef std::pair<NodeIterator, NodeIterator> NodeRange;
          typedef std::pair<ConstNodeIterator, ConstNodeIterator> ConstNodeRange;
          typedef boost::weak_ptr<Gravel::GraphNode> NodePtr;
              
          typedef std::map<NodePtr, NodePtr> BackMap;
          typedef BackMap::iterator BackMapIterator;
          typedef std::pair<BackMapIterator, BackMapIterator> BackMapRange;
          
          typedef std::map<NodePtr, Gravel::Pointer::Actor> ParentMap;
          
        // Destructor
        ~GraphNode();
        
        // points to implementation (which is an actor)
        
        static Gravel::Pointer::Actor getParent(Gravel::GraphNode::NodePtr);
         static void setParents(Gravel::Pointer::Actor);
         
         static BackMapRange getConnections(NodePtr);
         
        // Graph Node destructor removes back-link and removes from ring
        static void connect(boost::weak_ptr<GraphNode>, boost::weak_ptr<GraphNode>);
       
        // Default Constructor
        GraphNode();
         private: 
        unsigned width;
        
        static BackMap back;
        static std::map<NodePtr, Gravel::Pointer::Actor> parent;
       
        
        
        // Copy Constructor is declared but not implemented
        
        // Equality Assignment is declared but not implemented
    };
    namespace Interface { 
        
    class Actor { 
       public:
      //  std::set<Gravel::GraphNode> getInputs();
       virtual GraphNode::NodePtr getOutput() const = 0;
       virtual GraphNode::ConstNodeRange getInputs() const = 0;

      // set width
       virtual void setWidth(Gravel::GraphNode::NodePtr, unsigned) = 0;
       
    };
    
    };
    
    class Actor : public virtual Gravel::Interface::Actor {       
   
        public:
            
              GraphNode::ConstNodeRange getInputs() const;
              boost::weak_ptr<Gravel::GraphNode> getOutput() const;
              void setWidth(Gravel::GraphNode::NodePtr, unsigned);
         protected:
        // Has a smart pointer to Graph Node
      
        // All nodes are owned by a particular actor which creates them
        // Deletion of an actor means their nodes are deleted and dangling `back' nodes and next 
        // nodes are amended
        GraphNode::NodeMap nodes;
    };
    
}


#endif	/* ACTOR_H */

