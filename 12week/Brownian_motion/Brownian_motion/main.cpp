#include "visualizer.hpp"




int main()
{
    try {
        Visualizer Brownian_Motion;

        Brownian_Motion.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error\n";
    }


    return 0;
}
