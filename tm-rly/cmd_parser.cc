
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         cmdparse
#define yylex           cmdlex
#define yyerror         cmderror
#define yylval          cmdlval
#define yychar          cmdchar
#define yydebug         cmddebug
#define yynerrs         cmdnerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 52 "cmd_parser.yy"
 
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <netinet/in.h>
	#include <pthread.h>
	#include <string>

	#include "tm.h"
   	#include "config.h"

	#ifdef HAVE_LIBBROCCOLI
	#include "BroccoliComm.hh"
	#endif

	#include "Storage.hh"
	#include "Query.hh"
	#include "Index.hh"

	// Work around a bug in the relation between bison and GCC 3.x:
	#if defined (__GNUC__) && 3 <= __GNUC__
	#define __attribute__(arglist)
	#endif

	/* Internal datastructures whilse parsing */ 
	static QueryRequest * q_req;
	static QueryResult *q_res; 
	static IndexField *q_idxfield;
	static bool q_mem_only;
	static bool q_subscribe;
	static tm_time_t q_start;
	static tm_time_t q_end;
	static broccoli_worker_thread_data* q_bc_thread;

	static int nextQueryID = 0;

	//extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp);
	extern int yylex();
	struct yy_buffer_state;
	static pthread_mutex_t cmd_parser_lock;

	typedef struct yy_buffer_state *YY_BUFFER_STATE;
	extern void cmd_delete_buffer (YY_BUFFER_STATE b);
	extern YY_BUFFER_STATE cmd_scan_string (const char *yy_str);

	int cmderror(const char*);
	int cmd_parse_lineno=0;
	int cmd_parse_errors=0;
	//  const char* parse_filename=NULL;

	/*
	 * symbols shared with main.cc
	 */
	Storage* cmd_parser_storage=NULL;
	FILE *cmd_parser_outfp;
	extern void print_stats(FILE *fp);
	extern pcap_t* ph;


/* Line 189 of yacc.c  */
#line 141 "cmd_parser.cc"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SEMICOLON = 258,
     COLON = 259,
     DASH = 260,
     ASTERISK = 261,
     LBRACE = 262,
     RBRACE = 263,
     LPAREN = 264,
     RPAREN = 265,
     LBRACK = 266,
     RBRACK = 267,
     TOK_INTEGER = 268,
     TOK_STRING = 269,
     TOK_DOUBLE = 270,
     TOK_ID = 271,
     TOK_IP_ADDR = 272,
     TOK_SET_DYN_CLASS = 273,
     TOK_UNSET_DYN_CLASS = 274,
     TOK_ORIG = 275,
     TOK_RESP = 276,
     TOK_CLASS = 277,
     TOK_FILTER = 278,
     TOK_MAIN = 279,
     TOK_LOG_INTERVAL = 280,
     TOK_DEVICE = 281,
     TOK_LOGFILE = 282,
     TOK_WORKDIR = 283,
     TOK_READ_TRACEFILE = 284,
     TOK_BRO_CONNECT_STR = 285,
     TOK_MEM = 286,
     TOK_DISK = 287,
     TOK_K = 288,
     TOK_M = 289,
     TOK_G = 290,
     TOK_CUTOFF = 291,
     TOK_PRECEDENCE = 292,
     TOK_NO = 293,
     TOK_PKTS_TO_DISK = 294,
     TOK_CONSOLE = 295,
     TOK_MAX_INDEX_ENTRIES = 296,
     TOK_FILESIZE = 297,
     TOK_CONN_TIMEOUT = 298,
     TOK_QUERY = 299,
     TOK_FEED = 300,
     TOK_TO_FILE = 301,
     TOK_SUBSCRIBE = 302,
     TOK_CONN = 303,
     TOK_START = 304,
     TOK_END = 305,
     TOK_TAG = 306,
     TOK_TS = 307,
     TOK_PROTO = 308,
     TOK_PRINT = 309,
     TOK_NOP = 310,
     TOK_BRO_CONNECT = 311,
     TOK_SUSPEND_CUTOFF = 312,
     TOK_UNSUSPEND_CUTOFF = 313,
     TOK_SUSPEND_TIMEOUT = 314,
     TOK_UNSUSPEND_TIMEOUT = 315,
     TOK_SHOW = 316,
     TOK_STATS = 317,
     TOK_CONNS = 318,
     TOK_INDEX = 319,
     TOK_MEM_ONLY = 320,
     TOK_DEBUG_FIFOMEM = 321,
     TOK_SAMPLE = 322,
     TOK_HELP = 323
   };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define COLON 259
#define DASH 260
#define ASTERISK 261
#define LBRACE 262
#define RBRACE 263
#define LPAREN 264
#define RPAREN 265
#define LBRACK 266
#define RBRACK 267
#define TOK_INTEGER 268
#define TOK_STRING 269
#define TOK_DOUBLE 270
#define TOK_ID 271
#define TOK_IP_ADDR 272
#define TOK_SET_DYN_CLASS 273
#define TOK_UNSET_DYN_CLASS 274
#define TOK_ORIG 275
#define TOK_RESP 276
#define TOK_CLASS 277
#define TOK_FILTER 278
#define TOK_MAIN 279
#define TOK_LOG_INTERVAL 280
#define TOK_DEVICE 281
#define TOK_LOGFILE 282
#define TOK_WORKDIR 283
#define TOK_READ_TRACEFILE 284
#define TOK_BRO_CONNECT_STR 285
#define TOK_MEM 286
#define TOK_DISK 287
#define TOK_K 288
#define TOK_M 289
#define TOK_G 290
#define TOK_CUTOFF 291
#define TOK_PRECEDENCE 292
#define TOK_NO 293
#define TOK_PKTS_TO_DISK 294
#define TOK_CONSOLE 295
#define TOK_MAX_INDEX_ENTRIES 296
#define TOK_FILESIZE 297
#define TOK_CONN_TIMEOUT 298
#define TOK_QUERY 299
#define TOK_FEED 300
#define TOK_TO_FILE 301
#define TOK_SUBSCRIBE 302
#define TOK_CONN 303
#define TOK_START 304
#define TOK_END 305
#define TOK_TAG 306
#define TOK_TS 307
#define TOK_PROTO 308
#define TOK_PRINT 309
#define TOK_NOP 310
#define TOK_BRO_CONNECT 311
#define TOK_SUSPEND_CUTOFF 312
#define TOK_UNSUSPEND_CUTOFF 313
#define TOK_SUSPEND_TIMEOUT 314
#define TOK_UNSUSPEND_TIMEOUT 315
#define TOK_SHOW 316
#define TOK_STATS 317
#define TOK_CONNS 318
#define TOK_INDEX 319
#define TOK_MEM_ONLY 320
#define TOK_DEBUG_FIFOMEM 321
#define TOK_SAMPLE 322
#define TOK_HELP 323




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 111 "cmd_parser.yy"

	int i;
	int64_t i64;
	char* s;
	double d;
	IndexField* indexfield_p;
	IPAddress* ipaddress_p;
	ConnectionID4* connectionid4_p;
	QueryResult* queryresult_p;
	QueryRequest* queryrequest_p;



/* Line 214 of yacc.c  */
#line 327 "cmd_parser.cc"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 339 "cmd_parser.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   53

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  10
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNRULES -- Number of states.  */
#define YYNSTATES  55

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    17,    20,    23,
      26,    29,    34,    37,    40,    42,    46,    49,    53,    54,
      56,    58,    59,    62,    64,    69,    71,    75,    80,    83,
      85,    87,    89,    91
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      70,     0,    -1,    55,    -1,    54,    -1,    54,    14,    -1,
      68,    -1,    44,    75,    74,    72,    -1,    57,    76,    -1,
      58,    76,    -1,    59,    76,    -1,    60,    76,    -1,    18,
      17,    16,    71,    -1,    19,    17,    -1,    56,    14,    -1,
      56,    -1,    61,    48,    76,    -1,    61,    62,    -1,    61,
      48,    67,    -1,    -1,    20,    -1,    21,    -1,    -1,    72,
      73,    -1,    65,    -1,    49,    77,    50,    77,    -1,    47,
      -1,    64,    16,    14,    -1,    45,    16,    51,    16,    -1,
      46,    78,    -1,    14,    -1,    13,    -1,    15,    -1,    14,
      -1,    16,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   157,   157,   161,   165,   170,   185,   231,   239,   247,
     260,   268,   280,   289,   296,   308,   327,   331,   353,   356,
     359,   364,   366,   370,   373,   378,   385,   408,   429,   442,
     450,   451,   454,   455
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "COLON", "DASH", "ASTERISK",
  "LBRACE", "RBRACE", "LPAREN", "RPAREN", "LBRACK", "RBRACK",
  "TOK_INTEGER", "TOK_STRING", "TOK_DOUBLE", "TOK_ID", "TOK_IP_ADDR",
  "TOK_SET_DYN_CLASS", "TOK_UNSET_DYN_CLASS", "TOK_ORIG", "TOK_RESP",
  "TOK_CLASS", "TOK_FILTER", "TOK_MAIN", "TOK_LOG_INTERVAL", "TOK_DEVICE",
  "TOK_LOGFILE", "TOK_WORKDIR", "TOK_READ_TRACEFILE",
  "TOK_BRO_CONNECT_STR", "TOK_MEM", "TOK_DISK", "TOK_K", "TOK_M", "TOK_G",
  "TOK_CUTOFF", "TOK_PRECEDENCE", "TOK_NO", "TOK_PKTS_TO_DISK",
  "TOK_CONSOLE", "TOK_MAX_INDEX_ENTRIES", "TOK_FILESIZE",
  "TOK_CONN_TIMEOUT", "TOK_QUERY", "TOK_FEED", "TOK_TO_FILE",
  "TOK_SUBSCRIBE", "TOK_CONN", "TOK_START", "TOK_END", "TOK_TAG", "TOK_TS",
  "TOK_PROTO", "TOK_PRINT", "TOK_NOP", "TOK_BRO_CONNECT",
  "TOK_SUSPEND_CUTOFF", "TOK_UNSUSPEND_CUTOFF", "TOK_SUSPEND_TIMEOUT",
  "TOK_UNSUSPEND_TIMEOUT", "TOK_SHOW", "TOK_STATS", "TOK_CONNS",
  "TOK_INDEX", "TOK_MEM_ONLY", "TOK_DEBUG_FIFOMEM", "TOK_SAMPLE",
  "TOK_HELP", "$accept", "cmd", "orig_or_resp", "queryspec_flags",
  "queryspec_flag", "queryspec_key", "queryresult", "connection4",
  "timestamp", "string_id", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    71,
      71,    72,    72,    73,    73,    73,    74,    75,    75,    76,
      77,    77,    78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     4,     2,     2,     2,
       2,     4,     2,     2,     1,     3,     2,     3,     0,     1,
       1,     0,     2,     1,     4,     1,     3,     4,     2,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     2,    14,     0,     0,     0,
       0,     0,     5,     0,     0,    12,     0,     0,     0,     4,
      13,    29,     7,     8,     9,    10,     0,    16,     1,    18,
       0,    32,    33,    28,     0,    21,    17,    15,    19,    20,
      11,     0,     0,     6,    27,    26,    25,     0,    23,    22,
      30,    31,     0,     0,    24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    13,    40,    43,    49,    35,    18,    22,    52,    33
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -42
static const yytype_int8 yypact[] =
{
     -17,   -10,    -1,   -31,     5,   -42,     6,     8,     8,     8,
       8,   -39,   -42,    25,    10,   -42,    12,    -4,   -35,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -14,   -42,   -42,    -3,
     -21,   -42,   -42,   -42,    15,   -42,   -42,   -42,   -42,   -42,
     -42,    16,    19,   -41,   -42,   -42,   -42,    -2,   -42,   -42,
     -42,   -42,   -16,    -2,   -42
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,   -42,   -42,   -42,   -42,    -5,   -18,   -42
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      21,     1,     2,    23,    24,    25,    46,    14,    47,    26,
      31,    50,    32,    51,    16,    17,    15,    38,    39,    19,
      20,    37,    21,    27,    48,    28,    29,     3,    30,    34,
      41,    42,    44,    45,    53,    54,     0,     4,     5,     6,
       7,     8,     9,    10,    11,     0,     0,     0,     0,     0,
       0,    12,     0,    36
};

static const yytype_int8 yycheck[] =
{
      14,    18,    19,     8,     9,    10,    47,    17,    49,    48,
      14,    13,    16,    15,    45,    46,    17,    20,    21,    14,
      14,    26,    14,    62,    65,     0,    16,    44,    16,    64,
      51,    16,    16,    14,    50,    53,    -1,    54,    55,    56,
      57,    58,    59,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    -1,    67
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    18,    19,    44,    54,    55,    56,    57,    58,    59,
      60,    61,    68,    70,    17,    17,    45,    46,    75,    14,
      14,    14,    76,    76,    76,    76,    48,    62,     0,    16,
      16,    14,    16,    78,    64,    74,    67,    76,    20,    21,
      71,    51,    16,    72,    16,    14,    47,    49,    65,    73,
      13,    15,    77,    50,    77
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 157 "cmd_parser.yy"
    { 
		if(cmd_parser_outfp)
			fprintf(cmd_parser_outfp, "TOK_NOP\n"); 
	}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 161 "cmd_parser.yy"
    {
		if(cmd_parser_outfp)
			fprintf(cmd_parser_outfp, "PRINT\n");
	}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 165 "cmd_parser.yy"
    {
		if(cmd_parser_outfp)
			fprintf(cmd_parser_outfp, "PRINT string \"%s\"\n", (yyvsp[(2) - (2)].s));
		free((yyvsp[(2) - (2)].s));
	}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 170 "cmd_parser.yy"
    {
		if (cmd_parser_outfp) {
			fprintf(cmd_parser_outfp, "Online help not yet implemented. See Documentation/TM_HOWTO\n");
		}
	}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 186 "cmd_parser.yy"
    {
		int ok = 1;
		if (!q_res) {
			 /* queryresult can be NULL if no Broccoli support
			 * and Broccoli feed requested
			 */
			if(cmd_parser_outfp)
				fprintf(cmd_parser_outfp, "QUERY RESULT DESTINATION UNDEFINED\n");
			ok = 0;
		}
		if (ok && !q_idxfield) {
			if(cmd_parser_outfp)
				fprintf(cmd_parser_outfp, "QUERY KEY UNDEFINED\n");
			ok = 0;
		}

		if (ok) {
			//printf("DEBUG: start=%lf end=%lf, mem_only=%d, subscribe=%d\n", q_start, q_end, q_mem_only, q_subscribe);
			q_req = new QueryRequest(q_idxfield, q_start, q_end, q_mem_only, q_subscribe,
				cmd_parser_storage->getPcapDatalink(), cmd_parser_storage->getPcapSnaplen());
			if (!q_req) {
				if(cmd_parser_outfp)
					fprintf(cmd_parser_outfp, "COULD NOT CREATE QUERY REQUEST\n");
				ok = 0;
			}
		}
		if (ok) {
			cmd_parser_storage->query(q_req, q_res);
			/* queryresult will be `delete'd by storage->query
			 * (or later at connection inactivity timeout
			 * if a subscription is involved)
			 * Queryspec will be delete'd by storage->query
			 */
		} 
		else { 
			/* Cleanup */
			if (q_res)
				delete q_res;
			if (q_idxfield)
				delete q_idxfield;
			if (q_req)
				delete q_req;
		}
	}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 231 "cmd_parser.yy"
    {
		if ((yyvsp[(2) - (2)].connectionid4_p) != NULL) {
	        if(!cmd_parser_storage->suspendCutoff(*(ConnectionID4*)(yyvsp[(2) - (2)].connectionid4_p), true))
				if(cmd_parser_outfp)
					fprintf(cmd_parser_outfp, "NOT IN CONNECTION TABLE\n");
			delete((yyvsp[(2) - (2)].connectionid4_p));
		}
	}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 239 "cmd_parser.yy"
    {
		if ((yyvsp[(2) - (2)].connectionid4_p) != NULL)  {
	        if (!cmd_parser_storage->suspendCutoff(*(ConnectionID4*)(yyvsp[(2) - (2)].connectionid4_p), false))
				if(cmd_parser_outfp)
					fprintf(cmd_parser_outfp, "NOT IN CONNECTION TABLE\n");
			delete((yyvsp[(2) - (2)].connectionid4_p));
		}
	}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 247 "cmd_parser.yy"
    {
		if ((yyvsp[(2) - (2)].connectionid4_p) != NULL) {
			if (!cmd_parser_storage->suspendTimeout(*(ConnectionID4*)(yyvsp[(2) - (2)].connectionid4_p), true))
				if(cmd_parser_outfp)
					fprintf(cmd_parser_outfp, "NOT IN CONNECTION TABLE\n");
			/*
			   printf("successfully suspended timeout\n");
			else
			   printf("Connection wasn't in table. added it\n");
			  */
			delete((yyvsp[(2) - (2)].connectionid4_p));
		}
	}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 260 "cmd_parser.yy"
    {
		if ((yyvsp[(2) - (2)].connectionid4_p) != NULL) {
			if(!cmd_parser_storage->suspendTimeout(*(ConnectionID4*)(yyvsp[(2) - (2)].connectionid4_p), false))
				if(cmd_parser_outfp)
					fprintf(cmd_parser_outfp, "NOT IN CONNECTION TABLE\n");
			delete((yyvsp[(2) - (2)].connectionid4_p));
		}
	}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 268 "cmd_parser.yy"
    {
		/* FIXME: do the call to setDynClass later, otherwise this function
		might be called even if a parse error is discovered later!!! */
		if ((yyvsp[(2) - (4)].ipaddress_p) != NULL && (yyvsp[(3) - (4)].s) != NULL) {
			cmd_parser_storage->setDynClass((yyvsp[(2) - (4)].ipaddress_p), (yyvsp[(4) - (4)].i), (yyvsp[(3) - (4)].s));
			/* storage class owns $2 (IPAddress) and will take care of
			   deleting it */
		}
		if ((yyvsp[(3) - (4)].s) != NULL) {
			free((yyvsp[(3) - (4)].s));
		}
	}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 280 "cmd_parser.yy"
    {
		if ((yyvsp[(2) - (2)].ipaddress_p) != NULL) {
			cmd_parser_storage->unsetDynClass((yyvsp[(2) - (2)].ipaddress_p));
			/* storage class owns $2 (IPAddress) and will take care of
			   deleting it */
		}
	}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 289 "cmd_parser.yy"
    {
		if(cmd_parser_outfp)
			fprintf(cmd_parser_outfp, "BRO_CONNECT  <string> NOT IMPLEMENTED\n");
		free((yyvsp[(2) - (2)].s));
	      
	}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 296 "cmd_parser.yy"
    {
//		printf("BRO_CONNECT\n");
#ifdef HAVE_LIBBROCCOLI
		broccoli_start_worker_thread(-1);
#else
		if(cmd_parser_outfp) {
			fprintf(cmd_parser_outfp,
				PACKAGE " WAS COMPILED WITHOUT BROCCOLI SUPPORT\n");
		}
#endif
	}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 308 "cmd_parser.yy"
    {
		if ((yyvsp[(3) - (3)].connectionid4_p) != NULL) {

			ConnectionID4 cid=*(ConnectionID4*)(yyvsp[(3) - (3)].connectionid4_p);
	//		printf("show conn %s\n", cid.getStr().c_str());
	//		printf("getCopy...\n");
			Connection *c=cmd_parser_storage->getConns().getCopy(&cid);
	//		printf("... getCopy\n");
	//		Connection *c=cmd_parser_storage->getConns().get(&cid);
			if (c) {
				if(cmd_parser_outfp)
					fprintf(cmd_parser_outfp, "* %s\n", c->getStr().c_str());
					//fprintf(cmd_parser_outfp, "* %s\n%s\n", $3->getStr().c_str(),
					//	  c->getStr().c_str());
			} else if(cmd_parser_outfp)
				fprintf(cmd_parser_outfp, "NOT IN CONNECTION TABLE\n");
			delete (yyvsp[(3) - (3)].connectionid4_p);
		}
	}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 327 "cmd_parser.yy"
    {
		if(cmd_parser_outfp)
			print_stats(cmd_parser_outfp);
	}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 331 "cmd_parser.yy"
    {
		if(cmd_parser_outfp)
			cmd_parser_storage->getConns().printConnSample(cmd_parser_outfp);
	}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 353 "cmd_parser.yy"
    {
		(yyval.i) = TM_DYNCLASS_BOTH;
	}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 356 "cmd_parser.yy"
    {
		(yyval.i) = TM_DYNCLASS_ORIG;
	}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 359 "cmd_parser.yy"
    {
		(yyval.i) = TM_DYNCLASS_RESP;
	}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 370 "cmd_parser.yy"
    {
		q_mem_only = true;
	}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 374 "cmd_parser.yy"
    {
		q_start = (yyvsp[(2) - (4)].d);
		q_end = (yyvsp[(4) - (4)].d);
	}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 379 "cmd_parser.yy"
    {
		q_subscribe = true;
	}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 385 "cmd_parser.yy"
    {
		//fprintf(stderr, "INDEX QUERY: <%s>, string <%s>\n", $2, $3);
		IndexType *idx=cmd_parser_storage->getIndexes()->getIndexByName((yyvsp[(2) - (3)].s));
		if (idx) {
			IndexField *ifp;
			//fprintf(stderr, "found the index\n");
			ifp = idx->parseQuery((yyvsp[(3) - (3)].s));
			//DEBUG fprintf(stderr, ">>>>> %s\n", ifp->getStr().c_str());
			if (ifp==NULL) 
				cmderror("invalid query string");
			q_idxfield=ifp;
			//idx->debugPrint();
		}
		else {
			if(cmd_parser_outfp)
				fprintf(cmd_parser_outfp, "NO SUCH INDEX\n");
			q_idxfield = NULL;
		}
		free((yyvsp[(2) - (3)].s));
		free((yyvsp[(3) - (3)].s));
	}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 408 "cmd_parser.yy"
    {
		/* TODO: identify bc by $2 */
#ifdef HAVE_LIBBROCCOLI
		if (q_res != NULL) {
			cmderror("query result object already exists");
		}
		else {
			assert(q_bc_thread);
			q_res = new QueryResultBroConn(nextQueryID, q_bc_thread, (yyvsp[(4) - (4)].s));
			nextQueryID++;
		}
#else
		if(cmd_parser_outfp) {
			fprintf(cmd_parser_outfp,
				PACKAGE " was compiled without broccoli support\n");
		}
		q_res=NULL;
#endif
		free((yyvsp[(2) - (4)].s));
		free((yyvsp[(4) - (4)].s));
	}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 429 "cmd_parser.yy"
    {
		if (q_res != NULL) {
			cmderror("query result object already exists");
		}
		else {
			q_res = new QueryResultFile(nextQueryID, (yyvsp[(2) - (2)].s), cmd_parser_storage->getPcapDatalink(),cmd_parser_storage->getPcapSnaplen());
			nextQueryID++;
		}
		free((yyvsp[(2) - (2)].s));
	}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 442 "cmd_parser.yy"
    {
		(yyval.connectionid4_p) = ConnectionID4::parse((yyvsp[(1) - (1)].s));
		if ((yyval.connectionid4_p) == NULL) 
			cmderror("invalid connection specification");
		delete((yyvsp[(1) - (1)].s));
	}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 450 "cmd_parser.yy"
    { (yyval.d)=(yyvsp[(1) - (1)].i64); }
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 451 "cmd_parser.yy"
    { (yyval.d)=(yyvsp[(1) - (1)].d); }
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 454 "cmd_parser.yy"
    { (yyval.s)=(yyvsp[(1) - (1)].s); }
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 455 "cmd_parser.yy"
    { (yyval.s)=(yyvsp[(1) - (1)].s); }
    break;



/* Line 1455 of yacc.c  */
#line 2014 "cmd_parser.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 457 "cmd_parser.yy"

     
void 
cmd_parser_init(void) {
	pthread_mutex_init(&cmd_parser_lock, NULL);	
}

void
cmd_parser_finish(void) {
	pthread_mutex_destroy(&cmd_parser_lock);
}

int
cmderror(const char *msg) {
	if(cmd_parser_outfp)
		fprintf(cmd_parser_outfp, "PARSER ERROR - %s\n", msg);
	tmlog(TM_LOG_NOTE, "query", "PARSER ERROR - %s", msg); 
	cmd_parse_errors++;
	return 0;
}

/* Don't forget to call cmd_parser_init(), before you call the parser */
int
parse_cmd(const char* cmd, FILE *outfp, Storage* s, broccoli_worker_thread_data* thread) {
	pthread_mutex_lock(&cmd_parser_lock);
	// set variable parser_storage global to conf_parser.cc
	q_req = NULL;
	q_res = NULL;
	q_mem_only = false;
	q_subscribe = false;
	q_start = 0;
	q_end = 1e13; /* along time in the future */
	q_bc_thread = thread;
	
	cmd_parser_storage=s;
	cmd_parser_outfp = outfp;
	YY_BUFFER_STATE bufstate=cmd_scan_string(cmd);
	cmd_parse_errors=0;
	cmdparse();
	fflush(outfp);
	cmd_delete_buffer(bufstate);
	pthread_mutex_unlock(&cmd_parser_lock);
	return cmd_parse_errors;
}

