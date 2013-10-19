
#include <ionEngine.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main()
{
	if (! glfwInit())
	{
		std::cerr << "Error initializing glfw! " << std::endl;
		WaitForUser();
		exit(33);
	}

	int Count;
	GLFWmonitor ** Monitors = glfwGetMonitors(& Count);

	std::cout << "Monitors: " << std::endl;
	for (int i = 0; i < Count; ++ i)
	{
		int X, Y;
		glfwGetMonitorPhysicalSize(Monitors[i], & X, & Y);
		std::cout << "   [" << i << "] " << glfwGetMonitorName(Monitors[i]) << " " 
			<< X << " x " << Y 
			<< std::endl;
	}

	GLFWwindow * window = 0;
	glfwWindowHint(GLFW_VISIBLE, false);
	if (! (window = glfwCreateWindow(640, 480, "Utility Compile Test", 0, 0)))
	{
		std::cerr << "Error opening glfw window! " << std::endl;
		WaitForUser();
		exit(33);
	}
	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error initializing glew! " << glewGetErrorString(err) << std::endl;
		WaitForUser();
		exit(33);
	}
	
	std::cerr << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cerr << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;
	std::cerr << "Vender: " << glGetString(GL_VENDOR) << std::endl;
	std::cerr << "Renderer: " << glGetString(GL_RENDERER) << std::endl << std::endl;
	glfwDestroyWindow(window);
	glfwTerminate();

	WaitForUser();

	return 0;
}
