//
// Created by QCZ on 9/29/2024.
//

#include "HeatSolver.hpp"
#include "ExplicitScheme.hpp"
#include "ImplicitScheme.hpp"
#include "CrankNicolsonScheme.hpp"
#include "SchemeType.hpp"

int main() {


    // Set up simulation parameters
    SimulationParameters params(L, N, TL, TH, crit, NO, ST, thermalConductivity, density, specificHeat);

    // Select the time-stepping scheme
    SchemeType scheme = SchemeType::Explicit;

    // Instantiate the appropriate time-stepping scheme
    std::unique_ptr<TimeStepping> timeStepScheme;

    if (scheme == SchemeType::Explicit){
        timeStepScheme = std::make_unique<ExplicitScheme>();
    } else if (scheme == SchemeType::Implicit) {
        timeStepScheme == std::make_unique<ImplicitScheme>()
    } else if (scheme == SchemeType::CrankNicolson) {
        timeStepScheme == std::make_unique<CrankNicolson>()
    }

    // Create the solver and pass the time-stepping scheme
    HeatSolver solver(params, std::move(timeStepScheme));
    solver.run_simulation();

}