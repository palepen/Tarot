#include "../includes/Codegen.h"

//set the module name ot translation_unit 
// to set the cpu architecture prefered to use setTargetTriple
Codegen::Codegen(
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree,
    std::string_view sourcePath)
    :   resolvedTree(std::move(resolvedTree)),
        builder(context),
        module("<translation_unit", context){
            module.setSourceFileName(sourcePath);
            module.setTargetTriple(llvm::sys::getDefaultTargetTriple());
        }
    
    //we need to make all the functions available to other functions so the resolution happens in 2 passes
    // first makes the function available and next we resolve the bodies
    llvm::Module *Codegen::generateIR(){
        for(auto &&function : resolvedTree)
            generateFunctionDecl(*function);

        for(auto &&function : resolvedTree)
            generateFunctionBody(*function);

        
    }