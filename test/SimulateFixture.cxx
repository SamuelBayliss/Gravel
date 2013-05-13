
#include <gravel/test/SimulateFixture.h>

#include <exception>

#include <sys/wait.h>

SimulateFixture::SimulateFixture() : name("iverilog"), output_file("/tmp/sim") {
  
    
}

SimulateFixture::~SimulateFixture() { 
    
   
 
}

bool SimulateFixture::CompileSimulation(std::string rtl) {
    
    int success;
    
    const std::string output_file = "/tmp/sim";
    
    simulate_pid = fork();
    
    if (simulate_pid == -1) {
        throw std::exception();
    }
    
    if (simulate_pid == 0) { 
        // child
        
        // compiles in clock and reset generator and testbench code
        
        int success = execlp(name.c_str(), name.c_str(), std::string("-o").c_str(), output_file.c_str(), rtl.c_str(), NULL);
                
    } else {
        // parent 
        wait(&success);
    }
    
    return true;
}

bool SimulateFixture::RunSimulation(int cycles) {
    int success ; 
    
    /* cycles passed in as parameter to simulation */
    
     simulate_pid = fork();
    
    if (simulate_pid == -1) {
        throw std::exception();
    }
    
    if (simulate_pid == 0) { 
        // child
        int success = execlp(output_file.c_str(), output_file.c_str(), NULL);
                
    } else {
        // parent 
        wait(&success);
    }
    
    return true;
}