
// Author: Victor Covalciuc @2022

#ifndef __RANDOMISER_ONE_H__
#define __RANDOMISER_ONE_H__

// ---> RENAMING of DATA TYPES <--- // // §- Declarations -§ //
/*----------------------------------------------------------*/
// Apple implementation then microsoft implementation
#if defined(_STDLIB_H_) // Appple Specific Declaration
typedef __int32_t rand_t;
typedef __uint32_t urand_t;
#elif defined(__CLANG_STDINT_H) || defined(_STDINT)
typedef int32_t rand_t;
typedef uint32_t urand_t;
#else
typedef int rand_t;
typedef unsigned int urand_t;
#endif
/*----------------------------------------------------------*/

// ---> FUNCTIONS & CONSTANT FUNCTIONS <--- // // §- Declarations -§ //
/*------------------------------------------------------------------*/

// --> FUNCTIONS <-- //
urand_t Get_Random_NoU(void); // U - Unsigned
rand_t Get_Random_NoS(void);  // S - Signed
urand_t GetInitFlag(void);
void SetFlag(void);
void ResetFlag(void);
void InitRandomiser(rand_t);

// --> CONSTANT FUNCTIONS <-- //
#define INIT_RAND(UPPEER_SEED_LIMIT)   \
    InitRandomiser(UPPEER_SEED_LIMIT); \
    SetFlag();
/*------------------------------------------------------------------*/

// ---> PREPROCESSOR DIRECTIVES <--- // // §- Declarations -§ //
/*------------------------------------------------------------------*/
#define MANUAL_RESET_INIT_FALG_RAND ResetFlag();
#define U_RAND_FAILED 302 // OBLIGATORY DOUBLE CHECK WITH INIT_FLAG
#define S_RAND_FAILED -1
#define FLAG_INIT 1
#define FLAG_NOT_INIT 0
/*------------------------------------------------------------------*/

#endif
