#include "Wave.h"
#include "DistortEd_Algorithms.h"

int main ()
{
    Wave<float> wave;

    try
    {
        wave.readFile ("Jazz_Sax.wav");
        wave.printFileName ();
        wave.printInfo ();

        // Testing different processing algorithms

//        wave.processData (&DistortEdAlgorithms::scaleInDb<float>, 0.0f);
//
//        wave.processData (&DistortEdAlgorithms::processHardClip<float>, 0.1);
//
//        for(auto i = 0; i < 100; ++i){
//            wave.processData (&DistortEdAlgorithms::processCubicClip<float>, 1);
//        }
//
//        wave.processData (&DistortEdAlgorithms::processHalfWaveRect<float>);
//        wave.processData (&DistortEdAlgorithms::processFullWaveRect<float>);
//        wave.processData (&DistortEdAlgorithms::processInfiniteClip<float>);
//        wave.processData (&DistortEdAlgorithms::processExponentialClip<float>, 11.0f);
//        wave.processData (&DistortEdAlgorithms::processArcTanClip<float>, 6.0f);
//        wave.processData (&DistortEdAlgorithms::processBitClip<float>, 2.0f);
//        wave.processData (&DistortEdAlgorithms::processSineClip<float>);
//        for (int i = 0; i < 20; ++i)
//        {
//            wave.processData (&DistortEdAlgorithms::processPieceWiseClip<float>);
//            wave.processData (&DistortEdAlgorithms::scaleInDb<float>, -5.0f);
//            wave.processData (&DistortEdAlgorithms::processCubicClip<float>, 1);
//        }
//
//        wave.processData (&DistortEdAlgorithms::processHardClip<float>, 0.8);
//
//        wave.processData (&DistortEdAlgorithms::dcOffsetClip<float>, -0.9);
//
//        wave.processData (&DistortEdAlgorithms::diodeClip<float>);

        wave.writeFile ("test.wav");
    } catch (std::exception& e)
    {
        std::cout << "Exception Caught: " << e.what () << std::endl;
    }
    return 0;
}