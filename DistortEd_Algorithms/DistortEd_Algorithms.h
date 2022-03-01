//
// Created by edgallyot on 01/03/2022.
//

#ifndef WAVE_IO_DISTORTED_ALGORITHMS_H
#define WAVE_IO_DISTORTED_ALGORITHMS_H

#include <iostream>
#include <cmath>

void sayHello();

namespace DistortEdAlgorithms {
    template<typename T>
    T scaleInDb (T in, float dbChange){
        auto scale = pow(10.0f, static_cast<double>(dbChange / 20.0f));
        return static_cast<T>(scale * in);
    }

    template<typename T>
    T processHardClip (T in, float threshold)
    {
        T out;
        auto lo_threshold = static_cast<T>(0 - threshold);
        if (in > threshold)
        {
            out = threshold;
        } else if (in <= lo_threshold)
        {
            out = lo_threshold;
        } else
        {
            out = in;
        }
        return out;
    }

    template <typename T>
    T processCubicClip(T in, float alpha){
        auto coefficient = alpha * static_cast<double>(1.0f / 3.0f);
        T out = static_cast<T>(in - (coefficient * pow (static_cast<double>(in), 3.0f)));
        return out;
    }
}

#endif //WAVE_IO_DISTORTED_ALGORITHMS_H
