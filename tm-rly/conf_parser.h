
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
     LBRACE = 259,
     RBRACE = 260,
     LPAREN = 261,
     RPAREN = 262,
     LBRACK = 263,
     RBRACK = 264,
     LCOMMENT = 265,
     RCOMMENT = 266,
     TOK_INTEGER = 267,
     TOK_STRING = 268,
     TOK_DOUBLE = 269,
     TOK_ID = 270,
     TOK_IPADDRESS = 271,
     TOK_CLASS = 272,
     TOK_FILTER = 273,
     TOK_MAIN = 274,
     TOK_LOG_INTERVAL = 275,
     TOK_DEVICE = 276,
     TOK_LOGFILE = 277,
     TOK_WORKDIR = 278,
     TOK_QUERYFILEDIR = 279,
     TOK_INDEXDIR = 280,
     TOK_READ_TRACEFILE = 281,
     TOK_BRO_CONNECT_STR = 282,
     TOK_MEM = 283,
     TOK_DISK = 284,
     TOK_K = 285,
     TOK_M = 286,
     TOK_G = 287,
     TOK_CUTOFF = 288,
     TOK_PRECEDENCE = 289,
     TOK_DYN_TIMEOUT = 290,
     TOK_NO = 291,
     TOK_PKTS_TO_DISK = 292,
     TOK_CONSOLE = 293,
     TOK_DAEMON = 294,
     TOK_MAX_INDEX_ENTRIES = 295,
     TOK_FILESIZE = 296,
     TOK_CONN_TIMEOUT = 297,
     TOK_MAX_SUBSCRIPTIONS = 298,
     TOK_RMTCONSOLE = 299,
     TOK_RMTCONSOLE_PORT = 300,
     TOK_RMTCONSOLE_LISTEN_ADDR = 301,
     TOK_BRO_LISTEN = 302,
     TOK_BRO_LISTEN_PORT = 303,
     TOK_BRO_LISTEN_ADDR = 304,
     TOK_TWEAK_CAPTURE_THREAD = 305,
     TOK_SCOPE = 306,
     TOK_PRIORITY = 307
   };
#endif
/* Tokens.  */
#define SEMICOLON 258
#define LBRACE 259
#define RBRACE 260
#define LPAREN 261
#define RPAREN 262
#define LBRACK 263
#define RBRACK 264
#define LCOMMENT 265
#define RCOMMENT 266
#define TOK_INTEGER 267
#define TOK_STRING 268
#define TOK_DOUBLE 269
#define TOK_ID 270
#define TOK_IPADDRESS 271
#define TOK_CLASS 272
#define TOK_FILTER 273
#define TOK_MAIN 274
#define TOK_LOG_INTERVAL 275
#define TOK_DEVICE 276
#define TOK_LOGFILE 277
#define TOK_WORKDIR 278
#define TOK_QUERYFILEDIR 279
#define TOK_INDEXDIR 280
#define TOK_READ_TRACEFILE 281
#define TOK_BRO_CONNECT_STR 282
#define TOK_MEM 283
#define TOK_DISK 284
#define TOK_K 285
#define TOK_M 286
#define TOK_G 287
#define TOK_CUTOFF 288
#define TOK_PRECEDENCE 289
#define TOK_DYN_TIMEOUT 290
#define TOK_NO 291
#define TOK_PKTS_TO_DISK 292
#define TOK_CONSOLE 293
#define TOK_DAEMON 294
#define TOK_MAX_INDEX_ENTRIES 295
#define TOK_FILESIZE 296
#define TOK_CONN_TIMEOUT 297
#define TOK_MAX_SUBSCRIPTIONS 298
#define TOK_RMTCONSOLE 299
#define TOK_RMTCONSOLE_PORT 300
#define TOK_RMTCONSOLE_LISTEN_ADDR 301
#define TOK_BRO_LISTEN 302
#define TOK_BRO_LISTEN_PORT 303
#define TOK_BRO_LISTEN_ADDR 304
#define TOK_TWEAK_CAPTURE_THREAD 305
#define TOK_SCOPE 306
#define TOK_PRIORITY 307




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 81 "conf_parser.yy"

  int i;
  int64_t i64;
  char* s;
//  std::string s;
  double d;
  Fifo* fifo_p;
  struct in_addr ipaddr;
/*
  IndexType* index_type_p;
*/



/* Line 1676 of yacc.c  */
#line 171 "conf_parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE conflval;


