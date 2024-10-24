//
// Created by QCZ on 9/29/2024.
//

#include "SimulationParameters.hpp"
#include "Grid.hpp"

SimulationParameters::SimulationParameters(double L, int N, double TL, double TH, double crit, int NO, int ST, double dl,
                                           double thermalConductivity, double density, double specificHeat)
                         : L(L), N(N), TL(TL), TH(TH), crit(crit), NO(NO), ST(ST), lm(thermalConductivity) {

    // Calculate volumetric specific heat (rho * Cp)
    rhoCp = density * specificHeat;

    // Calculate thermal diffusivity (alpha = k / rhoCp)
    calculate_derived_properties();

}

void SimulationParameters::calculate_derived_properties() {
    alpha = lm / rhoCp;  // Thermal Conductivity
    dt = r / a * dl * dl;// time step
}