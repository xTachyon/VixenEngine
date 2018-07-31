#include <iostream>
#include "Camera.h"

namespace input {
	glm::mat4 Camera::getProjection() {
		return projection;
	}
	
	glm::mat4 Camera::getView() {
		return view;
	}
	
	glm::vec3 Camera::getPosition() {
		return position;
	}
	
	void Camera::update(graphics::Window *window) {
		double currentX = 0, currentY = 0;
		double xOffset = 0, yOffset = 0;
		glfwGetCursorPos(window->getWindow(), &currentX, &currentY);
		if (firstMouse) {
			lastX = currentX;
			lastY = currentY;
			firstMouse = false;
		}
		xOffset = currentX - lastX;
		yOffset = currentY - lastY;
		lastX = currentX;
		lastY = currentY;
		
		horizontal -= sensitivity * window->getDeltaTime() * xOffset;
		vertical -= sensitivity * window->getDeltaTime() * yOffset;
		
		vec3 direction(cos(vertical) * sin(horizontal), sin(vertical), cos(vertical) * cos(horizontal));
		vec3 right(sin(horizontal - 3.14f / 2.0f), 0, cos(horizontal - 3.14f / 2.0f));
		vec3 up = cross(right, direction);
		
		if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
			position += direction * window->getDeltaTime() * speed;
		if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
			position -= direction * window->getDeltaTime() * speed;
		if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
			position += right * window->getDeltaTime() * speed;
		if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
			position -= right * window->getDeltaTime() * speed;
		if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE))
			position += vec3(0, 1, 0) * window->getDeltaTime() * speed;
		if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT_SHIFT))
			position -= vec3(0, 1, 0) * window->getDeltaTime() * speed;
		
		projection = perspective(radians(FoV), 16.0f / 9.0f, 0.1f, 1000.0f);
		view = lookAt(position, position + direction, up);
	}
}