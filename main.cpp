#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Tooling/Tooling.h>

#include <gtest/gtest.h>

#include <utility>

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;

class DumpCallback : public MatchFinder::MatchCallback
{
    public:
    std::vector<std::string> Names;

    virtual void run(const MatchFinder::MatchResult &Result) override
    {
        if (const FunctionDecl *FD = Result.Nodes.getNodeAs<FunctionDecl>("function"))
        {
            Names.push_back(FD->getName().str());
            llvm::outs() << "Found function " << FD->getName() << "\n";
            FD->dump();
        }
    }
};

TEST(ASTMatcherPlay, Basic)
{
    DumpCallback Callback;
    MatchFinder Finder;
    Finder.addMatcher(functionDecl(hasName("add")).bind("function"), &Callback);

    auto Factory = std::unique_ptr(newFrontendActionFactory(&Finder));
    runToolOnCode(Factory->create(), "int add(int a, int b) { return a + b; }");

    EXPECT_EQ(Callback.Names.size(), 1);
    EXPECT_EQ(Callback.Names[0], "add");
}