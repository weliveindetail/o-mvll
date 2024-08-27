#include "omvll/log.hpp"
#include "omvll/utils.hpp"
#include "omvll/passes/cleaning/Cleaning.hpp"
#include "omvll/omvll_config.hpp"

#include <llvm/Demangle/Demangle.h>

using namespace llvm;

namespace omvll {

PreservedAnalyses Cleaning::run(Module &M, ModuleAnalysisManager &FAM) {
  bool Changed = false;
  for (Function& F : M) {
    std::string Name  = demangle(F.getName().str());
    StringRef NRef = Name;
    if (NRef.starts_with("_JNIEnv::") && config.inline_jni_wrappers) {
      SINFO("Inlining {}", Name);
      F.addFnAttr(Attribute::AlwaysInline);
      Changed = true;
    }
  }

  if (config.shuffle_functions) {
    shuffleFunctions(M);
    Changed = true;
  }

  SINFO("[{}] Done!", name());
  return Changed ? PreservedAnalyses::none() :
                   PreservedAnalyses::all();

}
}

