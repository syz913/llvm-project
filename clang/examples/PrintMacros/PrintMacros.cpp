#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/Lex/PPCallbacks.h"
#include "llvm/Support/raw_ostream.h"
using namespace clang;

namespace {

class PrintMacros : public PPCallbacks {
public:
  void MacroDefined(const Token &MacroNameTok,
                    const MacroDirective *MD) override {
    llvm::outs() << "MacroDefined reached"
                 << "\n";
    llvm::errs() << "Token kind:" << MacroNameTok.getKind() << "\n";
    MD->dump();
  }

  void MacroExpands(const Token &MacroNameTok, const MacroDefinition &MD,
                    SourceRange Range, const MacroArgs *Args) override {
    llvm::outs() << "MacroExpands reached"
                 << "\n";
  }
};

class PrintMacrosAction : public PluginASTAction {
protected:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                 StringRef InFile) override {
    Preprocessor &preprocessor = CI.getPreprocessor();
    preprocessor.addPPCallbacks(std::make_unique<PrintMacros>());
    return std::unique_ptr<ASTConsumer>(new ASTConsumer());
  }

  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &arg) override {
    return true;
  }
};

} // namespace

static FrontendPluginRegistry::Add<PrintMacrosAction> X("print-macros",
                                                        "print defined macros");
