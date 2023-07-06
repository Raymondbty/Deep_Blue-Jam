#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265358979323846

int DisplayHelp() {
    printf("USAGE\n"
           "    ./205IQ u s [IQ1] [IQ2]\n\n"
           "DESCRIPTION\n"
           "  u\tmean\n"
           "  s\tstandard deviation\n"
           "  IQ1\tminimum IQ\n"
           "  IQ2\tmaximum IQ\n");
    return 0;
}

typedef struct BigBrain {
    double b;
    double a;
    double FirstValue;
    double ScValue;
} BigBrain;

void DisplayPercentage(int z, double distrub) {
    printf("%d %.5f\n", z, distrub);
}

double CalcNum(double mean, double stanDev, double z) {
    const double inv_sqrt_2pi = 1.0 / (stanDev * sqrt(2.0 * PI));
    const double exponent = -0.5 * pow((z - mean) / stanDev, 2);
    const double density = inv_sqrt_2pi * exp(exponent);
    return density;
}

void PrintSmall(double iq_rate, double FirstValue) {
    printf("%.1f%% of people have an IQ inferior to %.0f\n", iq_rate * 100.0, FirstValue);
}

void BadIq(BigBrain *bb) {
    double iq_rate = 0;
    const double step = 0.01;

    for (double z = 0; z <= bb->FirstValue; z += step) {
        double density = CalcNum(bb->b, bb->a, z);
        iq_rate += density * step;
    }
    PrintSmall(iq_rate, bb->FirstValue);
}

void PrintRange(double iq_rate, double FirstValue, double ScValue) {
    printf("%.1f%% of people have an IQ between %.0f and %.0f\n", iq_rate, FirstValue, ScValue);
}

void CalculRange(BigBrain *bb) {
    double iq_rate = 0;

    for (int i = ceil(bb->FirstValue * 100); i < floor(bb->ScValue * 100); ++i)
        iq_rate += CalcNum(bb->b, bb->a, i / 100.0);
    PrintRange(iq_rate, bb->FirstValue, bb->ScValue);
}

int launch_iq(int argc, const char **argv) {
    int result = 0;
    if (argc < 3 || argc > 5) {
        fprintf(stderr, "Error: Invalid number of command-line arguments\n");
        return 1;
    }
    bool make_calcul = (argc == 4);
    BigBrain bb;
    bb.FirstValue = 0;
    bb.ScValue = 0;
    bb.b = atof(argv[1]);
    bb.a = atof(argv[2]);
    if (argc == 4)
        bb.FirstValue = atof(argv[3]);
    else if (argc == 5) {
        bb.FirstValue = atof(argv[3]);
        bb.ScValue = atof(argv[4]);
    }
    if (make_calcul) {
        BadIq(&bb);
    } else {
        CalculRange(&bb);
    }
    return result;
}

bool ParseDouble(const char *str, double *value) {
    char *endptr;
    *value = strtod(str, &endptr);
    return (*endptr == '\0');
}

int main(const int argc, const char **argv) {
    if (argc == 1) {
        fprintf(stderr, "Error: No arguments provided\n");
        return 84;
    } else if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        return DisplayHelp();
    } else if (argc < 4 || argc > 5) {
        fprintf(stderr, "Error: Invalid number of command-line arguments\n");
        return 84;
    }

    double mu, sigma, IQ1, IQ2;
    int arg_index = 1;
    if (!ParseDouble(argv[arg_index++], &mu) || mu < 0) {
        fprintf(stderr, "Error: Invalid value for mu\n");
        return 84;
    }
    if (!ParseDouble(argv[arg_index++], &sigma) || sigma < 0) {
        fprintf(stderr, "Error: Invalid value for sigma\n");
        return 84;
    }
    if (!ParseDouble(argv[arg_index++], &IQ1) || IQ1 < 0 || IQ1 > 200) {
        fprintf(stderr, "Error: Invalid value for IQ1\n");
        return 84;
    }
    if (argc == 5) {
        if (!ParseDouble(argv[arg_index++], &IQ2) || IQ2 < 0 || IQ2 > 200) {
            fprintf(stderr, "Error: Invalid value for IQ2\n");
            return 84;
        }
        if (IQ2 < IQ1) {
            fprintf(stderr, "Error: IQ2 cannot be smaller than IQ1\n");
            return 84;
        }
    }

    if (arg_index < argc) {
        fprintf(stderr, "Error: Too many command-line arguments\n");
        return 84;
    } else if (arg_index > argc) {
        fprintf(stderr, "Error: Not enough command-line arguments\n");
        return 84;
    }
    return launch_iq(argc, argv);
}
