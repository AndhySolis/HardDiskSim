/* A Bison parser, made by GNU Bison 3.4.1.  */

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
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "sintactico.y"

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
std::string Input="";
int yyerror(const char* mens){
//metodo que se llama al haber un error sintactico
//SE IMPRIME EN CONSOLA EL ERROR


std::cout <<mens<<" antes de comenzar el token: "<<yytext<<std::endl<<"Linea "<<yylineno<<"    Columna "<<columna<<"    "<<  std::endl;
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
	std::string Ruta="";	
};
//FASE 2
struct STRSEXT{
	std::string Id="";
	bool IdB=false;
	std::string Type="fast"; 
	std::string Ext="2fs";
};
struct STRSINGRE{ 
	std::string Usr;
	std::string Pwd;
	std::string Id;
};
struct STRSUSR{ 
	std::string Usr="";
	bool UsrB=false;
	std::string Pwd="";
	bool PwdB=false;
	std::string Grp="";
	bool GrpB=false;
};
struct STRSPER{
	std::string Path="";
	bool PathB=false;
	std::string Ugo="";
	bool UgoB=false;
	std::string R="0"; 
};
struct STRSARCH{
	std::string Path;
	bool PathB=false;
	std::string P="0";
	std::string Size="0";
	std::string Cont="";   
};
struct STRSEDIT{
	std::string Path="";
	bool PathB=false;
	std::string Cont="";
	bool ContB=false;   
};
struct STRSREN{
	std::string Path="";
	bool PathB=false;
	std::string Name="";  
	bool NameB=false;
};
struct STRSDIR{
	std::string Path;
	bool PathB=true;
	std::string P="0";  
};
struct STRSCOP{
	std::string Path;
	bool PathB=false;
	std::string Dest;
	bool DestB=false;   
};
struct STRSMOV{
	std::string Path;
	bool PathB=false;
	std::string Dest;
	bool DestB=false; 
};
struct STRSFIN{
	std::string Path="";
	bool PathB=false;
	std::string Name="";  
	bool NameB=false;
};
struct STRSCHOW{
	std::string Path;
	bool PathB=false;
	std::string R="0";
	std::string Usr; 
	bool UsrB=false;
};
struct STRSCHG{
	std::string Usr;
	bool UsrB=false;
	std::string Grp;
	bool GrpB=false; 
};

struct STRDITA{
	std::string Concatenar;
};


#line 235 "parser.cpp"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    loss = 312,
    ruta = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 168 "sintactico.y"


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

#line 362 "parser.cpp"

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


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#define YYLAST   272

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  118
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  245

#define YYUNDEFTOK  2
#define YYMAXUTOK   313

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
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   292,   292,   293,   295,   296,   302,   305,   308,   311,
     312,   313,   316,   317,   318,   319,   322,   323,   324,   327,
     328,   329,   332,   333,   334,   337,   338,   339,   342,   343,
     344,   347,   348,   349,   352,   355,   358,   359,   360,   361,
     362,   365,   366,   367,   368,   371,   374,   375,   376,   377,
     379,   381,   384,   387,   388,   389,   390,   392,   393,   394,
     395,   397,   398,   401,   402,   403,   418,   426,   427,   435,
     438,   446,   447,   448,   449,   450,   456,   457,   463,   469,
     470,   471,   477,   483,   489,   495,   501,   507,   513,   519,
     520,   521,   528,   529,   530,   531,   532,   534,   537,   538,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   555,
     556,   557,   560,   562,   563,   564,   565,   566,   568
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
  "recovery", "loss", "ruta", "$accept", "PASSWORD", "TERMIIDENTI",
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
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF -69

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-69)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     112,   -69,   -12,   -69,   -69,    -6,   -69,    25,   -69,   -69,
     -69,    38,    42,   -69,    39,   -69,   -69,    24,    61,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,    71,   109,
     -69,   -69,   -69,     7,   -11,    80,    44,    58,   -13,    81,
     -17,   -69,   -69,   -15,     1,   -69,    31,   -69,   -69,   -69,
      62,    -3,     0,   -69,   134,   -69,   153,    85,   -69,   -19,
     -69,    77,   128,   131,   132,   138,   148,   169,   170,   171,
     172,   173,   174,   175,   176,   -69,   177,   178,   179,   180,
     181,   182,   183,   -69,   184,   185,   186,   187,   188,   189,
     -69,   190,   191,   192,   -69,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   -69,   -69,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,    16,   130,    16,   106,   106,   106,
      16,    16,   106,   106,   106,   106,    16,   106,    16,   106,
      16,    16,    16,    16,    16,    16,   106,    16,    16,   226,
      16,    16,    16,   106,   106,   106,   106,   106,   106,   126,
     106,   106,   227,   228,   229,   230,    16,   232,   233,   231,
      16,   234,   106,   106,   236,    16,   106,    16,   106,   106,
      16,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   237,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    96,     0,   108,   111,     0,   117,     0,    52,    56,
      60,     0,     0,    49,     0,    44,    40,     0,     0,    33,
      30,    27,    24,    21,    18,    15,    11,     8,     0,     0,
      91,    90,    89,    88,    87,    86,    85,    84,    83,    82,
      81,    80,    79,    78,    77,    76,    75,    74,    73,    72,
      71,    70,     0,    62,    63,    64,    65,    66,    67,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     0,     0,     0,     0,     0,
      37,     0,     0,     0,    43,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    61,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    99,    98,    97,   112,   118,     5,     4,    51,    50,
      45,    35,    34,     7,     6,    10,     9,    14,    13,    17,
      16,    20,    19,    23,    22,    26,    29,    28,    31,    32,
      38,    36,    39,    41,    42,    48,    46,    47,    55,    53,
       3,    54,     2,    58,    57,     0,    92,    93,    94,    95,
     100,   101,   102,   103,   104,   105,   106,   107,   109,   110,
     114,   115,   113,   116,    59
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -69,   -69,   -40,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   220,   -69,   -69,   -68,
     -69,   -69,   -69,   -69,   -69
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   221,   188,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,   183,
      56,    57,    58,    59,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     104,   120,    88,    86,   121,    89,   122,    82,    61,    73,
       1,     2,     3,     4,     5,     6,     7,    74,   101,    62,
     181,    92,   102,   103,   182,    87,    90,    91,    83,    75,
       8,     9,    10,    11,    12,    71,    13,    14,    15,   123,
      93,    94,    72,    16,    17,    63,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,   185,    95,
      96,    64,   191,   192,    78,    65,    97,    66,   197,    67,
     199,    79,   201,   202,   203,   204,   205,   206,    80,   208,
     209,    68,   211,   212,   213,    81,   124,    98,   189,   190,
      99,   100,   193,   194,   195,   196,    69,   198,   229,   200,
      76,    84,   233,    77,    85,   118,   207,   238,   119,   240,
     186,   187,   243,   214,   215,   216,   217,   218,   219,   222,
     223,   224,     1,     2,     3,     4,     5,     6,     7,   220,
     186,   187,   235,   236,    70,   184,   239,   125,   241,   242,
     126,   127,     8,     9,    10,    11,    12,   128,    13,    14,
      15,   106,   107,   108,   109,    16,    17,   129,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
     110,   111,   112,   113,   114,   115,   116,   117,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   210,
     225,   226,     0,     0,   227,   230,   228,   232,   231,   237,
     234,     0,   244,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   105
};

static const yytype_int16 yycheck[] =
{
       0,    20,    17,    20,    23,    20,    25,    20,    20,    20,
      10,    11,    12,    13,    14,    15,    16,    28,    21,    25,
       4,    20,    25,    26,     8,    42,    41,    42,    41,    40,
      30,    31,    32,    33,    34,    28,    36,    37,    38,    58,
      39,    40,    35,    43,    44,    20,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,   126,    28,
      29,    23,   130,   131,    20,    23,    35,    28,   136,    45,
     138,    27,   140,   141,   142,   143,   144,   145,    20,   147,
     148,    20,   150,   151,   152,    27,     9,    25,   128,   129,
      28,    29,   132,   133,   134,   135,    25,   137,   166,   139,
      20,    20,   170,    23,    23,    20,   146,   175,    23,   177,
       4,     5,   180,   153,   154,   155,   156,   157,   158,   159,
     160,   161,    10,    11,    12,    13,    14,    15,    16,     3,
       4,     5,   172,   173,    25,     5,   176,     9,   178,   179,
       9,     9,    30,    31,    32,    33,    34,     9,    36,    37,
      38,    17,    18,    19,    20,    43,    44,     9,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      17,    18,    19,    20,    21,    22,    23,    24,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     3,
       3,     3,    -1,    -1,     5,     3,     6,     6,     5,     3,
       6,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52
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
      93,    20,    25,    20,    23,    23,    28,    45,    20,    25,
      25,    28,    35,    20,    28,    40,    20,    23,    20,    27,
      20,    27,    20,    41,    20,    23,    20,    42,    17,    20,
      41,    42,    20,    39,    40,    28,    29,    35,    25,    28,
      29,    21,    25,    26,     0,    85,    17,    18,    19,    20,
      17,    18,    19,    20,    21,    22,    23,    24,    20,    23,
      20,    23,    25,    58,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,     9,     9,     9,     9,     9,
       9,     4,     8,    88,     5,    88,     4,     5,    61,    61,
      61,    88,    88,    61,    61,    61,    61,    88,    61,    88,
      61,    88,    88,    88,    88,    88,    88,    61,    88,    88,
       3,    88,    88,    88,    61,    61,    61,    61,    61,    61,
       3,    60,    61,    61,    61,     3,     3,     5,     6,    88,
       3,     5,     6,    88,     6,    61,    61,     3,    88,    61,
      88,    61,    61,    88,     5
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    60,    61,    61,    62,    63,    64,    65,
      65,    65,    66,    66,    66,    66,    67,    67,    67,    68,
      68,    68,    69,    69,    69,    70,    70,    70,    71,    71,
      71,    72,    72,    72,    73,    74,    75,    75,    75,    75,
      75,    76,    76,    76,    76,    77,    78,    78,    78,    78,
      79,    80,    81,    82,    82,    82,    82,    83,    83,    83,
      83,    84,    84,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    86,    86,    86,    86,    86,    87,    88,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    90,
      90,    90,    91,    92,    92,    92,    92,    92,    93
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     4,     4,     1,     4,
       4,     1,     2,     4,     4,     1,     4,     4,     1,     4,
       4,     1,     4,     4,     1,     2,     4,     1,     4,     4,
       1,     4,     4,     1,     4,     4,     4,     2,     4,     4,
       1,     4,     4,     2,     1,     4,     4,     4,     4,     1,
       4,     4,     1,     4,     4,     4,     1,     4,     4,     5,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     4,     4,     4,     1,     4,     1,     1,
       4,     4,     4,     4,     4,     4,     4,     4,     1,     4,
       4,     1,     4,     4,     4,     4,     4,     1,     4
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
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
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
#line 292 "sintactico.y"
    {std::copy(std::begin((yyvsp[0].TEXT)), std::end((yyvsp[0].TEXT)), std::begin((yyval.TEXT)));}
#line 1631 "parser.cpp"
    break;

  case 3:
#line 293 "sintactico.y"
    {std::string Tempo=toString((yyvsp[0].TEXT)); strcpy((yyval.TEXT),Tempo.c_str());}
#line 1637 "parser.cpp"
    break;

  case 4:
#line 295 "sintactico.y"
    {std::copy(std::begin((yyvsp[0].TEXT)), std::end((yyvsp[0].TEXT)), std::begin((yyval.TEXT)));}
#line 1643 "parser.cpp"
    break;

  case 5:
#line 296 "sintactico.y"
    {std::string Tempo=(yyvsp[0].TEXT); Tempo=Tempo.substr(1,Tempo.length()-2); strcpy((yyval.TEXT),Tempo.c_str());}
#line 1649 "parser.cpp"
    break;

  case 6:
#line 302 "sintactico.y"
    {Ope->Loss((yyvsp[0].TEXT));}
#line 1655 "parser.cpp"
    break;

  case 7:
#line 305 "sintactico.y"
    {Ope->Recovery((yyvsp[0].TEXT));}
#line 1661 "parser.cpp"
    break;

  case 8:
#line 308 "sintactico.y"
    {std::string Entrada; std::cout<<"Modo Pausa, Escribar Cualquier Cosa Para Salir"<<std::endl;std::cin>>Entrada;}
#line 1667 "parser.cpp"
    break;

  case 9:
#line 311 "sintactico.y"
    {(yyvsp[-3].SCHG)->Grp=(yyvsp[0].TEXT); (yyval.SCHG)=(yyvsp[-3].SCHG); (yyval.SCHG)->GrpB=true;}
#line 1673 "parser.cpp"
    break;

  case 10:
#line 312 "sintactico.y"
    {(yyvsp[-3].SCHG)->Usr=(yyvsp[0].TEXT); (yyval.SCHG)=(yyvsp[-3].SCHG); (yyval.SCHG)->UsrB=true;}
#line 1679 "parser.cpp"
    break;

  case 11:
#line 313 "sintactico.y"
    {(yyval.SCHG)= new STRSCHG();}
#line 1685 "parser.cpp"
    break;

  case 12:
#line 316 "sintactico.y"
    {(yyvsp[-1].SCHOW)->R="1"; (yyval.SCHOW)=(yyvsp[-1].SCHOW);}
#line 1691 "parser.cpp"
    break;

  case 13:
#line 317 "sintactico.y"
    {(yyvsp[-3].SCHOW)->Usr=(yyvsp[0].TEXT); (yyval.SCHOW)=(yyvsp[-3].SCHOW); (yyval.SCHOW)->UsrB=true;}
#line 1697 "parser.cpp"
    break;

  case 14:
#line 318 "sintactico.y"
    {(yyvsp[-3].SCHOW)->Path=(yyvsp[0].TEXT); (yyval.SCHOW)=(yyvsp[-3].SCHOW); (yyval.SCHOW)->PathB=true;}
#line 1703 "parser.cpp"
    break;

  case 15:
#line 319 "sintactico.y"
    {(yyval.SCHOW)= new STRSCHOW();}
#line 1709 "parser.cpp"
    break;

  case 16:
#line 322 "sintactico.y"
    {(yyvsp[-3].SFIN)->Name=(yyvsp[0].TEXT); (yyval.SFIN)=(yyvsp[-3].SFIN); (yyval.SFIN)->NameB=true;}
#line 1715 "parser.cpp"
    break;

  case 17:
#line 323 "sintactico.y"
    {(yyvsp[-3].SFIN)->Path=(yyvsp[0].TEXT); (yyval.SFIN)=(yyvsp[-3].SFIN); (yyval.SFIN)->PathB=true;}
#line 1721 "parser.cpp"
    break;

  case 18:
#line 324 "sintactico.y"
    {(yyval.SFIN)=new STRSFIN();}
#line 1727 "parser.cpp"
    break;

  case 19:
#line 327 "sintactico.y"
    {(yyvsp[-3].SMOV)->Dest=(yyvsp[0].TEXT); (yyval.SMOV)=(yyvsp[-3].SMOV);  (yyval.SMOV)->DestB=true;}
#line 1733 "parser.cpp"
    break;

  case 20:
#line 328 "sintactico.y"
    {(yyvsp[-3].SMOV)->Path=(yyvsp[0].TEXT); (yyval.SMOV)=(yyvsp[-3].SMOV); (yyval.SMOV)->PathB=true;}
#line 1739 "parser.cpp"
    break;

  case 21:
#line 329 "sintactico.y"
    {(yyval.SMOV)=new STRSMOV();}
#line 1745 "parser.cpp"
    break;

  case 22:
#line 332 "sintactico.y"
    {(yyvsp[-3].SCOP)->Dest=(yyvsp[0].TEXT); (yyval.SCOP)=(yyvsp[-3].SCOP); (yyval.SCOP)->DestB=true;}
#line 1751 "parser.cpp"
    break;

  case 23:
#line 333 "sintactico.y"
    {(yyvsp[-3].SCOP)->Path=(yyvsp[0].TEXT); (yyval.SCOP)=(yyvsp[-3].SCOP); (yyval.SCOP)->PathB=true;}
#line 1757 "parser.cpp"
    break;

  case 24:
#line 334 "sintactico.y"
    {(yyval.SCOP)=new STRSCOP();}
#line 1763 "parser.cpp"
    break;

  case 25:
#line 337 "sintactico.y"
    {(yyvsp[-1].SDIR)->P="1"; (yyval.SDIR)=(yyvsp[-1].SDIR);}
#line 1769 "parser.cpp"
    break;

  case 26:
#line 338 "sintactico.y"
    {(yyvsp[-3].SDIR)->Path=(yyvsp[0].TEXT); (yyval.SDIR)=(yyvsp[-3].SDIR); (yyval.SDIR)->PathB=true;}
#line 1775 "parser.cpp"
    break;

  case 27:
#line 339 "sintactico.y"
    {(yyval.SDIR)= new STRSDIR();}
#line 1781 "parser.cpp"
    break;

  case 28:
#line 342 "sintactico.y"
    {(yyvsp[-3].SREN)->Name=(yyvsp[0].TEXT); (yyval.SREN)=(yyvsp[-3].SREN); (yyval.SREN)->NameB=true;}
#line 1787 "parser.cpp"
    break;

  case 29:
#line 343 "sintactico.y"
    {(yyvsp[-3].SREN)->Path=(yyvsp[0].TEXT); (yyval.SREN)=(yyvsp[-3].SREN); (yyval.SREN)->PathB=true;}
#line 1793 "parser.cpp"
    break;

  case 30:
#line 344 "sintactico.y"
    {(yyval.SREN)= new STRSREN();}
#line 1799 "parser.cpp"
    break;

  case 31:
#line 347 "sintactico.y"
    {(yyvsp[-3].SEDIT)->Path=(yyvsp[0].TEXT); (yyval.SEDIT)=(yyvsp[-3].SEDIT); (yyval.SEDIT)->PathB=true;}
#line 1805 "parser.cpp"
    break;

  case 32:
#line 348 "sintactico.y"
    {(yyvsp[-3].SEDIT)->Cont=(yyvsp[0].TEXT); (yyval.SEDIT)=(yyvsp[-3].SEDIT); (yyval.SEDIT)->ContB=true;}
#line 1811 "parser.cpp"
    break;

  case 33:
#line 349 "sintactico.y"
    {(yyval.SEDIT)= new STRSEDIT();}
#line 1817 "parser.cpp"
    break;

  case 34:
#line 352 "sintactico.y"
    {Ope->Rem((yyvsp[0].TEXT));}
#line 1823 "parser.cpp"
    break;

  case 35:
#line 355 "sintactico.y"
    {Ope->Cat((yyvsp[0].TEXT));}
#line 1829 "parser.cpp"
    break;

  case 36:
#line 358 "sintactico.y"
    {(yyvsp[-3].SARCH)->Path=(yyvsp[0].TEXT); (yyval.SARCH)=(yyvsp[-3].SARCH); (yyval.SARCH)->PathB=true;}
#line 1835 "parser.cpp"
    break;

  case 37:
#line 359 "sintactico.y"
    {(yyvsp[-1].SARCH)->P="1"; (yyval.SARCH)=(yyvsp[-1].SARCH);}
#line 1841 "parser.cpp"
    break;

  case 38:
#line 360 "sintactico.y"
    {(yyvsp[-3].SARCH)->Size=(yyvsp[0].TEXT); (yyval.SARCH)=(yyvsp[-3].SARCH);}
#line 1847 "parser.cpp"
    break;

  case 39:
#line 361 "sintactico.y"
    {(yyvsp[-3].SARCH)->Cont=(yyvsp[0].TEXT); (yyval.SARCH)=(yyvsp[-3].SARCH);}
#line 1853 "parser.cpp"
    break;

  case 40:
#line 362 "sintactico.y"
    {(yyval.SARCH)=new STRSARCH();}
#line 1859 "parser.cpp"
    break;

  case 41:
#line 365 "sintactico.y"
    {(yyvsp[-3].SPER)->Path=(yyvsp[0].TEXT); (yyval.SPER)=(yyvsp[-3].SPER); (yyval.SPER)->PathB=true;}
#line 1865 "parser.cpp"
    break;

  case 42:
#line 366 "sintactico.y"
    {(yyvsp[-3].SPER)->Ugo=(yyvsp[0].TEXT); (yyval.SPER)=(yyvsp[-3].SPER);  (yyval.SPER)->UgoB=true;}
#line 1871 "parser.cpp"
    break;

  case 43:
#line 367 "sintactico.y"
    {(yyvsp[-1].SPER)->R="1"; (yyval.SPER)=(yyvsp[-1].SPER);}
#line 1877 "parser.cpp"
    break;

  case 44:
#line 368 "sintactico.y"
    {(yyval.SPER) = new STRSPER();}
#line 1883 "parser.cpp"
    break;

  case 45:
#line 371 "sintactico.y"
    {Ope->Rmusr((yyvsp[0].TEXT));}
#line 1889 "parser.cpp"
    break;

  case 46:
#line 374 "sintactico.y"
    {(yyvsp[-3].SUSR)->Pwd=(yyvsp[0].TEXT); (yyval.SUSR)=(yyvsp[-3].SUSR); (yyval.SUSR)->PwdB=true;}
#line 1895 "parser.cpp"
    break;

  case 47:
#line 375 "sintactico.y"
    {(yyvsp[-3].SUSR)->Grp=(yyvsp[0].TEXT); (yyval.SUSR)=(yyvsp[-3].SUSR); (yyval.SUSR)->GrpB=true;}
#line 1901 "parser.cpp"
    break;

  case 48:
#line 376 "sintactico.y"
    {(yyvsp[-3].SUSR)->Usr=(yyvsp[0].TEXT); (yyval.SUSR)=(yyvsp[-3].SUSR); (yyval.SUSR)->UsrB=true;}
#line 1907 "parser.cpp"
    break;

  case 49:
#line 377 "sintactico.y"
    {(yyval.SUSR) = new STRSUSR();}
#line 1913 "parser.cpp"
    break;

  case 50:
#line 379 "sintactico.y"
    {Ope->Rmgrp((yyvsp[0].TEXT));}
#line 1919 "parser.cpp"
    break;

  case 51:
#line 381 "sintactico.y"
    {Ope->Mkgrp((yyvsp[0].TEXT));}
#line 1925 "parser.cpp"
    break;

  case 52:
#line 384 "sintactico.y"
    {Ope->Logout();}
#line 1931 "parser.cpp"
    break;

  case 53:
#line 387 "sintactico.y"
    {(yyvsp[-3].SINGRE)->Usr=(yyvsp[0].TEXT); (yyval.SINGRE)=(yyvsp[-3].SINGRE);}
#line 1937 "parser.cpp"
    break;

  case 54:
#line 388 "sintactico.y"
    {(yyvsp[-3].SINGRE)->Pwd=(yyvsp[0].TEXT); (yyval.SINGRE)=(yyvsp[-3].SINGRE);}
#line 1943 "parser.cpp"
    break;

  case 55:
#line 389 "sintactico.y"
    {(yyvsp[-3].SINGRE)->Id=(yyvsp[0].TEXT); (yyval.SINGRE)=(yyvsp[-3].SINGRE);}
#line 1949 "parser.cpp"
    break;

  case 56:
#line 390 "sintactico.y"
    {(yyval.SINGRE)= new STRSINGRE();}
#line 1955 "parser.cpp"
    break;

  case 57:
#line 392 "sintactico.y"
    {(yyvsp[-3].SEXT)->Id=(yyvsp[0].TEXT); (yyval.SEXT)=(yyvsp[-3].SEXT); (yyval.SEXT)->IdB=true;}
#line 1961 "parser.cpp"
    break;

  case 58:
#line 393 "sintactico.y"
    {(yyvsp[-3].SEXT)->Type=(yyvsp[0].TEXT); (yyval.SEXT)=(yyvsp[-3].SEXT);}
#line 1967 "parser.cpp"
    break;

  case 59:
#line 394 "sintactico.y"
    { (yyval.SEXT)=(yyvsp[-4].SEXT); (yyval.SEXT)->Ext[0]=(yyvsp[-1].TEXT)[0]; (yyval.SEXT)->Ext[1]=(yyvsp[0].TEXT)[0]; (yyval.SEXT)->Ext[2]=(yyvsp[0].TEXT)[1];}
#line 1973 "parser.cpp"
    break;

  case 60:
#line 395 "sintactico.y"
    {(yyval.SEXT)= new STRSEXT();}
#line 1979 "parser.cpp"
    break;

  case 61:
#line 397 "sintactico.y"
    {}
#line 1985 "parser.cpp"
    break;

  case 62:
#line 398 "sintactico.y"
    {}
#line 1991 "parser.cpp"
    break;

  case 63:
#line 401 "sintactico.y"
    {  if((yyvsp[0].SCREAR)->BSize && (yyvsp[0].SCREAR)->BUnit && (yyvsp[0].SCREAR)->BPath){Ope->Crear((yyvsp[0].SCREAR)->Size,(yyvsp[0].SCREAR)->Unit,(yyvsp[0].SCREAR)->Fit,(yyvsp[0].SCREAR)->Path);}else{std::cout << "MKDISK No Cumple Con Los Parametros Necesarios "<< std::endl;}}
#line 1997 "parser.cpp"
    break;

  case 64:
#line 402 "sintactico.y"
    {/*Se implementa Desde Produccion*/}
#line 2003 "parser.cpp"
    break;

  case 65:
#line 403 "sintactico.y"
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
#line 2023 "parser.cpp"
    break;

  case 66:
#line 418 "sintactico.y"
    {
		if((yyvsp[0].SMONTA)->BName && (yyvsp[0].SMONTA)->BPath){
			Ope->Montar((yyvsp[0].SMONTA)->Path,(yyvsp[0].SMONTA)->Name);
		}else{
			std::cout << "MOUNT No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
#line 2036 "parser.cpp"
    break;

  case 67:
#line 426 "sintactico.y"
    {/*Se implementa Desde Produccion*/}
#line 2042 "parser.cpp"
    break;

  case 68:
#line 427 "sintactico.y"
    {
		if((yyvsp[0].SREPOR)->BNameRep && (yyvsp[0].SREPOR)->BPath && (yyvsp[0].SREPOR)->BId){
			Ope->Reportes((yyvsp[0].SREPOR)->Id,(yyvsp[0].SREPOR)->NameRep,(yyvsp[0].SREPOR)->Path,(yyvsp[0].SREPOR)->Ruta);
		}else{
			std::cout << "REP No Cumple Con Los Parametros Necesarios "<< std::endl;
		}

	}
#line 2055 "parser.cpp"
    break;

  case 69:
#line 435 "sintactico.y"
    {/*Desde Produ*/}
#line 2061 "parser.cpp"
    break;

  case 70:
#line 438 "sintactico.y"
    {
		if((yyvsp[0].SEXT)->IdB){Ope->Mkfs((yyvsp[0].SEXT)->Id,(yyvsp[0].SEXT)->Type,(yyvsp[0].SEXT)->Ext);}
		else{
			std::cout << "MKFS le hace falta parametro 'Id', Enter Aceptar"<< std::endl;
			std::cin>>Input;
		}
	}
#line 2073 "parser.cpp"
    break;

  case 71:
#line 446 "sintactico.y"
    {Ope->Login((yyvsp[0].SINGRE)->Usr,(yyvsp[0].SINGRE)->Pwd,(yyvsp[0].SINGRE)->Id);}
#line 2079 "parser.cpp"
    break;

  case 72:
#line 447 "sintactico.y"
    {}
#line 2085 "parser.cpp"
    break;

  case 73:
#line 448 "sintactico.y"
    {}
#line 2091 "parser.cpp"
    break;

  case 74:
#line 449 "sintactico.y"
    {}
#line 2097 "parser.cpp"
    break;

  case 75:
#line 450 "sintactico.y"
    {
		if((yyvsp[0].SUSR)->UsrB && (yyvsp[0].SUSR)->PwdB && (yyvsp[0].SUSR)->GrpB)
		Ope->Mkusr((yyvsp[0].SUSR)->Usr,(yyvsp[0].SUSR)->Pwd,(yyvsp[0].SUSR)->Grp);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para MKUSR"<<std::endl;
		}
#line 2108 "parser.cpp"
    break;

  case 76:
#line 456 "sintactico.y"
    {}
#line 2114 "parser.cpp"
    break;

  case 77:
#line 457 "sintactico.y"
    {
		if((yyvsp[0].SPER)->UgoB && (yyvsp[0].SPER)->PathB )
		Ope->Chmod((yyvsp[0].SPER)->Path,(yyvsp[0].SPER)->Ugo,(yyvsp[0].SPER)->R);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para CHMOD"<<std::endl;		
	}
#line 2125 "parser.cpp"
    break;

  case 78:
#line 463 "sintactico.y"
    {
		if((yyvsp[0].SARCH)->PathB)
		Ope->Mkfile((yyvsp[0].SARCH)->Path,(yyvsp[0].SARCH)->P,(yyvsp[0].SARCH)->Size,(yyvsp[0].SARCH)->Cont);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para MKFILE"<<std::endl;
	}
#line 2136 "parser.cpp"
    break;

  case 79:
#line 469 "sintactico.y"
    {}
#line 2142 "parser.cpp"
    break;

  case 80:
#line 470 "sintactico.y"
    {}
#line 2148 "parser.cpp"
    break;

  case 81:
#line 471 "sintactico.y"
    {
		if((yyvsp[0].SEDIT)->PathB && (yyvsp[0].SEDIT)->ContB )
		Ope->Edit((yyvsp[0].SEDIT)->Path,(yyvsp[0].SEDIT)->Cont);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para EDIT"<<std::endl;
	}
#line 2159 "parser.cpp"
    break;

  case 82:
#line 477 "sintactico.y"
    {
		if((yyvsp[0].SREN)->PathB && (yyvsp[0].SREN)->NameB)
		Ope->Ren((yyvsp[0].SREN)->Path,(yyvsp[0].SREN)->Name);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para REN"<<std::endl;
	}
#line 2170 "parser.cpp"
    break;

  case 83:
#line 483 "sintactico.y"
    {
		if((yyvsp[0].SDIR)->PathB)
		Ope->Mkdir((yyvsp[0].SDIR)->Path,(yyvsp[0].SDIR)->P);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para REN"<<std::endl;
	}
#line 2181 "parser.cpp"
    break;

  case 84:
#line 489 "sintactico.y"
    {
		if((yyvsp[0].SCOP)->PathB && (yyvsp[0].SCOP)->DestB)
		Ope->Cp((yyvsp[0].SCOP)->Path,(yyvsp[0].SCOP)->Dest);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para CP"<<std::endl;		
	}
#line 2192 "parser.cpp"
    break;

  case 85:
#line 495 "sintactico.y"
    {
		if((yyvsp[0].SMOV)->PathB && (yyvsp[0].SMOV)->DestB)
		Ope->Mv((yyvsp[0].SMOV)->Path,(yyvsp[0].SMOV)->Dest);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para MV"<<std::endl;					
	}
#line 2203 "parser.cpp"
    break;

  case 86:
#line 501 "sintactico.y"
    {
		if((yyvsp[0].SFIN)->PathB && (yyvsp[0].SFIN)->NameB)
		Ope->Find((yyvsp[0].SFIN)->Path,(yyvsp[0].SFIN)->Name);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para FIND"<<std::endl;
	}
#line 2214 "parser.cpp"
    break;

  case 87:
#line 507 "sintactico.y"
    {
		if((yyvsp[0].SCHOW)->PathB && (yyvsp[0].SCHOW)->UsrB)
		Ope->Chown((yyvsp[0].SCHOW)->Path,(yyvsp[0].SCHOW)->R,(yyvsp[0].SCHOW)->Usr);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para CHOWN"<<std::endl;	
	}
#line 2225 "parser.cpp"
    break;

  case 88:
#line 513 "sintactico.y"
    {
		if((yyvsp[0].SCHG)->GrpB && (yyvsp[0].SCHG)->UsrB)
		Ope->Chgrp((yyvsp[0].SCHG)->Usr,(yyvsp[0].SCHG)->Grp);
		else
		std::cout<<"No Se Cumplen Parametros Obligatorios para CHGRP"<<std::endl;
	}
#line 2236 "parser.cpp"
    break;

  case 89:
#line 519 "sintactico.y"
    {}
#line 2242 "parser.cpp"
    break;

  case 90:
#line 520 "sintactico.y"
    {}
#line 2248 "parser.cpp"
    break;

  case 91:
#line 521 "sintactico.y"
    {}
#line 2254 "parser.cpp"
    break;

  case 92:
#line 528 "sintactico.y"
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR); (yyval.SCREAR)->Size=atoi((yyvsp[0].TEXT)); (yyval.SCREAR)->BSize=true;  }
#line 2260 "parser.cpp"
    break;

  case 93:
#line 529 "sintactico.y"
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR);  (yyval.SCREAR)->Fit[0]=(yyvsp[0].TEXT)[0]; (yyval.SCREAR)->Fit[1]=(yyvsp[0].TEXT)[1]; }
#line 2266 "parser.cpp"
    break;

  case 94:
#line 530 "sintactico.y"
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR); (yyval.SCREAR)->Unit=(yyvsp[0].TEXT)[0]; (yyval.SCREAR)->BUnit=true;}
#line 2272 "parser.cpp"
    break;

  case 95:
#line 531 "sintactico.y"
    {(yyval.SCREAR)=(yyvsp[-3].SCREAR);  (yyval.SCREAR)->Path=toString((yyvsp[0].TEXT));  (yyval.SCREAR)->BPath=true; }
#line 2278 "parser.cpp"
    break;

  case 96:
#line 532 "sintactico.y"
    {(yyval.SCREAR) = new STRCREAR();}
#line 2284 "parser.cpp"
    break;

  case 97:
#line 534 "sintactico.y"
    {Ope->BorrarDisco(toString((yyvsp[0].TEXT)));}
#line 2290 "parser.cpp"
    break;

  case 98:
#line 537 "sintactico.y"
    {std::copy(std::begin((yyvsp[0].TEXT)), std::end((yyvsp[0].TEXT)), std::begin((yyval.TEXT)));}
#line 2296 "parser.cpp"
    break;

  case 99:
#line 538 "sintactico.y"
    {std::string Tempo=(yyvsp[0].TEXT); Tempo=Tempo.substr(1,Tempo.length()-2); strcpy((yyval.TEXT),Tempo.c_str());}
#line 2302 "parser.cpp"
    break;

  case 100:
#line 542 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Size=atoi((yyvsp[0].TEXT)); (yyval.SFORMA)->BSize=true; 	if((yyval.SFORMA)->Realizar==-1)(yyval.SFORMA)->Realizar=0;}
#line 2308 "parser.cpp"
    break;

  case 101:
#line 543 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Fit[0]=(yyvsp[0].TEXT)[0]; (yyval.SFORMA)->Fit[1]=(yyvsp[0].TEXT)[1];}
#line 2314 "parser.cpp"
    break;

  case 102:
#line 544 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Unit=(yyvsp[0].TEXT)[0];}
#line 2320 "parser.cpp"
    break;

  case 103:
#line 545 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA);   (yyval.SFORMA)->Path=toString((yyvsp[0].TEXT));   (yyval.SFORMA)->BPath=true; }
#line 2326 "parser.cpp"
    break;

  case 104:
#line 546 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Type=(yyvsp[0].TEXT)[0];}
#line 2332 "parser.cpp"
    break;

  case 105:
#line 547 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Delete=toString((yyvsp[0].TEXT));   if((yyval.SFORMA)->Realizar==-1)(yyval.SFORMA)->Realizar=1;}
#line 2338 "parser.cpp"
    break;

  case 106:
#line 548 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Name=toString((yyvsp[0].TEXT)); (yyval.SFORMA)->BName=true;}
#line 2344 "parser.cpp"
    break;

  case 107:
#line 549 "sintactico.y"
    {(yyval.SFORMA)=(yyvsp[-3].SFORMA); (yyval.SFORMA)->Add=atoi((yyvsp[0].TEXT));    if((yyval.SFORMA)->Realizar==-1)(yyval.SFORMA)->Realizar=2;}
#line 2350 "parser.cpp"
    break;

  case 108:
#line 550 "sintactico.y"
    {(yyval.SFORMA)= new STRFORMATO();}
#line 2356 "parser.cpp"
    break;

  case 109:
#line 555 "sintactico.y"
    {(yyval.SMONTA)=(yyvsp[-3].SMONTA);  (yyval.SMONTA)->Path=toString((yyvsp[0].TEXT));   (yyval.SMONTA)->BPath=true; }
#line 2362 "parser.cpp"
    break;

  case 110:
#line 556 "sintactico.y"
    {(yyval.SMONTA)=(yyvsp[-3].SMONTA);  (yyval.SMONTA)->BName=true; (yyval.SMONTA)->Name=toString((yyvsp[0].TEXT));}
#line 2368 "parser.cpp"
    break;

  case 111:
#line 557 "sintactico.y"
    { (yyval.SMONTA) = new STRMONTAR();}
#line 2374 "parser.cpp"
    break;

  case 112:
#line 560 "sintactico.y"
    {Ope->Desmontar(toString((yyvsp[0].TEXT)));}
#line 2380 "parser.cpp"
    break;

  case 113:
#line 562 "sintactico.y"
    {(yyval.SREPOR)=(yyvsp[-3].SREPOR); (yyval.SREPOR)->BId=true; (yyval.SREPOR)->Id=toString((yyvsp[0].TEXT));}
#line 2386 "parser.cpp"
    break;

  case 114:
#line 563 "sintactico.y"
    {(yyval.SREPOR)=(yyvsp[-3].SREPOR);  (yyval.SREPOR)->Path=toString((yyvsp[0].TEXT));  (yyval.SREPOR)->BPath=true; }
#line 2392 "parser.cpp"
    break;

  case 115:
#line 564 "sintactico.y"
    {(yyval.SREPOR)=(yyvsp[-3].SREPOR);  (yyval.SREPOR)->BNameRep=true; (yyval.SREPOR)->NameRep=toString((yyvsp[0].TEXT));;}
#line 2398 "parser.cpp"
    break;

  case 116:
#line 565 "sintactico.y"
    {(yyval.SREPOR)=(yyvsp[-3].SREPOR);   (yyval.SREPOR)->Ruta=toString((yyvsp[0].TEXT));;}
#line 2404 "parser.cpp"
    break;

  case 117:
#line 566 "sintactico.y"
    { (yyval.SREPOR) = new STRREPORTE();}
#line 2410 "parser.cpp"
    break;

  case 118:
#line 568 "sintactico.y"
    {Ope->Ejecutar(toString((yyvsp[0].TEXT)));}
#line 2416 "parser.cpp"
    break;


#line 2420 "parser.cpp"

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
#line 570 "sintactico.y"

