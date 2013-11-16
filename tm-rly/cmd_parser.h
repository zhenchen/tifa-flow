
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 202 "cmd_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE cmdlval;


