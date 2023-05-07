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

#ifdef HAZAL_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		HAZAL_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 4.5), "Hazal requires at least OpenGL version 4.5");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}