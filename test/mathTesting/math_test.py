from ctypes import Structure, c_float, CDLL, byref

# Define the structures with the same memory layout as C
class Vector3(Structure):
    _fields_ = [("x", c_float),
                ("y", c_float),
                ("z", c_float)]

class Matrix4x4(Structure):
    _fields_ = [("m", c_float * 16)]  # This is a flat array of 16 floats

# Load the shared library
lib = CDLL('./libmathtesting.so')

# Set up the return types and argument types for the C functions
lib.translationMatrix.restype = Matrix4x4
lib.translationMatrix.argtypes = [c_float, c_float, c_float]

lib.rotationMatrix.restype = Matrix4x4
lib.rotationMatrix.argtypes = [c_float, c_float, c_float, c_float]

lib.multiplyMatrix.restype = Matrix4x4
lib.multiplyMatrix.argtypes = [Matrix4x4, Matrix4x4]

lib.extractPosition.restype = Vector3
lib.extractPosition.argtypes = [Matrix4x4]

# Now you can call the functions
trans_mat = lib.translationMatrix(1.0, 2.0, 3.0)
rot_mat = lib.rotationMatrix(90.0, 0.0, 0.0, 1.0)
result_mat = lib.multiplyMatrix(rot_mat, trans_mat)
position = lib.extractPosition(result_mat)

print(f"Position: {position.x}, {position.y}, {position.z}")


import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Original and transformed points
original_point = [1.0, 2.0, 3.0]
transformed_point = [-2.0, 1.0, 3.0]

# Create a new figure for plotting
fig = plt.figure()

# Add a 3D subplot
ax = fig.add_subplot(111, projection='3d')

# Plot the original point in red
ax.scatter(original_point[0], original_point[1], original_point[2], c='r', marker='o', s=100, label='Original Point')

# Plot the transformed point in blue
ax.scatter(transformed_point[0], transformed_point[1], transformed_point[2], c='b', marker='^', s=100, label='Transformed Point')

# Set labels
ax.set_xlabel('X Axis')
ax.set_ylabel('Y Axis')
ax.set_zlabel('Z Axis')

# Set the title
ax.set_title('3D Point Transformation')

# Adding a legend to show labels
ax.legend()

# Show the plot
plt.show()

