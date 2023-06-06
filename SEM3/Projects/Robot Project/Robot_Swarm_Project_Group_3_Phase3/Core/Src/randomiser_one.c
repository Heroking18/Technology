#include <stdlib.h>
#include <time.h>
#include "randomiser_one.h"

// 0 = NOT INISIALISED 1 = INISIALISED
static rand_t init = 0;
static rand_t randomiser_limit = 1;

/**
 * @brief Generates a random number, either positive or negative
 *
 * @return urand_t A random number, Only POSITIVE, up to the limit set by INIT_RAND
 */
urand_t Get_Random_NoU(void)
{
    if (!init)
    {
        return U_RAND_FAILED;
    }

    rand_t randVal = rand();
    if (randVal < 0) // if the value is negative
    {
        return (-(randVal)) % randomiser_limit; // Gracefully convert the value to a positive on
    }
    return randVal % randomiser_limit; // Otherwise just return it as it is
}

/**
 * @brief Generates a random number, either positive or negative
 *
 * @return rand_t A random number up to the limit set by INIT_RAND
 */
rand_t Get_Random_NoS(void)
{
    if (!init)
    {
        ResetFlag();
        return S_RAND_FAILED; // report error
    }
    return rand() % randomiser_limit;
}

/**
 * @brief Set the Flag of the randomiser
 */
void SetFlag(void)
{
    init = 1;
}

/**
 * @brief Manualy reset the randomiser's set falg
 */
void ResetFlag(void)
{
    init = 0;
}

/**
 * @brief Inisialise the randomiser
 *
 * @param seed_limit The uppper limit of the no. to generate
 */
void InitRandomiser(rand_t limit)
{
    srand((urand_t)time(NULL));
    randomiser_limit = limit;
}

/**
 * @brief Get the Init Flag varaible
 *
 * @return urand_t The current valiue of the Randomiser Initialisation flag
 */
urand_t GetInitFlag(void)
{
    return init;
}
