#include "Random.h"

namespace Walnut {

	thread_local std::mt19937 Random::s_RandomEngine;
	thread_local std::uniform_int_distribution<std::mt19937::result_type> Random::s_Distribution;

}
