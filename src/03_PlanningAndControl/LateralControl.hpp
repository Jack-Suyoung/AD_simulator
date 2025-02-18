#ifndef LATERAL_CONTROL_HPP
#define LATERAL_CONTROL_HPP

double StanleyControl(const PlanningResults_t* path_result, const VehicleState_t* ego_state, double k, double v0);

#endif // LATERAL_CONTROL_HPP
