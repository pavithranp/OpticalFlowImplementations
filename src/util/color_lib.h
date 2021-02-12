// Copyright [2020] <Pavithran Pandiyan>
#include <math.h>

void vector_to_RGB(float x, float y, int& R, int& G, int& B)
{

    // HSV to RGB conversion
    // hope there is a easier way to do this
    float Pi, amp, phi, alpha, beta;
    /* set pi */
    Pi = 2.0 * acos(0.0);

    amp = sqrt(x * x + y * y);

    if (amp > 1) amp = 1;
    if (x == 0.0)
        if (y >= 0.0) phi = 0.5 * Pi;
        else phi = 1.5 * Pi;
    else if (x > 0.0)
        if (y >= 0.0) phi = atan(y / x);
        else phi = 2.0 * Pi + atan(y / x);
    else phi = Pi + atan(y / x);

    phi = phi / 2.0;
    R = 0;
    G = 0;
    B = 0;
    // interpolation between red (0) and blue (0.25 * Pi)
    if ((phi >= 0.0) && (phi < 0.125 * Pi)) {
        beta = phi / (0.125 * Pi);
        alpha = 1.0 - beta;
        R = (int)floor(amp * (alpha * 255.0 + beta * 255.0));
        G = (int)floor(amp * (alpha * 0.0 + beta * 0.0));
        B = (int)floor(amp * (alpha * 0.0 + beta * 255.0));
    }
    if ((phi >= 0.125 * Pi) && (phi < 0.25 * Pi)) {
        beta = (phi - 0.125 * Pi) / (0.125 * Pi);
        alpha = 1.0 - beta;
        R = (int)floor(amp * (alpha * 255.0 + beta * 64.0));
        G = (int)floor(amp * (alpha * 0.0 + beta * 64.0));
        B = (int)floor(amp * (alpha * 255.0 + beta * 255.0));
    }
    // interpolation between blue (0.25 * Pi) and green (0.5 * Pi)
    if ((phi >= 0.25 * Pi) && (phi < 0.375 * Pi)) {
        beta = (phi - 0.25 * Pi) / (0.125 * Pi);
        alpha = 1.0 - beta;
        R = (int)floor(amp * (alpha * 64.0 + beta * 0.0));
        G = (int)floor(amp * (alpha * 64.0 + beta * 255.0));
        B = (int)floor(amp * (alpha * 255.0 + beta * 255.0));
    }
    if ((phi >= 0.375 * Pi) && (phi < 0.5 * Pi)) {
        beta = (phi - 0.375 * Pi) / (0.125 * Pi);
        alpha = 1.0 - beta;
        R = (int)floor(amp * (alpha * 0.0 + beta * 0.0));
        G = (int)floor(amp * (alpha * 255.0 + beta * 255.0));
        B = (int)floor(amp * (alpha * 255.0 + beta * 0.0));
    }
    // interpolation between green (0.5 * Pi) and yellow (0.75 * Pi)
    if ((phi >= 0.5 * Pi) && (phi < 0.75 * Pi)) {
        beta = (phi - 0.5 * Pi) / (0.25 * Pi);
        alpha = 1.0 - beta;
        R = (int)floor(amp * (alpha * 0.0 + beta * 255.0));
        G = (int)floor(amp * (alpha * 255.0 + beta * 255.0));
        B = (int)floor(amp * (alpha * 0.0 + beta * 0.0));
    }
    // interpolation between yellow (0.75 * Pi) and red (Pi)
    if ((phi >= 0.75 * Pi) && (phi <= Pi)) {
        beta = (phi - 0.75 * Pi) / (0.25 * Pi);
        alpha = 1.0 - beta;
        R = (int)floor(amp * (alpha * 255.0 + beta * 255.0));
        G = (int)floor(amp * (alpha * 255.0 + beta * 0.0));
        B = (int)floor(amp * (alpha * 0.0 + beta * 0.0));
    }
    std::cout << x << " " << y << " " << R << " " << G << " " << B << " angle:" << phi << std::endl;
    /* check RGB range */
}
