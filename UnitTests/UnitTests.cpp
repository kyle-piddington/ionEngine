
#define CATCH_CONFIG_RUNNER
#include <catch.hpp>


int main(int argc, char * const argv[])
{
	int result = Catch::Session().run(argc, argv);

#ifdef WIN32
	system("PAUSE");
#endif

	return result;
}