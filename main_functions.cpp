#include "main_functions.hpp"

int generate_rand_int(int dec, int limit) {
    std::random_device rd;
    std::mt19937::result_type seed = rd() ^ (
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
                ).count() +
            (std::mt19937::result_type)
            std::chrono::duration_cast<std::chrono::microseconds>(
                std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count() );

    std::mt19937 gen(seed);
    std::uniform_int_distribution<unsigned> distrib(1, 6);

    int result = 0;
    for (int i = 0; i <= dec; ++i) {            // Decimal 
        while (1) {
            result += static_cast<int>(distrib(gen))*pow(10,i);
            if (result <= limit) {
                break;
            }
            result = 0;
        }
    }

    return result;
}
