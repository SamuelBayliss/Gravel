/* 
 * File:   Actor.h
 * Author: sb1708
 *
 * Created on March 26, 2013, 11:40 AM
 */

#ifndef ACTOR_H
#define	ACTOR_H

#include <map>

namespace Gravel { 
    /* Actors can be Symbols or Expressions */
    /* Symbols with only an output are constants */
    /* Symbols with input and output can be registered */
    typedef enum GraphEdgeDirection {Input, Output};
    
    class GraphNode { 
    private: 
        GraphNode * next;
        GraphNode * back;
     
        // Copy Constructor is declared but not implemented
        
        // Equality Assignment is declared but not implemented
    public :     
        // Destructor
        ~GraphNode();
        
        // Graph Node destructor removes back-link and removes from ring
        
        // Default Constructor
        GraphNode();
    };
    
    class Actor {       
        // Has a smart pointer to Graph Node
        typedef std::multimap<GraphEdgeDirection, boost::shared_ptr<GraphNode> > Nodemap;
        // All nodes are owned by a particular actor which creates them
        // Deletion of an actor means their nodes are deleted and dangling `back' nodes and next 
        // nodes are amended
    };
    
}


#endif	/* ACTOR_H */

