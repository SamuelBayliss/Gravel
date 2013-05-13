/* 
 * File:   SimulateFixture.h
 * Author: sb1708
 *
 * Created on April 28, 2013, 7:35 PM
 */

#ifndef SIMULATEFIXTURE_H
#define	SIMULATEFIXTURE_H

#include <string>

class SimulateFixture { 
  
    /*
     
        
     
     */
    
   const std::string name;
   const std::string output_file;
   
    pid_t simulate_pid;
    
public : 
    SimulateFixture();
    ~SimulateFixture();
    
bool CompileSimulation(std::string);
bool RunSimulation(int);

};

#endif	/* SIMULATEFIXTURE_H */

