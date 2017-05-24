//! Initial Stress Generator
//!
//! The main code to generate points within a rectangle
//! Input:  output of mpm_point_generator

#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

//! \brief    Get initial stress
//! \details  Get input, generate initial stress, write output

int main() {
  try {
    //! Reading input file
    //! Error would be reported

    //! User input inputFilename and outputFilename
    std::string inputfilename;
    std::string outputfilename;

    std::cout << "Type the input file name, default: [bin/soilParticles.smf]: ";
    std::getline(std::cin, inputfilename);
    if (inputfilename == "") inputfilename = "bin/soilParticles.smf";

    std::cout
        << "Type the output file name, default: [bin/initStressSoilP.dat]: ";
    std::getline(std::cin, outputfilename);
    if (outputfilename == "") outputfilename = "bin/initStressSoilP.dat";

    //! Get two parameters
    double density(20.);
    double k0(0.5);

    //! Note that y direction is vertical
    //! Note that the stress is negative for pushing down in y direction

    //! Open input file and store y-dir
    std::ifstream inputFile;
    inputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    inputFile.open(inputfilename);

    unsigned total_num_points;
    std::vector<double> ycoord;
    double value;

    inputFile >> total_num_points;

    for (unsigned i = 0; i < total_num_points; ++i) {
      inputFile >> value;
      inputFile >> value;
      ycoord.push_back(value);
      inputFile >> value;
    }

    inputFile.close();
    std::cout << "The input file has been read."
              << "\n";

    //! Calculate stresses
    double max_height = *std::max_element(ycoord.begin(), ycoord.end());
    std::vector<unsigned> index;
    std::vector<double> ver_stress;
    std::vector<double> hor_stress;

    unsigned l = 0;
    for (double coord : ycoord) {
      ver_stress.emplace_back(-(max_height - coord) * density);
      hor_stress.emplace_back(-(max_height - coord) * density * k0);
      index.push_back(l);
      ++l;
    }

    //! Open output file and store all data
    std::ofstream outputFile(outputfilename);

    outputFile << total_num_points << "\n";
    for (unsigned i = 0; i < total_num_points; ++i) {
      outputFile << index.at(i) << "\t";
      outputFile << hor_stress.at(i) << "\t";
      outputFile << ver_stress.at(i) << "\t";
      outputFile << hor_stress.at(i) << "\t";
      outputFile << 0 << "\t";
      outputFile << 0 << "\t";
      outputFile << 0 << "\t";
      outputFile << "\n";
    }

    outputFile.close();
    std::cout << "The output file has been generated."
              << "\n";

  }

  catch (std::exception& except) {
    std::cout << "Caught exception: '" << except.what() << "'\n";
    return EXIT_FAILURE;
  }
}
