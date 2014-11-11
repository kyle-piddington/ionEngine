
#include "Context.h"
#include <GL/glew.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		void Context::Init()
		{
			CheckedGLCall(glEnable(GL_DEPTH_TEST));
			CheckedGLCall(glDepthFunc(GL_LEQUAL));
		}

		void Context::Clear(std::vector<EBuffer> Buffers)
		{
			static u32 const BufferLookup[3] =
			{
				GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT
			};
			int BitMask = 0;
			for (auto Buffer : Buffers)
				BitMask |= BufferLookup[(int) Buffer];
			CheckedGLCall(glClear(BitMask));
		}

		void Context::SetClearColor(color3f const & Color)
		{
			CheckedGLCall(glClearColor(Color.Red, Color.Green, Color.Blue, 1.f));
		}

		vec2i Context::GetViewportSize()
		{
			int viewport[4];
			CheckedGLCall(glGetIntegerv(GL_VIEWPORT, viewport));

			return vec2i(viewport[2] - viewport[0], viewport[3] - viewport[1]);
		}
	}
}
