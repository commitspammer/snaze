#ifndef RANDENGINE_H
#define RANDENGINE_H
#include <vector>
#include <random>

using namespace std;

class RandEngine {
private:
	/**@brief First integer for range of possible random integers. */
	int lowest;

	/**@brief Last integer for range of possible random integers. */
	int highest;

	/**@brief Dummy random device. */
	std::random_device rd;

	/**@brief Random number generator algorithm. */
	std::mt19937 mt;

	/**@brief Range of possible random integers as uniform distribution object. */
	std::uniform_int_distribution<int> dist;

public:

	/**@brief RandEngine constructor.
	 * @param lowest First integer for range of possible random integers.
	 * @param highest Last integer for range of possible random integers.
	 */
	RandEngine(int lowest, int highest);

	/**@brief Generates a random integer from engine's distribution.
	 * @return Random integer generated.
	 */
	int generate_int();

	/**@brief Generates a random permutation of all integers from engine's dist.
	 * @return Random permutation generated.
	 */
	vector<int> generate_permutation();
};

#endif

