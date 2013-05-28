/* 
 * File:   GraphUtilities.h
 * Author: sb1708
 *
 * Created on April 30, 2013, 4:33 PM
 */

#ifndef GRAPHUTILITIES_H
#define	GRAPHUTILITIES_H

#include <map>
#include <set>

template <class T>
 std::set < std::set <T> > find_disjoint_sets(std::multimap<T, T> edge_set)  { 
 
    typedef std::set < T > NodeSet;
    typedef  std::multimap<T,T> EdgeSet;
    typedef std::set < std::set <T> > DisjointSets;
 
    
    // start with empty set of node sets
     
    typename EdgeSet::iterator edgit;
     
     
     DisjointSets disjoint_sets;
     
    
     
     for (edgit = edge_set.begin() ; edgit != edge_set.end() ; edgit++ ) { 
   
         if(disjoint_sets.empty()) {
             /* if the edges are in neither sets, add both into a new set*/
               std::set<T>  nodes;
               nodes.insert(edgit->first);
               nodes.insert(edgit->second);
               disjoint_sets.insert(nodes);
             
         } else { 
             typename DisjointSets::iterator from_match = disjoint_sets.end();
             typename DisjointSets::iterator to_match = disjoint_sets.end();
             
                typename  DisjointSets::iterator search_iterator;
             for (search_iterator = disjoint_sets.begin() ; search_iterator != disjoint_sets.end() ; search_iterator++) {
                 if (search_iterator->find(edgit->first) != search_iterator->end()) {
                     from_match = search_iterator;
                 }
                 
             }
             for (search_iterator = disjoint_sets.begin() ; search_iterator != disjoint_sets.end() ; search_iterator++) {
                     if (search_iterator->find(edgit->second) != search_iterator->end()) {
                     to_match = search_iterator;
                 }
             }
             
             if ((from_match != disjoint_sets.end()) && (to_match != disjoint_sets.end()) && (from_match != to_match) ) {
                      /* if the edges straddle two sets, merge the sets*/
                 
                  std::set < T >  merged_set;
                  merged_set = (*from_match);
                  merged_set.insert(to_match->begin(), to_match->end());
                  disjoint_sets.erase(to_match);
                  disjoint_sets.erase(from_match);
                  disjoint_sets.insert(merged_set);
             }
             
             if ((from_match == disjoint_sets.end()) && (to_match == disjoint_sets.end())) { 
                    /* if the edges are in no sets, add both into a new set*/
                      std::set < T > nodes;
                      nodes.insert(edgit->first);
                      nodes.insert(edgit->second);
                      disjoint_sets.insert(nodes);
             }
   
        
             if ((from_match == disjoint_sets.end()) && (to_match != disjoint_sets.end())) { 
                  /* if one vertex in edge is in a set, add the other */
                 std::set < T >  nodes = (*to_match);
                 nodes.insert(edgit->first);
                 disjoint_sets.erase(to_match);
                 disjoint_sets.insert(nodes);
             }
        
        
             if ((to_match == disjoint_sets.end()) && (from_match != disjoint_sets.end())) { 
                 /* if one vertex in edge is in a set, add the other */
                 std::set < T >  nodes = (*from_match);
                 nodes.insert(edgit->second);
                 disjoint_sets.erase(from_match);
                 disjoint_sets.insert(nodes);
             }

         }
         
     }
     
     return disjoint_sets;
     
}



#endif	/* GRAPHUTILITIES_H */

