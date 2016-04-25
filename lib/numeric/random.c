#include "config/config.h"

#include "numeric/random.h"

#if OS_UNIX
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  #include <unistd.h>
#endif

float64 orion_rand_uniform_dist(orion_rand_state_t* state) {
	return ( (float64) kiss99_rng_KISS( state ) ) / KISS99_RNG_RANDOM_MAX;
}

uint32_t _orion_rand_seeds() {
	uint32_t r;

#if OS_UNIX
	/* read from /dev/urandom */
	int fn;
	char random_device[] = "/dev/urandom";
	fn = open(random_device, O_RDONLY);
	if (fn == - 1)
		/* Failed ! */
		die("Could not open %s for seeding RNG", random_device);
	if ( read(fn, &r, 4) != 4)
		/* Failed ! */
		die("Could not read %s for seeding RNG", random_device);
	close(fn);
#elif defined(_CRT_RAND_S)
	rand_s( &r );
#else
	die("%s", "Random seeding not implemented on this platform");
#endif

	return r;
}

/* Based on the report "Good Practice in (Pseudo)Random Number Generation for
 * Bioinformatics Applications" by David Jones.
 * <http://www0.cs.ucl.ac.uk/staff/d.jones/GoodPracticeRNG.pdf>
 */
/* Initialise KISS generator using /dev/urandom */
void kiss99_rng_init(kiss99_rng_state* state) {
	state->x = _orion_rand_seeds();
	while (!( state->y = _orion_rand_seeds())); /* y must not be zero !  */
	state->z = _orion_rand_seeds() ;
	/* We don’t really need to set c as well but
	   let's anyway
	   ... */
	/* NOTE: offset c by 1 to avoid z=c=0 */
	state->c = _orion_rand_seeds() % 698769068 + 1; /* Should be less than 698769069 */
}

