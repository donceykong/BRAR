#ifndef INVERSE_KINEMATICS_H
#define INVERSE_KINEMATICS_H

// Jacobian-inverse IK
void computeInverseKinematics(Vector3 targetPosition) {
    const float tolerance = 0.01; // Define a tolerance for the position error
    const int maxIterations = 1000; // Limit the number of iterations
    int iteration = 0;

    Vector3 currentEndEffectorPos = endEffectorPosition; // From your forward kinematics
    while (distance(currentEndEffectorPos, targetPosition) > tolerance && iteration < maxIterations) {
        Matrix4x4 jacobian = computeJacobian(); // Compute the Jacobian matrix for the current joint angles
        Vector3 error = subtract(targetPosition, currentEndEffectorPos); // Position error
        Vector3 deltaTheta = solveJacobianInverse(jacobian, error); // Calculate change in joint angles

        // Update joint angles
        joint0Angle += deltaTheta.x;
        joint1Angle += deltaTheta.y;
        joint2Angle += deltaTheta.z;
        // ... update other joint angles as needed

        computeForwardKinematics(); // Recompute forward kinematics with new joint angles
        currentEndEffectorPos = endEffectorPosition; // Update the current end-effector position

        iteration++;
    }
}

#endif // INVERSE_KINEMATICS_H