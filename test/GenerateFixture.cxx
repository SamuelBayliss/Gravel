
#include <gravel/test/GenerateFixture.h>

#include "gravel/Context.h"

GenerateFixture::~GenerateFixture() { 
    Gravel::Context * ctx = Gravel::Context::getInstance();
    ctx->reset();
}

GenerateFixture::GenerateFixture() { 
    
}