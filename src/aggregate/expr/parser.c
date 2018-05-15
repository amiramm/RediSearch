/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 31 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"

#include "token.h"
#include "expression.h"
#include "parser.h"

#line 34 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    RSExprParser_ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is RSExprParser_ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    RSExprParser_ParseARG_SDECL     A static variable declaration for the %extra_argument
**    RSExprParser_ParseARG_PDECL     A parameter declaration for the %extra_argument
**    RSExprParser_ParseARG_STORE     Code to store %extra_argument into yypParser
**    RSExprParser_ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 30
#define YYACTIONTYPE unsigned char
#define RSExprParser_ParseTOKENTYPE  RSExprToken 
typedef union {
  int yyinit;
  RSExprParser_ParseTOKENTYPE yy0;
  double yy6;
  RSArgList * yy12;
  RSExpr * yy35;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define RSExprParser_ParseARG_SDECL  RSExprParseCtx *ctx ;
#define RSExprParser_ParseARG_PDECL , RSExprParseCtx *ctx 
#define RSExprParser_ParseARG_FETCH  RSExprParseCtx *ctx  = yypParser->ctx 
#define RSExprParser_ParseARG_STORE yypParser->ctx  = ctx 
#define YYNSTATE             37
#define YYNRULE              27
#define YY_MAX_SHIFT         36
#define YY_MIN_SHIFTREDUCE   48
#define YY_MAX_SHIFTREDUCE   74
#define YY_MIN_REDUCE        75
#define YY_MAX_REDUCE        101
#define YY_ERROR_ACTION      102
#define YY_ACCEPT_ACTION     103
#define YY_NO_ACTION         104
/************* End control #defines *******************************************/

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if:
**    (1)  The yy_shift_ofst[S]+X value is out of range, or
**    (2)  yy_lookahead[yy_shift_ofst[S]+X] is not equal to X, or
**    (3)  yy_shift_ofst[S] equal YY_SHIFT_USE_DFLT.
** (Implementation note: YY_SHIFT_USE_DFLT is chosen so that
** YY_SHIFT_USE_DFLT+X will be out of range for all possible lookaheads X.
** Hence only tests (1) and (2) need to be evaluated.)
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (122)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */     5,    4,    1,   11,   10,    9,    8,    7,    6,   18,
 /*    10 */    14,   16,   15,   12,   13,   68,   49,   75,    5,    4,
 /*    20 */    77,   11,   10,    9,    8,    7,    6,   18,   14,   16,
 /*    30 */    15,   12,   13,    5,    4,   77,   11,   10,    9,    8,
 /*    40 */     7,    6,   18,   14,   16,   15,   12,   13,   11,   10,
 /*    50 */     9,    8,    7,    6,   18,   14,   16,   15,   12,   13,
 /*    60 */     3,   18,   14,   16,   15,   12,   13,   66,   36,  103,
 /*    70 */    20,   66,   34,   17,   22,   69,   35,   65,   67,   16,
 /*    80 */    15,   12,   13,   66,   66,   66,   21,   23,   24,   66,
 /*    90 */    66,   66,   25,   26,   27,   66,   66,   66,   28,   29,
 /*   100 */    30,   66,   66,   66,   31,   55,   54,   66,   66,   66,
 /*   110 */    33,   52,   51,   66,   66,   70,   19,   32,   77,   77,
 /*   120 */    77,    2,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    2,   16,    4,    5,    6,    7,    8,    9,   10,
 /*    10 */    11,   12,   13,   14,   15,   21,   17,    0,    1,    2,
 /*    20 */    29,    4,    5,    6,    7,    8,    9,   10,   11,   12,
 /*    30 */    13,   14,   15,    1,    2,   29,    4,    5,    6,    7,
 /*    40 */     8,    9,   10,   11,   12,   13,   14,   15,    4,    5,
 /*    50 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   15,
 /*    60 */     3,   10,   11,   12,   13,   14,   15,   25,   11,   27,
 /*    70 */    28,   25,   26,   16,   28,   18,   19,   20,   21,   12,
 /*    80 */    13,   14,   15,   25,   25,   25,   28,   28,   28,   25,
 /*    90 */    25,   25,   28,   28,   28,   25,   25,   25,   28,   28,
 /*   100 */    28,   25,   25,   25,   28,   28,   28,   25,   25,   25,
 /*   110 */    28,   28,   28,   25,   25,   17,   28,   28,   29,   29,
 /*   120 */    29,   23,
};
#define YY_SHIFT_USE_DFLT (122)
#define YY_SHIFT_COUNT    (36)
#define YY_SHIFT_MIN      (-14)
#define YY_SHIFT_MAX      (98)
static const short yy_shift_ofst[] = {
 /*     0 */    57,   57,   57,   57,   57,   57,   57,   57,   57,   57,
 /*    10 */    57,   57,   57,   57,   57,   57,   57,   57,   57,   -1,
 /*    20 */    17,   32,   32,   44,   44,   44,   51,   51,   51,   51,
 /*    30 */    51,   51,   67,   67,   98,  -14,   -6,
};
#define YY_REDUCE_USE_DFLT (-1)
#define YY_REDUCE_COUNT (18)
#define YY_REDUCE_MIN   (0)
#define YY_REDUCE_MAX   (89)
static const signed char yy_reduce_ofst[] = {
 /*     0 */    42,   46,   58,   59,   60,   64,   65,   66,   70,   71,
 /*    10 */    72,   76,   77,   78,   82,   83,   84,   88,   89,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   102,   99,  102,  102,  102,  102,  102,  102,  102,  102,
 /*    10 */   102,  102,  102,  102,  102,  102,  102,  102,  102,  102,
 /*    20 */   102,  101,  100,   91,   90,   89,   88,   87,   86,   85,
 /*    30 */    84,   83,   77,   80,  102,   98,  102,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  RSExprParser_ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void RSExprParser_ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "AND",           "OR",            "NOT",         
  "EQ",            "NE",            "LT",            "LE",          
  "GT",            "GE",            "PLUS",          "MINUS",       
  "DIVIDE",        "TIMES",         "MOD",           "POW",         
  "LP",            "RP",            "PROPERTY",      "SYMBOL",      
  "STRING",        "NUMBER",        "ARGLIST",       "COMMA",       
  "error",         "number",        "arglist",       "program",     
  "expr",        
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "program ::= expr",
 /*   1 */ "expr ::= LP expr RP",
 /*   2 */ "expr ::= expr PLUS expr",
 /*   3 */ "expr ::= expr DIVIDE expr",
 /*   4 */ "expr ::= expr TIMES expr",
 /*   5 */ "expr ::= expr MINUS expr",
 /*   6 */ "expr ::= expr POW expr",
 /*   7 */ "expr ::= expr MOD expr",
 /*   8 */ "expr ::= expr EQ expr",
 /*   9 */ "expr ::= expr NE expr",
 /*  10 */ "expr ::= expr LT expr",
 /*  11 */ "expr ::= expr LE expr",
 /*  12 */ "expr ::= expr GT expr",
 /*  13 */ "expr ::= expr GE expr",
 /*  14 */ "expr ::= expr AND expr",
 /*  15 */ "expr ::= expr OR expr",
 /*  16 */ "expr ::= NOT expr",
 /*  17 */ "expr ::= STRING",
 /*  18 */ "expr ::= number",
 /*  19 */ "number ::= NUMBER",
 /*  20 */ "number ::= MINUS NUMBER",
 /*  21 */ "expr ::= PROPERTY",
 /*  22 */ "expr ::= SYMBOL LP arglist RP",
 /*  23 */ "expr ::= SYMBOL",
 /*  24 */ "arglist ::=",
 /*  25 */ "arglist ::= expr",
 /*  26 */ "arglist ::= arglist COMMA expr",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to RSExprParser_ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void RSExprParser_ParseInit(void *yypParser){
  yyParser *pParser = (yyParser*)yypParser;
#ifdef YYTRACKMAXSTACKDEPTH
  pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  pParser->yytos = NULL;
  pParser->yystack = NULL;
  pParser->yystksz = 0;
  if( yyGrowStack(pParser) ){
    pParser->yystack = &pParser->yystk0;
    pParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  pParser->yyerrcnt = -1;
#endif
  pParser->yytos = pParser->yystack;
  pParser->yystack[0].stateno = 0;
  pParser->yystack[0].major = 0;
}

#ifndef RSExprParser_Parse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to RSExprParser_Parse and RSExprParser_ParseFree.
*/
void *RSExprParser_ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ) RSExprParser_ParseInit(pParser);
  return pParser;
}
#endif /* RSExprParser_Parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  RSExprParser_ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
      /* Default NON-TERMINAL Destructor */
    case 24: /* error */
    case 27: /* program */
    case 28: /* expr */
{
#line 23 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
RSExpr_Free((yypminor->yy35)); 
#line 516 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
}
      break;
    case 25: /* number */
{
#line 26 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"

#line 523 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
}
      break;
    case 26: /* arglist */
{
#line 29 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
RSArgList_Free((yypminor->yy12)); 
#line 530 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void RSExprParser_ParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef RSExprParser_Parse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void RSExprParser_ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  RSExprParser_ParseFinalize(p);
  (*freeProc)(p);
}
#endif /* RSExprParser_Parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int RSExprParser_ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static unsigned int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yytos->stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   RSExprParser_ParseARG_FETCH;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   RSExprParser_ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  RSExprParser_ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH] ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 27, 1 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 3 },
  { 28, 2 },
  { 28, 1 },
  { 28, 1 },
  { 25, 1 },
  { 25, 2 },
  { 28, 1 },
  { 28, 4 },
  { 28, 1 },
  { 26, 0 },
  { 26, 1 },
  { 26, 3 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno        /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  RSExprParser_ParseARG_FETCH;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH-1] ){
      yyStackOverflow(yypParser);
      return;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        return;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* program ::= expr */
#line 44 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ ctx->root = yymsp[0].minor.yy35; }
#line 875 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
        break;
      case 1: /* expr ::= LP expr RP */
#line 46 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yymsp[-2].minor.yy35 = yymsp[-1].minor.yy35; }
#line 880 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
        break;
      case 2: /* expr ::= expr PLUS expr */
#line 47 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewOp('+', yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 885 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 3: /* expr ::= expr DIVIDE expr */
#line 48 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{  yylhsminor.yy35 = RS_NewOp('/', yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 891 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 4: /* expr ::= expr TIMES expr */
#line 49 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{  yylhsminor.yy35 = RS_NewOp('*', yymsp[-2].minor.yy35, yymsp[0].minor.yy35);}
#line 897 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 5: /* expr ::= expr MINUS expr */
#line 50 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{  yylhsminor.yy35 = RS_NewOp('-', yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 903 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 6: /* expr ::= expr POW expr */
#line 51 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{  yylhsminor.yy35 = RS_NewOp('^', yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 909 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 7: /* expr ::= expr MOD expr */
#line 52 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewOp('%', yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 915 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 8: /* expr ::= expr EQ expr */
#line 55 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_Eq, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 921 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 9: /* expr ::= expr NE expr */
#line 56 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_Ne, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 927 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 10: /* expr ::= expr LT expr */
#line 57 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_Lt, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 933 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 11: /* expr ::= expr LE expr */
#line 58 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_Le, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 939 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 12: /* expr ::= expr GT expr */
#line 59 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_Gt, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 945 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 13: /* expr ::= expr GE expr */
#line 60 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_Ge, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 951 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 14: /* expr ::= expr AND expr */
#line 61 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_And, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 957 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 15: /* expr ::= expr OR expr */
#line 62 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewPredicate(RSCondition_Or, yymsp[-2].minor.yy35, yymsp[0].minor.yy35); }
#line 963 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy35 = yylhsminor.yy35;
        break;
      case 16: /* expr ::= NOT expr */
#line 63 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yymsp[-1].minor.yy35 = RS_NewPredicate(RSCondition_Not, yymsp[0].minor.yy35, NULL); }
#line 969 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
        break;
      case 17: /* expr ::= STRING */
#line 66 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 =  RS_NewStringLiteral((char*)yymsp[0].minor.yy0.s, yymsp[0].minor.yy0.len); }
#line 974 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[0].minor.yy35 = yylhsminor.yy35;
        break;
      case 18: /* expr ::= number */
#line 67 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewNumberLiteral(yymsp[0].minor.yy6); }
#line 980 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[0].minor.yy35 = yylhsminor.yy35;
        break;
      case 19: /* number ::= NUMBER */
#line 69 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy6 = yymsp[0].minor.yy0.numval; }
#line 986 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[0].minor.yy6 = yylhsminor.yy6;
        break;
      case 20: /* number ::= MINUS NUMBER */
#line 70 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yymsp[-1].minor.yy6 = -yymsp[0].minor.yy0.numval; }
#line 992 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
        break;
      case 21: /* expr ::= PROPERTY */
#line 72 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy35 = RS_NewProp(yymsp[0].minor.yy0.s, yymsp[0].minor.yy0.len); }
#line 997 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[0].minor.yy35 = yylhsminor.yy35;
        break;
      case 22: /* expr ::= SYMBOL LP arglist RP */
#line 73 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{
    RSFunction cb = RSFunctionRegistry_Get(yymsp[-3].minor.yy0.s, yymsp[-3].minor.yy0.len);
    if (!cb) {
        asprintf(&ctx->errorMsg, "Unknown function name '%.*s'", yymsp[-3].minor.yy0.len, yymsp[-3].minor.yy0.s);
        ctx->ok = 0;
        yylhsminor.yy35 = NULL; 
    } else {
         yylhsminor.yy35 = RS_NewFunc(yymsp[-3].minor.yy0.s, yymsp[-3].minor.yy0.len, yymsp[-1].minor.yy12, cb);
    }
}
#line 1012 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-3].minor.yy35 = yylhsminor.yy35;
        break;
      case 23: /* expr ::= SYMBOL */
#line 84 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{
    if (yymsp[0].minor.yy0.len == 4 && !strncmp(yymsp[0].minor.yy0.s, "NULL", 4)) {
        yylhsminor.yy35 = RS_NewNullLiteral();
    } else {
        asprintf(&ctx->errorMsg, "Unknown symbol '%.*s'", yymsp[0].minor.yy0.len, yymsp[0].minor.yy0.s);
        ctx->ok = 0;
        yylhsminor.yy35 = NULL; 
    }
}
#line 1026 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[0].minor.yy35 = yylhsminor.yy35;
        break;
      case 24: /* arglist ::= */
#line 94 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yymsp[1].minor.yy12 = RS_NewArgList(NULL); }
#line 1032 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
        break;
      case 25: /* arglist ::= expr */
#line 95 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ yylhsminor.yy12 = RS_NewArgList(yymsp[0].minor.yy35); }
#line 1037 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[0].minor.yy12 = yylhsminor.yy12;
        break;
      case 26: /* arglist ::= arglist COMMA expr */
#line 96 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
{ 
    yylhsminor.yy12 = RSArgList_Append(yymsp[-2].minor.yy12, yymsp[0].minor.yy35);
}
#line 1045 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
  yymsp[-2].minor.yy12 = yylhsminor.yy12;
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ){
      yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    }
    yymsp -= yysize-1;
    yypParser->yytos = yymsp;
    yymsp->stateno = (YYACTIONTYPE)yyact;
    yymsp->major = (YYCODETYPE)yygoto;
    yyTraceShift(yypParser, yyact);
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yypParser->yytos -= yysize;
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  RSExprParser_ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  RSExprParser_ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  RSExprParser_ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  RSExprParser_ParseARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 38 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.y"
  

    asprintf(&ctx->errorMsg, "Syntax error at offset %d near '%.*s'", TOKEN.pos, TOKEN.len, TOKEN.s);
    ctx->ok = 0;
#line 1110 "/Users/dvirvolk/code/RediSearch/src/aggregate/expr/parser.c"
/************ End %syntax_error code ******************************************/
  RSExprParser_ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  RSExprParser_ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  RSExprParser_ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "RSExprParser_ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void RSExprParser_Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  RSExprParser_ParseTOKENTYPE yyminor       /* The value for the token */
  RSExprParser_ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  unsigned int yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  yypParser = (yyParser*)yyp;
  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  RSExprParser_ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}