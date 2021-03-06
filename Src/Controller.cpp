#include "Controller.h"

Controller::Controller(){
	currentState = INIT;
	angle = 0.0f;
}



void Controller::handleKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods){
	angle += 0.001f;

	switch (currentState){

	case Controller::READY:
		if (action == GLFW_PRESS && GLFW_MOD_CONTROL) {
			switch (key) {
			case GLFW_KEY_W:
				model->translateCamera(glm::vec3(0.0f, 0.0f, 0.5f));
				break;
			case GLFW_KEY_A:
				model->translateCamera(glm::vec3(-0.5f, 0.0f, 0.0f));
				break;
			case GLFW_KEY_S:
				model->translateCamera(glm::vec3(0.0f, 0.0f, -0.5f));
				break;
			case GLFW_KEY_D:
				model->translateCamera(glm::vec3(0.5f, 0.0f, 0.0f));
				break;
			default:
				break;
			}
		}
		break;

	case Controller::DRAGGING:
		break;

	case Controller::HALT:
		break;

	default:
		break;
	}

}



void Controller::handleMouseClick(GLFWwindow* window, int button, int action, int mods){
	std::cout << "CLICKED SETUP \n";
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	switch (currentState) {

	case Controller::INIT:
		model->addShape(0);
		model->addShape(0);
		//model->addShape(3);
		model->translateShape(model->getShapes()[0], glm::vec3(0.0f, 0.0f, -3.0f));
		model->translateShape(model->getShapes()[1], glm::vec3(0.0f, 1.0f, -2.0f));

		currentState = READY;
		break;

	case Controller::READY:
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			currentState = DRAGGING;
		}
		break;
	case Controller::DRAGGING:
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
			currentState = READY;
		}
		break;

	case Controller::HALT:
		//model->translateShape(model->getShapes()[0], glm::vec3(xpos / 800.0f, xpos / 800.0f, -3.0f));
		break;

	default:
		break;
	}
}

void Controller::handleMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	std::cout << "WE SCHOOLING" << xoffset << "      " << yoffset << std::endl;
	switch (currentState)
	{
	case Controller::INIT:
		break;
	case Controller::READY:
		model->zoomCamera(yoffset * 0.1f);
		break;
	case Controller::DRAGGING:
		break;
	case Controller::HALT:
		break;
	default:
		break;
	}

}


void Controller::handleMouseMove(GLFWwindow* window, double xpos, double ypos){
	switch (currentState) {
	case Controller::READY:
		break;

	case Controller::DRAGGING:
		//model->rotateShape(model->getShapes()[0], glm::vec3(1.0f, 1.0f, 0.0f), angle);
		model->rotateCamera(PrevX - xpos, PrevY - ypos);
		break;

	case Controller::HALT:
		break;

	default:
		break;
	}
	PrevX = xpos;
	PrevY = ypos;
	//angle += 1.0f;
}




void Controller::setModel(Model* givenModel) {
	model = givenModel;
}