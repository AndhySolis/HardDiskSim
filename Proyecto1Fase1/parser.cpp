/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintactico.y" /* yacc.c:337  */

#include "scanner.h"//se importa el header del analisis sintactico
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <iostream> //libreria para imprimir en cosola de C
#include <QString> //libreria para manejo de STRINGS de QT
#include "sistema.h"


extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON
Sistema *Ope = new Sistema();
std::string toString(const char *TEXT){
	std::string Salida="";
	Salida=TEXT;
	return Salida;
}

int yyerror(const char* mens){
//metodo que se llama al haber un error sintactico
//SE IMPRIME EN CONSOLA EL ERROR
std::cout <<mens<<" "<<yytext<< std::endl;
return 0;
}






struct STRCREAR{
	std::string Path;
	int Size;
	char Unit='m';
	char Fit[2]={'b','f'};
	bool BSize=false;
	bool BUnit=false;
	bool BPath=false;
	
};

struct STRFORMATO{
	int Realizar=-1;
	int Size;
	bool BSize=false;
	char Unit='m';
	std::string Path;
	bool BPath=false;
	char Type='p';
	char Fit[2]={'b','f'};
	std::string Delete;
	std::string Name;
	bool BName=false;
	int Add;	
};

struct STRMONTAR{
	std::string Path;
	bool BPath=false;
	std::string Name;
	bool BName=false;	
};

struct STRREPORTE{
	std::string Path;
	bool BPath=false;
	std::string NameRep;
	bool BNameRep=false;
	std::string Id;
	bool BId=false;		
};

struct STRSEXT{
	std::string Id;
	std::string Type; 
};
struct STRSINGRE{ 
	std::string Usr;
	std::string Pwd;
	std::string Id;
};
struct STRSUSR{ 
	std::string Usr;
	std::string Pwd;
	std::string Grp;
};
struct STRSPER{
	std::string Path;
	std::string Ugo;
	std::string R; 
};
struct STRSARCH{
	std::string Path;
	std::string P;
	std::string Size;
	std::string Cont;   
};
struct STRSEDIT{
	std::string Path;
	std::string Cont;   
};
struct STRSREN{
	std::string Path;
	std::string Name;  
};
struct STRSDIR{
	std::string Path;
	std::string P;  
};
struct STRSCOP{
	std::string Path;
	std::string Dest;   
};
struct STRSMOV{
	std::string Path;
	std::string Dest; 
};
struct STRSFIN{
	std::string Path;
	std::string Name; 
};
struct STRSCHOW{
	std::string Path;
	std::string R;
	std::string Usr; 
};
struct STRSCHG{
	std::string Usr;
	std::string Grp; 
};

struct STRDITA{
	std::string Concatenar;
};


#line 209 "parser.cpp" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    entero = 258,
    cadena = 259,
    identificador = 260,
    letra = 261,
    comentario = 262,
    direccion = 263,
    igual = 264,
    mkdisk = 265,
    rmdisk = 266,
    fdisk = 267,
    mount = 268,
    unmount = 269,
    rep = 270,
    exec = 271,
    size = 272,
    fit = 273,
    unit = 274,
    path = 275,
    typep = 276,
    deletep = 277,
    name = 278,
    add = 279,
    id = 280,
    fs = 281,
    dest = 282,
    usr = 283,
    pwd = 284,
    logout = 285,
    login = 286,
    mkfs = 287,
    mkgrp = 288,
    rmgrp = 289,
    grp = 290,
    mkusr = 291,
    rmusr = 292,
    chmodp = 293,
    ugo = 294,
    r = 295,
    p = 296,
    cont = 297,
    mkfile = 298,
    cat = 299,
    file = 300,
    rem = 301,
    edit = 302,
    ren = 303,
    mkdirp = 304,
    cp = 305,
    mv = 306,
    find = 307,
    chownp = 308,
    chgrp = 309,
    pausep = 310,
    recovery = 311,
    loss = 312
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 142 "sintactico.y" /* yacc.c:352  */


//se especifican los tipo de valores para los no terminales y lo terminales
char TEXT [256];
struct STRDITA *TEXT2 ;
struct STRCREAR   *SCREAR;
struct STRFORMATO *SFORMA;
struct STRMONTAR  *SMONTA;
struct STRREPORTE *SREPOR;
//FASE2
struct STRSEXT* SEXT;
struct STRSINGRE* SINGRE;
struct STRSUSR* SUSR;
struct STRSPER* SPER;
struct STRSARCH* SARCH;
struct STRSEDIT* SEDIT;
struct STRSREN* SREN;
struct STRSDIR* SDIR;
struct STRSCOP* SCOP;
struct STRSMOV* SMOV;
struct STRSFIN* SFIN;
struct STRSCHOW* SCHOW;
struct STRSCHG* SCHG;

#line 335 "parser.cpp" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  104
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   239

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  119
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  247

#define YYUNDEFTOK  2
#define YYMAXUTOK   312

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
      55,    56,    57
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   267,   267,   268,   272,   273,   275,   276,   278,   281,
     284,   287,   288,   289,   292,   293,   294,   295,   298,   299,
     300,   303,   304,   305,   308,   309,   310,   313,   314,   315,
     318,   319,   320,   323,   324,   325,   328,   331,   334,   335,
     336,   337,   338,   341,   342,   343,   344,   347,   350,   351,
     352,   353,   355,   357,   360,   363,   364,   365,   366,   368,
     369,   370,   371,   374,   375,   377,   378,   379,   394,   402,
     403,   411,   414,   415,   416,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   442,   443,   444,   445,   446,   448,
     451,   452,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   469,   470,   471,   474,   476,   477,   478,   479,   481
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "entero", "cadena", "identificador",
  "letra", "comentario", "direccion", "igual", "mkdisk", "rmdisk", "fdisk",
  "mount", "unmount", "rep", "exec", "size", "fit", "unit", "path",
  "typep", "deletep", "name", "add", "id", "fs", "dest", "usr", "pwd",
  "logout", "login", "mkfs", "mkgrp", "rmgrp", "grp", "mkusr", "rmusr",
  "chmodp", "ugo", "r", "p", "cont", "mkfile", "cat", "file", "rem",
  "edit", "ren", "mkdirp", "cp", "mv", "find", "chownp", "chgrp", "pausep",
  "recovery", "loss", "$accept", "TERMIIDENTI", "TERMIMUC", "MUCHO",
  "MATAR", "RECUPERAR", "PAUSA", "CAMBIARGRUPO", "CAMBIARPROP", "FIN",
  "MOVER", "COPIAR", "NUEVACARPETA", "RENOMBRAR", "EDITARCHIVO", "REMOVER",
  "VERCONTE", "NUEVOARCHIVO", "PERMISO", "BORRARUSUARIO", "HACERUSUARIO",
  "BORRARGRUPO", "HACERGRUPO", "SALIR", "INGRE", "EXT3", "PROGRAMA",
  "OPCION", "CREAR", "BORRAR", "TERMIDIRECC", "FORMATO", "MONTAR",
  "DESMONTAR", "REPORTES", "EJECUTAR", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312
};
# endif

#define YYPACT_NINF -121

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-121)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     152,  -121,    -5,  -121,  -121,    26,  -121,    32,  -121,  -121,
    -121,    40,    58,  -121,    57,  -121,  -121,    27,    66,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,    89,    94,
    -121,  -121,  -121,     4,    -9,    44,    33,    35,   -14,    60,
     -13,  -121,  -121,    -4,     1,  -121,   -27,  -121,  -121,  -121,
      72,    49,   104,  -121,   105,  -121,    25,    79,  -121,    53,
    -121,    96,    99,   100,   102,   112,   117,   118,   119,    -1,
      -1,   120,   121,   122,   123,   124,   130,   134,   135,   136,
     137,   140,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   178,   182,   183,   184,   185,
     188,   201,   202,  -121,  -121,  -121,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,    10,   224,    10,    -1,    -1,    -1,    10,
      10,  -121,  -121,  -121,  -121,    -1,    -1,    10,    -1,    -1,
      10,    -1,    10,    10,    10,    10,    10,    -1,    10,    -1,
      10,     9,    -1,    10,    -1,    10,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   227,   226,   228,
      10,   229,   230,   231,    10,   232,    -1,    -1,   233,    10,
      -1,    10,    -1,    -1,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,     9,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    98,     0,   110,   113,     0,   118,     0,    54,    58,
      62,     0,     0,    51,     0,    46,    42,     0,     0,    35,
      32,    29,    26,    23,    20,    17,    13,    10,     0,     0,
      93,    92,    91,    90,    89,    88,    87,    86,    85,    84,
      83,    82,    81,    80,    79,    78,    77,    76,    75,    74,
      73,    72,     0,    64,    65,    66,    67,    68,    69,    70,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    61,     1,    63,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     2,     9,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,   100,    99,   114,   119,    53,
      52,    47,    37,    36,    12,    11,    16,    15,    14,    19,
      18,    22,    21,    25,    24,    28,    27,    31,    30,    33,
       7,     6,    34,     5,    40,    38,    39,    41,    43,    44,
      45,    50,    48,    49,    57,    55,    56,    60,    59,    94,
      95,    96,    97,   102,   103,   104,   105,   106,   107,   108,
     109,   111,   112,   116,   117,   115,     4
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -121,   -70,  -121,    21,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,  -121,
    -121,  -121,  -121,  -121,  -121,  -121,  -121,   187,  -121,  -121,
    -120,  -121,  -121,  -121,  -121,  -121
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   133,   212,   213,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
     186,    56,    57,    58,    59,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     134,    95,    96,   131,   132,   188,    82,    86,    97,   192,
     193,    73,   210,    88,   184,    61,    89,   196,   185,    74,
     199,    92,   201,   202,   203,   204,   205,    83,   207,    87,
     209,    75,    71,   215,   211,   217,   218,    90,    91,    72,
      93,    94,   110,   111,   112,   113,   114,   115,   116,   117,
     232,    62,    63,    78,   236,    80,   189,   190,   191,   241,
      79,   243,    81,    64,    76,   194,   195,    77,   197,   198,
     101,   200,    67,   120,   102,   103,   121,   206,   122,   208,
      84,    65,   214,    85,   216,    66,    68,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,    98,    69,   118,
      99,   100,   119,    70,   104,   123,   238,   239,   124,   125,
     242,   126,   244,   245,     1,     2,     3,     4,     5,     6,
       7,   127,   106,   107,   108,   109,   128,   129,   130,   135,
     136,   137,   138,   139,     8,     9,    10,    11,    12,   140,
      13,    14,    15,   141,   142,   143,   144,    16,    17,   145,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,     1,     2,     3,     4,     5,     6,     7,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,     8,     9,    10,    11,    12,   159,    13,    14,
      15,   160,   161,   162,   163,    16,    17,   164,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   187,
     229,   230,   233,   246,   231,   234,   240,   235,   237,   105
};

static const yytype_uint8 yycheck[] =
{
      70,    28,    29,     4,     5,   125,    20,    20,    35,   129,
     130,    20,     3,    17,     4,    20,    20,   137,     8,    28,
     140,    20,   142,   143,   144,   145,   146,    41,   148,    42,
     150,    40,    28,   153,    25,   155,   156,    41,    42,    35,
      39,    40,    17,    18,    19,    20,    21,    22,    23,    24,
     170,    25,    20,    20,   174,    20,   126,   127,   128,   179,
      27,   181,    27,    23,    20,   135,   136,    23,   138,   139,
      21,   141,    45,    20,    25,    26,    23,   147,    25,   149,
      20,    23,   152,    23,   154,    28,    20,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,    25,     9,    20,
      28,    29,    23,     9,     0,     9,   176,   177,     9,     9,
     180,     9,   182,   183,    10,    11,    12,    13,    14,    15,
      16,     9,    17,    18,    19,    20,     9,     9,     9,     9,
       9,     9,     9,     9,    30,    31,    32,    33,    34,     9,
      36,    37,    38,     9,     9,     9,     9,    43,    44,     9,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    10,    11,    12,    13,    14,    15,    16,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,    30,    31,    32,    33,    34,     9,    36,    37,
      38,     9,     9,     9,     9,    43,    44,     9,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     5,
       3,     5,     3,   212,     6,     5,     3,     6,     6,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    11,    12,    13,    14,    15,    16,    30,    31,
      32,    33,    34,    36,    37,    38,    43,    44,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    89,    90,    91,    92,
      93,    20,    25,    20,    23,    23,    28,    45,    20,     9,
       9,    28,    35,    20,    28,    40,    20,    23,    20,    27,
      20,    27,    20,    41,    20,    23,    20,    42,    17,    20,
      41,    42,    20,    39,    40,    28,    29,    35,    25,    28,
      29,    21,    25,    26,     0,    85,    17,    18,    19,    20,
      17,    18,    19,    20,    21,    22,    23,    24,    20,    23,
      20,    23,    25,     9,     9,     9,     9,     9,     9,     9,
       9,     4,     5,    59,    59,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     4,     8,    88,     5,    88,    59,
      59,    59,    88,    88,    59,    59,    88,    59,    59,    88,
      59,    88,    88,    88,    88,    88,    59,    88,    59,    88,
       3,    25,    60,    61,    59,    88,    59,    88,    88,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,     3,
       5,     6,    88,     3,     5,     6,    88,     6,    59,    59,
       3,    88,    59,    88,    59,    59,    61
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    58,    59,    59,    60,    60,    61,    61,    62,    63,
      64,    65,    65,    65,    66,    66,    66,    66,    67,    67,
      67,    68,    68,    68,    69,    69,    69,    70,    70,    70,
      71,    71,    71,    72,    72,    72,    73,    74,    75,    75,
      75,    75,    75,    76,    76,    76,    76,    77,    78,    78,
      78,    78,    79,    80,    81,    82,    82,    82,    82,    83,
      83,    83,    83,    84,    84,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    86,    86,    86,    86,    86,    87,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    90,    90,    90,    91,    92,    92,    92,    92,    93
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     3,     3,
       1,     4,     4,     1,     4,     4,     4,     1,     4,     4,
       1,     4,     4,     1,     4,     4,     1,     4,     4,     1,
       4,     4,     1,     4,     4,     1,     4,     4,     4,     4,
       4,     4,     1,     4,     4,     4,     1,     4,     4,     4,
       4,     1,     4,     4,     1,     4,     4,     4,     1,     4,
       4,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     4,     4,     1,     4,
       1,     1,     4,     4,     4,     4,     4,     4,     4,     4,
       1,     4,     4,     1,     4,     4,     4,     4,     1,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

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
#line 267 "sintactico.y" /* yacc.c:1652  */
    {std::copy(std::begin((yyvsp[0].TEXT)), std::end((yyvsp[0].TEXT)), std::begin((yyval.TEXT)));}
#line 1595 "parser.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 268 "sintactico.y" /* yacc.c:1652  */
    {std::string Tempo=(yyvsp[0].TEXT); Tempo=Tempo.substr(1,Tempo.length()-1); strcpy((yyval.TEXT),Tempo.c_str());}
#line 1601 "parser.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 272 "sintactico.y" /* yacc.c:1652  */
    {((yyvsp[-1].TEXT2)->Concatenar)=((yyvsp[-1].TEXT2)->Concatenar)+((yyvsp[0].TEXT2)->Concatenar); (yyval.TEXT2)=(yyvsp[-1].TEXT2);}
#line 1607 "parser.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 273 "sintactico.y" /* yacc.c:1652  */
    {(yyval.TEXT2)=(yyvsp[0].TEXT2);}
#line 1613 "parser.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 275 "sintactico.y" /* yacc.c:1652  */
    {STRDITA *Temp = new STRDITA(); Temp->Concatenar=(yyvsp[0].TEXT);(yyval.TEXT2)=Temp;}
#line 1619 "parser.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 276 "sintactico.y" /* yacc.c:1652  */
    {STRDITA *Temp = new STRDITA(); Temp->Concatenar=(yyvsp[0].TEXT); (yyval.TEXT2)=Temp;}
#line 1625 "parser.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 278 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1631 "parser.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 281 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1637 "parser.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 284 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1643 "parser.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 287 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SCHG)->Grp=(yyvsp[0].TEXT); (yyval.SCHG)=(yyvsp[-3].SCHG);}
#line 1649 "parser.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 288 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SCHG)->Usr=(yyvsp[0].TEXT); (yyval.SCHG)=(yyvsp[-3].SCHG);}
#line 1655 "parser.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 289 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCHG)= new STRSCHG();}
#line 1661 "parser.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 292 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SCHOW)->R=(yyvsp[0].TEXT); (yyval.SCHOW)=(yyvsp[-3].SCHOW);}
#line 1667 "parser.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 293 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SCHOW)->Usr=(yyvsp[0].TEXT); (yyval.SCHOW)=(yyvsp[-3].SCHOW);}
#line 1673 "parser.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 294 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SCHOW)->Path=(yyvsp[0].TEXT); (yyval.SCHOW)=(yyvsp[-3].SCHOW);}
#line 1679 "parser.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 295 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCHOW)= new STRSCHOW();}
#line 1685 "parser.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 298 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SFIN)->Name=(yyvsp[0].TEXT); (yyval.SFIN)=(yyvsp[-3].SFIN);}
#line 1691 "parser.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 299 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SFIN)->Path=(yyvsp[0].TEXT); (yyval.SFIN)=(yyvsp[-3].SFIN);}
#line 1697 "parser.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 300 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFIN)=new STRSFIN();}
#line 1703 "parser.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 303 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SMOV)->Dest=(yyvsp[0].TEXT); (yyval.SMOV)=(yyvsp[-3].SMOV);}
#line 1709 "parser.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 304 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SMOV)->Path=(yyvsp[0].TEXT); (yyval.SMOV)=(yyvsp[-3].SMOV);}
#line 1715 "parser.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 305 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SMOV)=new STRSMOV();}
#line 1721 "parser.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 308 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SCOP)->Dest=(yyvsp[0].TEXT); (yyval.SCOP)=(yyvsp[-3].SCOP);}
#line 1727 "parser.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 309 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SCOP)->Path=(yyvsp[0].TEXT); (yyval.SCOP)=(yyvsp[-3].SCOP);}
#line 1733 "parser.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 310 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCOP)=new STRSCOP();}
#line 1739 "parser.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 313 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SDIR)->P=(yyvsp[0].TEXT); (yyval.SDIR)=(yyvsp[-3].SDIR);}
#line 1745 "parser.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 314 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SDIR)->Path=(yyvsp[0].TEXT); (yyval.SDIR)=(yyvsp[-3].SDIR);}
#line 1751 "parser.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 315 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SDIR)= new STRSDIR();}
#line 1757 "parser.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 318 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SREN)->Name=(yyvsp[0].TEXT); (yyval.SREN)=(yyvsp[-3].SREN);}
#line 1763 "parser.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 319 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SREN)->Path=(yyvsp[0].TEXT); (yyval.SREN)=(yyvsp[-3].SREN);}
#line 1769 "parser.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 320 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SREN)= new STRSREN();}
#line 1775 "parser.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 323 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SEDIT)->Path=(yyvsp[0].TEXT); (yyval.SEDIT)=(yyvsp[-3].SEDIT);}
#line 1781 "parser.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 324 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SEDIT)->Cont=(yyvsp[0].TEXT2)->Concatenar; (yyval.SEDIT)=(yyvsp[-3].SEDIT);}
#line 1787 "parser.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 325 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SEDIT)= new STRSEDIT();}
#line 1793 "parser.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 328 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1799 "parser.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 331 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1805 "parser.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 334 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SARCH)->Path=(yyvsp[0].TEXT); (yyval.SARCH)=(yyvsp[-3].SARCH);}
#line 1811 "parser.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 335 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SARCH)->P=(yyvsp[0].TEXT); (yyval.SARCH)=(yyvsp[-3].SARCH);}
#line 1817 "parser.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 336 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SARCH)->Size=(yyvsp[0].TEXT); (yyval.SARCH)=(yyvsp[-3].SARCH);}
#line 1823 "parser.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 337 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SARCH)->Cont=(yyvsp[0].TEXT); (yyval.SARCH)=(yyvsp[-3].SARCH);}
#line 1829 "parser.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 338 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SARCH)=new STRSARCH();}
#line 1835 "parser.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 341 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SPER)->Path=(yyvsp[0].TEXT); (yyval.SPER)=(yyvsp[-3].SPER);}
#line 1841 "parser.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 342 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SPER)->Ugo=(yyvsp[0].TEXT); (yyval.SPER)=(yyvsp[-3].SPER);}
#line 1847 "parser.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 343 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SPER)->R=(yyvsp[0].TEXT); (yyval.SPER)=(yyvsp[-3].SPER);}
#line 1853 "parser.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 344 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SPER) = new STRSPER();}
#line 1859 "parser.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 347 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1865 "parser.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 350 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SUSR)->Pwd=(yyvsp[0].TEXT); (yyval.SUSR)=(yyvsp[-3].SUSR);}
#line 1871 "parser.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 351 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SUSR)->Grp=(yyvsp[0].TEXT); (yyval.SUSR)=(yyvsp[-3].SUSR);}
#line 1877 "parser.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 352 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SUSR)->Usr=(yyvsp[0].TEXT); (yyval.SUSR)=(yyvsp[-3].SUSR);}
#line 1883 "parser.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 353 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SUSR) = new STRSUSR();}
#line 1889 "parser.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 355 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1895 "parser.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 357 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1901 "parser.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 360 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1907 "parser.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 363 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SINGRE)->Usr=(yyvsp[0].TEXT); (yyval.SINGRE)=(yyvsp[-3].SINGRE);}
#line 1913 "parser.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 364 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SINGRE)->Pwd=(yyvsp[0].TEXT); (yyval.SINGRE)=(yyvsp[-3].SINGRE);}
#line 1919 "parser.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 365 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SINGRE)->Id=(yyvsp[0].TEXT); (yyval.SINGRE)=(yyvsp[-3].SINGRE);}
#line 1925 "parser.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 366 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SINGRE)= new STRSINGRE();}
#line 1931 "parser.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 368 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SEXT)->Id=(yyvsp[0].TEXT); (yyval.SEXT)=(yyvsp[-3].SEXT);}
#line 1937 "parser.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 369 "sintactico.y" /* yacc.c:1652  */
    {(yyvsp[-3].SEXT)->Type=(yyvsp[0].TEXT); (yyval.SEXT)=(yyvsp[-3].SEXT);}
#line 1943 "parser.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 370 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1949 "parser.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 371 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SEXT)= new STRSEXT();}
#line 1955 "parser.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 374 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1961 "parser.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 375 "sintactico.y" /* yacc.c:1652  */
    {}
#line 1967 "parser.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 377 "sintactico.y" /* yacc.c:1652  */
    {  if((yyvsp[0].SCREAR)->BSize && (yyvsp[0].SCREAR)->BUnit && (yyvsp[0].SCREAR)->BPath){Ope->Crear((yyvsp[0].SCREAR)->Size,(yyvsp[0].SCREAR)->Unit,(yyvsp[0].SCREAR)->Fit,(yyvsp[0].SCREAR)->Path);}else{std::cout << "MKDISK No Cumple Con Los Parametros Necesarios "<< std::endl;}}
#line 1973 "parser.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 378 "sintactico.y" /* yacc.c:1652  */
    {/*Se implementa Desde Produccion*/}
#line 1979 "parser.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 379 "sintactico.y" /* yacc.c:1652  */
    {
		if((yyvsp[0].SFORMA)->BName && (yyvsp[0].SFORMA)->BPath){
				if((yyvsp[0].SFORMA)->Realizar==0){
					if((yyvsp[0].SFORMA)->BSize){  Ope->Formato((yyvsp[0].SFORMA)->Size,(yyvsp[0].SFORMA)->Fit,(yyvsp[0].SFORMA)->Unit,(yyvsp[0].SFORMA)->Path,(yyvsp[0].SFORMA)->Type,(yyvsp[0].SFORMA)->Name);	}
					else{std::cout << "Para Crear Es Necesario Dar Un Tamanio "<< std::endl;}
				}else if((yyvsp[0].SFORMA)->Realizar==1){
						Ope->Borrar((yyvsp[0].SFORMA)->Delete,(yyvsp[0].SFORMA)->Path,(yyvsp[0].SFORMA)->Name);
				}else if((yyvsp[0].SFORMA)->Realizar==2){
						Ope->Aumentar((yyvsp[0].SFORMA)->Add,(yyvsp[0].SFORMA)->Path,(yyvsp[0].SFORMA)->Name,(yyvsp[0].SFORMA)->Unit);
				}else{
					std::cout << " No Se Ha Indicado Ninguna Operacion En El FDISK "<< std::endl;
				}
		}
		else{std::cout << "FDISK No Cumple Con Los Parametros Necesarios "<< std::endl;}
	}
#line 1999 "parser.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 394 "sintactico.y" /* yacc.c:1652  */
    {
		if((yyvsp[0].SMONTA)->BName && (yyvsp[0].SMONTA)->BPath){
			Ope->Montar((yyvsp[0].SMONTA)->Path,(yyvsp[0].SMONTA)->Name);
		}else{
			std::cout << "MOUNT No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
#line 2012 "parser.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 402 "sintactico.y" /* yacc.c:1652  */
    {/*Se implementa Desde Produccion*/}
#line 2018 "parser.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 403 "sintactico.y" /* yacc.c:1652  */
    {
		if((yyvsp[0].SREPOR)->BNameRep && (yyvsp[0].SREPOR)->BPath && (yyvsp[0].SREPOR)->BId){
			Ope->Reportes((yyvsp[0].SREPOR)->Id,(yyvsp[0].SREPOR)->NameRep,(yyvsp[0].SREPOR)->Path);
		}else{
			std::cout << "REP No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
#line 2031 "parser.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 411 "sintactico.y" /* yacc.c:1652  */
    {/*Desde Produ*/}
#line 2037 "parser.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 414 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2043 "parser.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 415 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2049 "parser.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 416 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2055 "parser.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 417 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2061 "parser.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 418 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2067 "parser.cpp" /* yacc.c:1652  */
    break;

  case 77:
#line 419 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2073 "parser.cpp" /* yacc.c:1652  */
    break;

  case 78:
#line 420 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2079 "parser.cpp" /* yacc.c:1652  */
    break;

  case 79:
#line 421 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2085 "parser.cpp" /* yacc.c:1652  */
    break;

  case 80:
#line 422 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2091 "parser.cpp" /* yacc.c:1652  */
    break;

  case 81:
#line 423 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2097 "parser.cpp" /* yacc.c:1652  */
    break;

  case 82:
#line 424 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2103 "parser.cpp" /* yacc.c:1652  */
    break;

  case 83:
#line 425 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2109 "parser.cpp" /* yacc.c:1652  */
    break;

  case 84:
#line 426 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2115 "parser.cpp" /* yacc.c:1652  */
    break;

  case 85:
#line 427 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2121 "parser.cpp" /* yacc.c:1652  */
    break;

  case 86:
#line 428 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2127 "parser.cpp" /* yacc.c:1652  */
    break;

  case 87:
#line 429 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2133 "parser.cpp" /* yacc.c:1652  */
    break;

  case 88:
#line 430 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2139 "parser.cpp" /* yacc.c:1652  */
    break;

  case 89:
#line 431 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2145 "parser.cpp" /* yacc.c:1652  */
    break;

  case 90:
#line 432 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2151 "parser.cpp" /* yacc.c:1652  */
    break;

  case 91:
#line 433 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2157 "parser.cpp" /* yacc.c:1652  */
    break;

  case 92:
#line 434 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2163 "parser.cpp" /* yacc.c:1652  */
    break;

  case 93:
#line 435 "sintactico.y" /* yacc.c:1652  */
    {}
#line 2169 "parser.cpp" /* yacc.c:1652  */
    break;

  case 94:
#line 442 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR); (yyval.SCREAR)->Size=atoi((yyvsp[0].TEXT)); (yyval.SCREAR)->BSize=true;  }
#line 2175 "parser.cpp" /* yacc.c:1652  */
    break;

  case 95:
#line 443 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR);  (yyval.SCREAR)->Fit[0]=(yyvsp[0].TEXT)[0]; (yyval.SCREAR)->Fit[1]=(yyvsp[0].TEXT)[1]; }
#line 2181 "parser.cpp" /* yacc.c:1652  */
    break;

  case 96:
#line 444 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR); (yyval.SCREAR)->Unit=(yyvsp[0].TEXT)[0]; (yyval.SCREAR)->BUnit=true;}
#line 2187 "parser.cpp" /* yacc.c:1652  */
    break;

  case 97:
#line 445 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR);  (yyval.SCREAR)->Path=toString((yyvsp[0].TEXT));  (yyval.SCREAR)->BPath=true; }
#line 2193 "parser.cpp" /* yacc.c:1652  */
    break;

  case 98:
#line 446 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SCREAR) = new STRCREAR();}
#line 2199 "parser.cpp" /* yacc.c:1652  */
    break;

  case 99:
#line 448 "sintactico.y" /* yacc.c:1652  */
    {Ope->BorrarDisco(toString((yyvsp[0].TEXT)));}
#line 2205 "parser.cpp" /* yacc.c:1652  */
    break;

  case 100:
#line 451 "sintactico.y" /* yacc.c:1652  */
    {std::copy(std::begin((yyvsp[0].TEXT)), std::end((yyvsp[0].TEXT)), std::begin((yyval.TEXT)));}
#line 2211 "parser.cpp" /* yacc.c:1652  */
    break;

  case 101:
#line 452 "sintactico.y" /* yacc.c:1652  */
    {std::string Tempo=(yyvsp[0].TEXT); Tempo=Tempo.substr(1,Tempo.length()-1); strcpy((yyval.TEXT),Tempo.c_str());}
#line 2217 "parser.cpp" /* yacc.c:1652  */
    break;

  case 102:
#line 456 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Size=atoi((yyvsp[0].TEXT)); (yyval.SFORMA)->BSize=true; 	if((yyval.SFORMA)->Realizar==-1)(yyval.SFORMA)->Realizar=0;}
#line 2223 "parser.cpp" /* yacc.c:1652  */
    break;

  case 103:
#line 457 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Fit[0]=(yyvsp[0].TEXT)[0]; (yyval.SFORMA)->Fit[1]=(yyvsp[0].TEXT)[1];}
#line 2229 "parser.cpp" /* yacc.c:1652  */
    break;

  case 104:
#line 458 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Unit=(yyvsp[0].TEXT)[0];}
#line 2235 "parser.cpp" /* yacc.c:1652  */
    break;

  case 105:
#line 459 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA);   (yyval.SFORMA)->Path=toString((yyvsp[0].TEXT));   (yyval.SFORMA)->BPath=true; }
#line 2241 "parser.cpp" /* yacc.c:1652  */
    break;

  case 106:
#line 460 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Type=(yyvsp[0].TEXT)[0];}
#line 2247 "parser.cpp" /* yacc.c:1652  */
    break;

  case 107:
#line 461 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Delete=toString((yyvsp[0].TEXT));   if((yyval.SFORMA)->Realizar==-1)(yyval.SFORMA)->Realizar=1;}
#line 2253 "parser.cpp" /* yacc.c:1652  */
    break;

  case 108:
#line 462 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Name=toString((yyvsp[0].TEXT)); (yyval.SFORMA)->BName=true;}
#line 2259 "parser.cpp" /* yacc.c:1652  */
    break;

  case 109:
#line 463 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Add=atoi((yyvsp[0].TEXT));    if((yyval.SFORMA)->Realizar==-1)(yyval.SFORMA)->Realizar=2;}
#line 2265 "parser.cpp" /* yacc.c:1652  */
    break;

  case 110:
#line 464 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SFORMA)= new STRFORMATO();}
#line 2271 "parser.cpp" /* yacc.c:1652  */
    break;

  case 111:
#line 469 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SMONTA)=(yyvsp[-3].SMONTA);  (yyval.SMONTA)->Path=toString((yyvsp[0].TEXT));   (yyval.SMONTA)->BPath=true; }
#line 2277 "parser.cpp" /* yacc.c:1652  */
    break;

  case 112:
#line 470 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SMONTA)=(yyvsp[-3].SMONTA);  (yyval.SMONTA)->BName=true; (yyval.SMONTA)->Name=toString((yyvsp[0].TEXT));}
#line 2283 "parser.cpp" /* yacc.c:1652  */
    break;

  case 113:
#line 471 "sintactico.y" /* yacc.c:1652  */
    { (yyval.SMONTA) = new STRMONTAR();}
#line 2289 "parser.cpp" /* yacc.c:1652  */
    break;

  case 114:
#line 474 "sintactico.y" /* yacc.c:1652  */
    {Ope->Desmontar(toString((yyvsp[0].TEXT)));}
#line 2295 "parser.cpp" /* yacc.c:1652  */
    break;

  case 115:
#line 476 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SREPOR)=(yyvsp[-3].SREPOR); (yyval.SREPOR)->BId=true; (yyval.SREPOR)->Id=toString((yyvsp[0].TEXT));}
#line 2301 "parser.cpp" /* yacc.c:1652  */
    break;

  case 116:
#line 477 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SREPOR)=(yyvsp[-3].SREPOR);  (yyval.SREPOR)->Path=toString((yyvsp[0].TEXT));  (yyval.SREPOR)->BPath=true; }
#line 2307 "parser.cpp" /* yacc.c:1652  */
    break;

  case 117:
#line 478 "sintactico.y" /* yacc.c:1652  */
    {(yyval.SREPOR)=(yyvsp[-3].SREPOR);  (yyval.SREPOR)->BNameRep=true; (yyval.SREPOR)->NameRep=toString((yyvsp[0].TEXT));;}
#line 2313 "parser.cpp" /* yacc.c:1652  */
    break;

  case 118:
#line 479 "sintactico.y" /* yacc.c:1652  */
    { (yyval.SREPOR) = new STRREPORTE();}
#line 2319 "parser.cpp" /* yacc.c:1652  */
    break;

  case 119:
#line 481 "sintactico.y" /* yacc.c:1652  */
    {Ope->Ejecutar(toString((yyvsp[0].TEXT)));}
#line 2325 "parser.cpp" /* yacc.c:1652  */
    break;


#line 2329 "parser.cpp" /* yacc.c:1652  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 483 "sintactico.y" /* yacc.c:1918  */

