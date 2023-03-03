#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Hazal {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		HAZAL_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HAZAL_CORE_ASSERT(status, "Failed to initialize Glad!");

		HAZAL_CORE_INFO("OpenGL Renderer: ");
		HAZAL_CORE_INFO("  {0}", (char*) glGetString(GL_VENDOR));
		HAZAL_CORE_INFO("  {0}", (char*) glGetString(GL_RENDERER));
		HAZAL_CORE_INFO("  {0}", (char*) glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}