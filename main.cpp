#include "Wave.h"
#include "DistortEd_Algorithms.h"

int main() {
    Wave<float> wave;

    try {
        wave.readFile("Jazz_Sax.wav");
        wave.printFileName();
        wave.printInfo();

        // Testing different processing algorithms

        wave.processData (&DistortEdAlgorithms::scaleInDb<float>, 10);

        wave.processData (&DistortEdAlgorithms::processHardClip<float>, 0.1);

        for(auto i = 0; i < 100; ++i){
            wave.processData (&DistortEdAlgorithms::processCubicClip<float>, 1);
        }


        wave.writeFile("test.wav");
    } catch (std::exception &e) {
        std::cout << "Exception Caught: " << e.what() << std::endl;
    }
    return 0;
}