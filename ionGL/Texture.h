
#pragma once

#include <ionCore.h>
#include <ionMath.h>

#include "Utilities.h"


namespace ion
{
	namespace GL
	{
		class Texture
		{
		public:

			////////////////////
			// Texture Params //
			////////////////////

			enum class EFilter
			{
				Nearest = 0,
				Linear = 1
			};

			enum class EWrapMode
			{
				Clamp = 0,
				Mirror = 1,
				Repeat = 2
			};

			enum class EFormatComponents
			{
				R = 0,
				RG = 1,
				RGB = 2,
				RGBA = 3
			};

			enum class EInternalFormatType
			{
				Fix8 = 0,
				Fix16 = 1,
				U8 = 2,
				U16 = 3,
				U32 = 4,
				S8 = 5,
				S16 = 6,
				S32 = 7,
				F16 = 8,
				F32 = 9
			};
			
			static u32 const InternalFormatMatrix[4][10];
			static u32 const FormatMatrix[4];

			static string const InternalFormatStringMatrix[4][10];
			static string const FormatStringMatrix[4];
			

			///////////////
			// Interface //
			///////////////
			
			virtual ~Texture();
			
			void SetMinFilter(EFilter const MinFilter);
			void SetMagFilter(EFilter const MagFilter);
			void SetMipMapFilter(EFilter const MipMapFilter);
			void SetWrapMode(EWrapMode const WrapMode);
			void SetAnisotropy(f32 const Anisotropy);
			
			EFilter GetMinFilter();
			EFilter GetMagFilter();
			EFilter GetMipMapFilter();
			EWrapMode GetWrapMode();
			f32 GetAnisotropy();

			virtual u32 GetHandle() const;
			virtual u32 GetGLBindTextureTarget() = 0;

		protected:

			Texture();
			virtual u32 GetGLTextureBindingEnum() = 0;
			void ApplyParams();
			
			u32 Handle = 0;
			
			EFilter MinFilter = EFilter::Linear;
			EFilter MagFilter = EFilter::Linear;
			EFilter MipMapFilter = EFilter::Linear;
			EWrapMode WrapMode = EWrapMode::Repeat;

			//! Anisotrophic filtering value
			//! A value < 0 indicates that the max anisotrophy value should be used
			f32 Anisotropy = -1.f;

			bool MipMaps;
		};

		class Texture2D : public Texture
		{

		public:

			Texture2D(vec2u const & Size, bool const MipMaps = true, EFormatComponents const Components = EFormatComponents::RGBA, EInternalFormatType const Type = EInternalFormatType::Fix8);

			//! 
			//! Note that this is not a direct corollary to the glTextureImage2D call - you must first call Storage to allocate space for this texture
			//! This method simply calls SubImage with a zero offset and size = texture size
			void Image(void const * const data, EFormatComponents const Components = EFormatComponents::RGBA, EFormatType const Type = EFormatType::U8);

			void SubImage(void const * const data, vec2u const & offset, vec2u const & size, EFormatComponents const components = EFormatComponents::RGBA, EFormatType const type = EFormatType::U8);

			u32 GetGLBindTextureTarget();

		protected:

			u32 GetGLTextureBindingEnum();

			vec2u Size;
		};
	}
}
