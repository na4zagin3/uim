/*===========================================================================
 *  FileName : sigschemeinternal.h
 *  About    : variable and function definitions for internal use
 *
 *  Copyright (C) 2005      by Kazuki Ohta (mover@hct.zaq.ne.jp)
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of authors nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 *  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
===========================================================================*/
#ifndef __SIGSCHEMEINTERNAL_H
#define __SIGSCHEMEINTERNAL_H

/*=======================================
   System Include
=======================================*/
#include <stdarg.h>

/*=======================================
   Local Include
=======================================*/
#include "sigscheme.h"
#include "sigschemefunctable.h"

/*=======================================
   Type Definitions
=======================================*/
typedef struct ScmSpecialCharInfo_ ScmSpecialCharInfo;
struct ScmSpecialCharInfo_ {
    int code;             /* character code as ASCII/Unicode */
    const char *esc_seq;  /* escape sequence as string */
    const char *lex_rep;  /* lexical representation as character object */
};

/*=======================================
   Variable Declarations
=======================================*/
/* sigscheme.c */
extern ScmObj Scm_sym_else, Scm_sym_yields;

/* io.c */
extern ScmObj scm_current_input_port;
extern ScmObj scm_current_output_port;
extern ScmObj scm_current_error_port;

/* debug.c */
extern void (*Scm_writess_func)(ScmObj port, ScmObj obj);

/* read.c */
extern const ScmSpecialCharInfo Scm_special_char_table[];

/* storage.c */
#if SCM_USE_VALUECONS
extern ScmObj SigScm_null_values;
#endif

/*=======================================
   Macro Declarations
=======================================*/
#ifndef FALSE
#define FALSE 0
#endif /* FALSE */
#ifndef TRUE
#define TRUE  (!FALSE)
#endif /* TRUE */

/* trace stack for debugging */
#define MAKE_TRACE_FRAME(obj, env) (CONS(obj, env))
#define TRACE_FRAME_OBJ CAR
#define TRACE_FRAME_ENV CDR

/* FreeCell Handling Macros */
#if SCM_OBJ_COMPACT
#define SCM_FREECELLP(a)            (SCM_CONSP(a))
#define SCM_AS_FREECELL(a)          (SCM_ASSERT_TYPE(SCM_CONSP(a), (a)))
#define SCM_FREECELL_CAR(a)         (SCM_CAR(a))
#define SCM_FREECELL_CDR(a)         (SCM_CDR(a))
#define SCM_ENTYPE_FREECELL(a)      (SCM_ENTYPE_CONS(a))
#define SCM_FREECELL_SET_CAR(a, car) (SCM_CONS_SET_CAR((a), (car)))
#define SCM_FREECELL_SET_CDR(a, cdr) (SCM_CONS_SET_CDR((a), (cdr)))
#else
#define SCM_FREECELLP(a)            (SCM_TYPE(a) == ScmFreeCell)
#define SCM_AS_FREECELL(a)          (SCM_ASSERT_TYPE(SCM_FREECELLP(a), (a)))
#define SCM_FREECELL_CAR(a)         (SCM_AS_FREECELL(a)->obj.cons.car)
#define SCM_FREECELL_CDR(a)         (SCM_AS_FREECELL(a)->obj.cons.cdr)
#define SCM_ENTYPE_FREECELL(a)      (SCM_ENTYPE((a), ScmFreeCell))
#define SCM_FREECELL_SET_CAR(a, car) (SCM_FREECELL_CAR(a) = (car))
#define SCM_FREECELL_SET_CDR(a, cdr) (SCM_FREECELL_CDR(a) = (cdr))
#endif

/* Prefix-less Abbreviation Names For Convenient Internal Use */
#define SYM_QUOTE            SCM_SYM_QUOTE
#define SYM_QUASIQUOTE       SCM_SYM_QUASIQUOTE
#define SYM_UNQUOTE          SCM_SYM_UNQUOTE
#define SYM_UNQUOTE_SPLICING SCM_SYM_UNQUOTE_SPLICING
#define SYM_ELSE             Scm_sym_else
#define SYM_YIELDS           Scm_sym_yields

#define EQ             SCM_EQ
#define NULLP          SCM_NULLP
#define FALSEP         SCM_FALSEP
#define NFALSEP        SCM_NFALSEP
#define EOFP           SCM_EOFP

#define CAR            SCM_CAR
#define CDR            SCM_CDR
#define SET_CAR        SCM_CONS_SET_CAR
#define SET_CDR        SCM_CONS_SET_CDR
#define CAAR           SCM_CAAR
#define CADR           SCM_CADR
#define CDAR           SCM_CDAR
#define CDDR           SCM_CDDR

#define CONS           SCM_CONS
#define LIST_1         SCM_LIST_1
#define LIST_2         SCM_LIST_2
#define LIST_3         SCM_LIST_3
#define LIST_4         SCM_LIST_4
#define LIST_5         SCM_LIST_5

#define DEREF          SCM_DEREF
#define SET            SCM_SET
#define REF_CAR        SCM_REF_CAR
#define REF_CDR        SCM_REF_CDR
#define REF_OFF_HEAP   SCM_REF_OFF_HEAP

#define EVAL           SCM_EVAL

#define INTP           SCM_INTP
#define CONSP          SCM_CONSP
#define SYMBOLP        SCM_SYMBOLP
#define CHARP          SCM_CHARP
#define STRINGP        SCM_STRINGP
#define FUNCP          SCM_FUNCP
#define SYNTAXP        SCM_SYNTAXP
#define CLOSUREP       SCM_CLOSUREP
#define PROCEDUREP     SCM_PROCEDUREP
#define VECTORP        SCM_VECTORP
#define PORTP          SCM_PORTP
#define CONTINUATIONP  SCM_CONTINUATIONP
#if SCM_USE_VALUECONS
#define NULLVALUESP    SCM_NULLVALUESP
#endif /* SCM_USE_VALUECONS */
#define VALUEPACKETP   SCM_VALUEPACKETP
#define FREECELLP      SCM_FREECELLP
#define C_POINTERP     SCM_C_POINTERP
#define C_FUNCPOINTERP SCM_C_FUNCPOINTERP
#define ENVP           SCM_ENVP
#define ERROBJP        SCM_ERROBJP

#define LISTP          SCM_LISTP
#define LIST_1_P       SCM_LIST_1_P
#define LIST_2_P       SCM_LIST_2_P
#define LIST_3_P       SCM_LIST_3_P
#define LIST_4_P       SCM_LIST_4_P
#define LIST_5_P       SCM_LIST_5_P

#define CDBG           SCM_CDBG
#define DBG            SCM_DBG

/*
 * Abbrev name for these constants are not provided since it involves some
 * consistency problems and confusions. Use the canonical names always.
 *
 * SCM_NULL
 * SCM_TRUE
 * SCM_FALSE
 * SCM_EOF
 * SCM_UNBOUND
 * SCM_UNDEF
 */

/* Obscures identifier ID. */
#define SCM_MANGLE(id) Scm_internal_##id

#define VALIDP(obj)   (!EQ((obj), SCM_INVALID))
#define INVALIDP(obj) (EQ((obj), SCM_INVALID))

/* Declares the current function name as seen by Scheme codes.  TYPE
 * is ignored, but we may use it in the future to implement a stub
 * generator.  This macro can be invoked only at the beginning of a
 * function body, right after local variable declarations. */
#define DECLARE_FUNCTION(func_name, type) \
    const char *SCM_MANGLE(name); \
    ScmObj SCM_MANGLE(tmp); \
    SCM_MANGLE(name) = func_name; \
    SCM_MANGLE(tmp)  = SCM_INVALID /* No semicolon here. */

/* DECLARE_FUNCTION without the functype.
 * FIXME: is there a better name? */
#define DECLARE_INTERNAL_FUNCTION(name) DECLARE_FUNCTION((name), ignored)

/* Signals an error.  The current function name and the message are
   sent to the error port.  The message is formatted by vfprintf(). */
#define ERR SigScm_Error

/* Signals an error that occured on an object.  The current function
 * name, the message, then the object, are written (with `write') to
 * the error port. */
#define ERR_OBJ(msg, obj) Scm_ErrorObj(SCM_MANGLE(name), (msg), (obj))

/* ASSERT_NO_MORE_ARG() asserts that the variadic argument list has
 * been exhausted.  The assertion is implicit in NO_MORE_ARG(), so
 * usually you don't have to call it explicitly.
 * ASSERT_PROPER_ARG_LIST() should be used when scanning is ended
 * prematurely, e.g. if an argument to "and" evaluates to #f.  Both
 * macros expand to no-ops #if !SCM_STRICT_ARGCHECK.
 */
#if SCM_STRICT_ARGCHECK
#define NO_MORE_ARG(args) \
    (!CONSP(args) \
     && (NULLP(args) \
         || (ERR_OBJ("improper argument list terminator", (args)), 1)))
#define ASSERT_NO_MORE_ARG(args) \
    (NO_MORE_ARG(args) || (ERR_OBJ("superfluous argument(s)", (args)), 1))
#define ASSERT_PROPER_ARG_LIST(args) \
    (ScmOp_c_length(args) >= 0 \
     || (ERR_OBJ("bad argument list", (args)), 1))
#else  /* not SCM_STRICT_ARGCHECK */
#define NO_MORE_ARG(args) (!CONSP(args))
#define ASSERT_NO_MORE_ARG(args)
#define ASSERT_PROPER_ARG_LIST(args)
#endif /* not SCM_STRICT_ARGCHECK */

/* Destructively retreives the first element of an argument list.  If
 * ARGS doesn't contain enough arguments, return SCM_INVALID. */
#define POP_ARG(args) \
     (CONSP(args) \
      ? (SCM_MANGLE(tmp) = CAR(args), (args) = CDR(args), SCM_MANGLE(tmp)) \
      : SCM_INVALID)

/* Like POP_ARG(), but signals an error if no argument is
   available. */
#define MUST_POP_ARG(args) \
     (CONSP(args) \
      ? (SCM_MANGLE(tmp) = CAR(args), (args) = CDR(args), SCM_MANGLE(tmp)) \
      : (ERR("missing argument(s)"), NULL))

#define ASSERT_TYPE(pred, typename, obj) \
    (pred(obj) || (ERR_OBJ(typename " required but got", (obj)), 1))

#define ASSERT_INTP(obj)     ASSERT_TYPE(INTP, "integer", (obj))
#define ASSERT_CONSP(obj)    ASSERT_TYPE(CONSP, "pair", (obj))
#define ASSERT_SYMBOLP(obj)  ASSERT_TYPE(SYMBOLP, "symbol", (obj))
#define ASSERT_CHARP(obj)    ASSERT_TYPE(CHARP, "character", (obj))
#define ASSERT_STRINGP(obj)  ASSERT_TYPE(STRINGP, "string", (obj))
#define ASSERT_FUNCP(obj)    ASSERT_TYPE(FUNCP, "function", (obj))
#define ASSERT_CLOSUREP(obj) ASSERT_TYPE(CLOSUREP, "closure", (obj))
#define ASSERT_VECTORP(obj)  ASSERT_TYPE(VECTORP, "vector", (obj))
#define ASSERT_PORTP(obj)    ASSERT_TYPE(PORTP, "port", (obj))
#define ASSERT_CONTINUATIONP(obj) ASSERT_TYPE(CONTINUATIONP, "continuation", (obj))
#define ASSERT_PROCEDUREP(obj) ASSERT_TYPE(PROCEDUREP, "procedure", (obj))
#define ASSERT_ENVP(obj)     ASSERT_TYPE(ENVP, "environment specifier", (obj))
#define ASSERT_ERROBJP(obj)  ASSERT_TYPE(ERROBJP, "error object", (obj))
#define ASSERT_LISTP(obj)    ASSERT_TYPE(LISTP, "list", (obj))

/* Macros For Handling Continuation Object */
#define INVALID_CONTINUATION_OPAQUE  NULL

/* Symbol Name Hash Size */
#define NAMEHASH_SIZE 1024

#define SCM_ERR_HEADER "Error: "

/*=======================================
   String Mutation Assertion
=======================================*/
#define ASSERT_MUTABLEP(str)                                            \
    do {                                                                \
        if (SCM_STRING_MUTATION_TYPE(str) == SCM_STR_IMMUTABLE)         \
            ERR_OBJ("attempted to modify immutable string", str);       \
    } while (/* CONSTCOND */ 0)

/*=======================================
   List Constructor
=======================================*/
typedef ScmRef ScmQueue;
#define SCM_QUEUE_INVALIDATE(_q) ((_q) = NULL)
#define SCM_QUEUE_VALIDP(_q)     (_q)
#define SCM_QUEUE_POINT_TO(_q, _out) ((_q) = SCM_REF_OFF_HEAP(_out))
#define SCM_QUEUE_ADD(_q, _dat) (SET((_q), LIST_1(_dat)),       \
                                 (_q) = REF_CDR(DEREF(_q)))
#define SCM_QUEUE_APPEND(_q, _lst)              \
    do {                                        \
        SET((_q), (_lst));                      \
        while (CONSP(DEREF(_q)))                \
            (_q) = REF_CDR(DEREF(_q));          \
    } while (/* CONSTCOND */ 0)
#define SCM_QUEUE_TERMINATOR(_q)          (DEREF(_q))
#define SCM_QUEUE_SLOPPY_APPEND(_q, _lst) (SET((_q), (_lst)))

/*=======================================
   Local Buffer Allocator
=======================================*/
/* don't touch inside directly */
#define ScmLBuf(T)                                                           \
    struct ScmLBuf_##T##_ {                                                  \
        T *_buf;                                                             \
        size_t _size;                                                        \
        T *_init_buf;                                                        \
        size_t _init_size;                                                   \
        int _extended_cnt;                                                   \
    }

/* lvalue access is permitted */
#define LBUF_BUF(lbuf)       ((lbuf)._buf)

/* lvalue access is not permitted */
#define LBUF_END(lbuf)       (&LBUF_BUF(lbuf)[LBUF_SIZE(lbuf)])
#define LBUF_SIZE(lbuf)      ((lbuf)._size)
#define LBUF_INIT_SIZE(lbuf) ((lbuf)._init_size)
#define LBUF_EXT_CNT(lbuf)   ((lbuf)._extended_cnt)

#define LBUF_INIT(lbuf, init_buf, init_size)                                 \
    do {                                                                     \
        (lbuf)._buf  = (lbuf)._init_buf  = init_buf;                         \
        (lbuf)._size = (lbuf)._init_size = init_size;                        \
        (lbuf)._extended_cnt = 0;                                            \
    } while (/* CONSTCOND */ 0)

#define LBUF_FREE(lbuf)                                                      \
    do {                                                                     \
        if ((lbuf)._buf != (lbuf)._init_buf)                                 \
            free((lbuf)._buf);                                               \
    } while (/* CONSTCOND */ 0)

#define LBUF_ALLOC(lbuf, size)                                               \
    do {                                                                     \
        (lbuf)._buf = Scm_malloc(size);                                      \
        (lbuf)._size = (size);                                               \
    } while (/* CONSTCOND */ 0)

#define LBUF_REALLOC(lbuf, size)                                             \
    do {                                                                     \
        if ((lbuf)._buf == (lbuf)._init_buf) {                               \
            (lbuf)._buf = memcpy(Scm_malloc(size), LBUF_BUF(lbuf), LBUF_SIZE(lbuf)); \
        } else {                                                             \
            (lbuf)._buf = Scm_realloc((lbuf)._buf, (size));                  \
        }                                                                    \
        (lbuf)._size = (size);                                               \
    } while (/* CONSTCOND */ 0)

#define LBUF_EXTEND(lbuf, f, min_size)                                       \
    do {                                                                     \
        size_t new_size;                                                     \
                                                                             \
        if (LBUF_SIZE(lbuf) < (min_size)) {                                  \
            new_size = f(lbuf);                                              \
            if (new_size < LBUF_SIZE(lbuf))                                  \
                ERR("local buffer exceeded");                                \
            if (new_size < (size_t)min_size)                                 \
                new_size = (size_t)min_size;                                 \
            LBUF_REALLOC((lbuf), new_size);                                  \
            (lbuf)._extended_cnt++;                                          \
        }                                                                    \
    } while (/* CONSTCOND */ 0)

/*
 * extended size functions:
 * define your own version if more optimized version is needed
 */
#define LBUF_F_LINEAR(lbuf)      (LBUF_SIZE(lbuf) + LBUF_INIT_SIZE(lbuf))
#define LBUF_F_EXPONENTIAL(lbuf) (LBUF_SIZE(lbuf) << 1)

/*=======================================
   Function Declarations
=======================================*/
/* storage.c */
void SigScm_InitStorage(size_t heap_size, size_t heap_alloc_threshold,
                        int n_heaps_max, int n_heaps_init);
void SigScm_FinalizeStorage(void);

/* storage-gc.c */
void   SigScm_InitGC(size_t heap_size, size_t heap_alloc_threshold,
                     int n_heaps_max, int n_heaps_init);
void   SigScm_FinalizeGC(void);
ScmObj SigScm_NewObjFromHeap(void);

/* storage-continuation.c */
void   SigScm_InitContinuation(void);
void   SigScm_FinalizeContinuation(void);
void   Scm_DestructContinuation(ScmObj cont);
ScmObj Scm_CallWithCurrentContinuation(ScmObj proc, ScmEvalState *eval_state);
void   Scm_CallContinuation(ScmObj cont, ScmObj ret);
ScmObj Scm_DynamicWind(ScmObj before, ScmObj thunk, ScmObj after);
void Scm_PushTraceFrame(ScmObj obj, ScmObj env);
void Scm_PopTraceFrame(void);
ScmObj Scm_TraceStack(void);

/* storage-symbol.c */
void   SigScm_InitSymbol(void);
void   SigScm_FinalizeSymbol(void);

/* eval.c */
/* environment related functions */
ScmObj Scm_ExtendEnvironment(ScmObj vars, ScmObj vals, ScmObj env);
ScmObj Scm_AddEnvironment(ScmObj var, ScmObj val, ScmObj env);
ScmRef Scm_LookupEnvironment(ScmObj var, ScmObj env);
ScmObj Scm_SymbolValue(ScmObj var, ScmObj env);

ScmObj Scm_eval(ScmObj obj, ScmObj env);
ScmObj Scm_tailcall(ScmObj proc, ScmObj args, ScmEvalState *eval_state);

ScmObj ScmExp_cond_internal(ScmObj args, ScmObj case_key, ScmEvalState *eval_state);

/* error.c */
void SigScm_InitError(void);
void *Scm_malloc(size_t size);
void *Scm_calloc(size_t number, size_t size);
void *Scm_realloc(void *ptr, size_t size);
void Scm_ThrowException(ScmObj errorobj) SCM_NORETURN;
void SigScm_ShowErrorHeader(void);
void Scm_ErrorObj(const char *func_name, const char *msg, ScmObj obj) SCM_NORETURN;

/* operations.c */
int ScmOp_c_length(ScmObj lst);

/* io.c */
void Scm_InitIO(void);
ScmCharPort *Scm_NewCharPort(ScmBytePort *bport);

/* sigscheme.c */
char **Scm_InterpretArgv(char **argv);
void Scm_FreeArgv(char **argv);

#endif /* __SIGSCHEMEINTERNAL_H */
