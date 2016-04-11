#ifndef NUMERIC_KISS99_RNG
#define NUMERIC_KISS99_RNG 1

/* system headers */
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

/* local headers */
#include "util/util.h"

/* structs, enums */
#define KISS99_RNG_RANDOM_MAX UINT32_MAX

typedef struct {
	/* seed values */
	uint32_t z/*=362436069*/;
	uint32_t w/*=521288629*/;
	uint32_t jsr/*=123456789*/;
	uint32_t jcong/*=380116160*/;
	uint32_t a/*=224466889*/;
	uint32_t b/*=7584631*/;
	/* state table */
	uint32_t t[256];

	/* non-seed state: init to 0 */
	uint32_t x/*=0*/;
	uint32_t y/*=0*/;

	/* temporary storage */
	uint32_t bro;

	/* counter: init to zero */
	unsigned char c/*=0*/;
} kiss99_rng_state;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Macros */
#define kiss99_rng_znew(state) (state->z=36969*(state->z&65535)+(state->z>>16))
#define kiss99_rng_wnew(state) (state->w=18000*(state->w&65535)+(state->w>>16))
#define kiss99_rng_MWC(state) ((kiss99_rng_znew(state)<<16)+kiss99_rng_wnew(state) )
#define kiss99_rng_SHR3(state) (state->jsr^=(state->jsr<<17), state->jsr^=(state->jsr>>13), state->jsr^=(state->jsr<<5))
#define kiss99_rng_CONG(state) (state->jcong=69069*state->jcong+1234567)
#define kiss99_rng_FIB(state) ((state->b=state->a+state->b),(state->a=state->b-state->a))
#define kiss99_rng_KISS(state) ((kiss99_rng_MWC(state)^kiss99_rng_CONG(state))+kiss99_rng_SHR3(state))
#define kiss99_rng_LFIB4(state) (state->c++,state->t[state->c]=state->t[state->c]+state->t[kiss99_rng_UC(state->c+58)]+state->t[kiss99_rng_UC(state->c+119)]+state->t[kiss99_rng_UC(state->c+178)])
#define kiss99_rng_SWB(state) (state->c++,state->bro=(state->x<state->y),state->t[state->c]=(state->x=state->t[kiss99_rng_UC(state->c+34)])-(state->y=state->t[kiss99_rng_UC(state->c+19)]+state->bro))
#define kiss99_rng_UNI(state) (kiss99_rng_KISS(state)*2.328306e-10)
#define kiss99_rng_VNI(state) ((int32_t) kiss99_rng_KISS(state))*4.656613e-10
#define kiss99_rng_UC (unsigned char) /*a cast operation*/

/* Function prototypes */
extern void kiss99_rng_set_table(kiss99_rng_state* state, uint32_t i1,uint32_t i2,uint32_t i3,uint32_t i4,uint32_t i5,uint32_t i6);
extern kiss99_rng_state* kiss99_rng_state_new();


#ifdef __cplusplus
};
#endif /* __cplusplus */

#endif /* NUMERIC_KISS99_RNG */
