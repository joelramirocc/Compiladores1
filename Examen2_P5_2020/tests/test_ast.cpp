#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "spl_ast.h"
#include "spl_interp.h"


#define EQ(a,b) std::make_shared<EQExpr>(a,b)
#define NEQ(a,b) std::make_shared<NEQExpr>(a,b)
#define FUNC(a,b,c) std::make_shared<FuncExpr>(a,b,c)
#define CALL(a,b) std::make_shared<CallExpr>(a,b)
#define ADD(a,b) std::make_shared<AddExpr>(a,b)
#define SUB(a,b) std::make_shared<SubExpr>(a,b)
#define MUL(a,b) std::make_shared<MultExpr>(a,b)
#define DIV(a,b) std::make_shared<DivExpr>(a,b)
#define NUM(n) std::make_shared<NumberExpr>(n)
#define VAR(n) std::make_shared<IdentExpr>(n)
#define ASSIGN(a,b) std::make_shared<AssignStmt>(a,b)
#define COND(a,b,c) std::make_shared<IfStmt>(a,b,c)
#define SEQ std::make_shared<SeqStmt>


ASTNodePtr makeFuncDecl(const std::string& name, const std::vector<std::string>& params,
                        ASTNodePtr expr)
{
    return FUNC(name, params, expr);
}

ASTNodePtr makeFuncCall(const std::string& name, const std::vector<ASTNodePtr>& args)
{
    return CALL(name, args);
}

ASTNodePtr makeSeq(const std::vector<ASTNodePtr>& stmts)
{
    return SEQ(stmts);
}

TEST_CASE("Error: Function not defined")
{
    ASTNodePtr root = ASSIGN("x", makeFuncCall("func", {}) );

    StmtInterp interp;

    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Error: Duplicated definition of function")
{
    ASTNodePtr root = makeSeq({
        makeFuncDecl("add", {}, {}),
        makeFuncDecl("add", {}, {})
    });

    StmtInterp interp;

    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Error: Mismatch argument count")
{   
    ASTNodePtr root = makeSeq({
        makeFuncDecl("add", {"a", "b", "c"}, {}),
        ASSIGN("x", makeFuncCall("add", { NUM(10) }))
    });

    StmtInterp interp;

    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Error: Variable not defined")
{
    ASTNodePtr root = makeSeq({
        ASSIGN("x", VAR("y"))
    });

    StmtInterp interp;
    REQUIRE_THROWS( interp.exec(root.get()) );
}

TEST_CASE("Single Assign")
{
    std::vector<ASTNodePtr> stmts = {
        ASSIGN("x", MUL(ADD(NUM(10), NUM(7)), NUM(5)))
    };

    ASTNodePtr root = SEQ(stmts);
    StmtInterp interp;

    StmtInterp::Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 85 );
}

TEST_CASE("Multiple Assign")
{
    std::vector<ASTNodePtr> stmts = {
        ASSIGN("x", ADD(NUM(10), NUM(7))),
        ASSIGN("y", SUB(NUM(170), NUM(7))),
        ASSIGN("z", MUL(NUM(13), NUM(17)))
    };

    ASTNodePtr root = SEQ(stmts);
    StmtInterp interp;

    StmtInterp::Table vars = interp.exec(root.get());

    auto itx = vars.find("x");
    auto ity = vars.find("y");
    auto itz = vars.find("z");

    REQUIRE( itx != vars.end() );
    CHECK( itx->second == 17 );
    REQUIRE( ity != vars.end() );
    CHECK( ity->second == 163 );
    REQUIRE( itz != vars.end() );
    CHECK( itz->second ==  221);
}

TEST_CASE("Two argument function")
{
    std::vector<ASTNodePtr> stmts = {
        makeFuncDecl( "add", {"a", "b"}, ADD(VAR("a"), VAR("b")) ),
        ASSIGN( "x", makeFuncCall("add", {NUM(10), NUM(20)}) )
     };

    ASTNodePtr root = SEQ(stmts);
    StmtInterp interp;

    StmtInterp::Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 30 );
}

TEST_CASE("Three argument function")
{
    ASTNodePtr add_fn = makeFuncDecl("add",  { "a", "b", "c" },
                                     { MUL(ADD(VAR("c"), VAR("a")), SUB(VAR("b"), VAR("c"))) });

    ASTNodePtr root = makeSeq({
        add_fn,
        ASSIGN("x", makeFuncCall("add", { NUM(10), NUM(20), NUM(3) })),
    });

    StmtInterp interp;

    StmtInterp::Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 221 );
}

TEST_CASE("Function order")
{
    ASTNodePtr add_fn = makeFuncDecl(
                                        "add",  { "a", "b", "c" }, 
                                        ADD(makeFuncCall("mul", {VAR("a"), VAR("b")}), VAR("c"))
                                     );

    ASTNodePtr mul_fn = makeFuncDecl("mul",  { "a", "b" }, MUL(VAR("a"), VAR("b")) );

    ASTNodePtr root = makeSeq({
        add_fn,
        mul_fn,
        ASSIGN("x", makeFuncCall("add", { NUM(10), NUM(17), NUM(3) })),
    });

    StmtInterp interp;

    StmtInterp::Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 173 );
}

TEST_CASE("Recursive function")
{
    ASTNodePtr fact_fn = makeFuncDecl(
                                        "fact",  { "n" },
                                        COND( EQ(VAR("n"), NUM(0)),
                                              NUM(1),
                                              MUL( VAR("n"), makeFuncCall("fact", { SUB(VAR("n"), NUM(1)) }) )
                                            )
                                      );

    ASTNodePtr root = makeSeq({
        fact_fn,
        ASSIGN("x", makeFuncCall("fact", { NUM(7) })),
    });

    StmtInterp interp;

    StmtInterp::Table vars = interp.exec(root.get());

    auto it = vars.find("x");

    REQUIRE( it != vars.end() );
    CHECK( it->second == 5040 );
}