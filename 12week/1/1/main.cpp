#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "visualizer.hpp"

int main(int argc, char ** argv)
{
    try 
	{
        const std::complex <float> c = { 0.285,  0.01 };
        Visualizer visualizer(c);

		visualizer.run();
    }
    catch (const std::exception & exception) 
	{
        std::cerr << exception.what() << '\n';
        return EXIT_FAILURE;
    }
	catch (...)
	{
		std::cerr << "Unknown exception\n";




		return EXIT_FAILURE;
	}

	system("pause");

    return EXIT_SUCCESS;
}
