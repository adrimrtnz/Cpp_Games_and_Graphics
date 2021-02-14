#include <glm/glm.hpp>  // vec3, vec3, mat4
#include <glm/ext.hpp>	// translate, scale, rotate


// Defining a 2D point. The arguments passed are the X and Y coordinates
glm::vec2 p1 = glm::vec2(2.0f, 10.0f);

// Defining a 3D point. The areguments passed are the X, Y and Z coordinates
glm::vec3 p2 = glm::vec3(10.0f, 5.0f, 2.0f);

// Creating a 4x4 matrix. The 1.0f shows that the matrix is initialized as an identity matrix
glm::mat4 matrix = glm::mat4(1.0f);

glm::mat4 translation = glm::translate(matrix, glm::vec3(3.0f, 4.0f, 8.0f));

// To translate the object
glm::mat4 scale = glm::scale(matrix, glm::vec3(2.0f, 2.0f, 2.0f));

// glm::radians() convert degrees into radians
glm::mat4 rxMatrix = glm::rotate(glm::mat4(), glm::radians(45.0f), glm::vec3(1.0, 0.0, 0.0));
glm::mat4 ryMatrix = glm::rotate(glm::mat4(), glm::radians(25.0f), glm::vec3(0.0, 1.0, 0.0));
glm::mat4 rzMatrix = glm::rotate(glm::mat4(), glm::radians(10.0f), glm::vec3(0.0, 0.0, 1.0));

// OpenGL data types
	// OpenGL data types are prefixed with GL, followed by the data type
	// GLboolean, GLint, GLhalf, GLfloat...

// To create the view matrix with GLM, create three variables to define
// camera position, camera target position, camera up vector
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 200.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Create the matrix using the lookAt function and ussing the camera pasition as argument
glm::mat4 viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
