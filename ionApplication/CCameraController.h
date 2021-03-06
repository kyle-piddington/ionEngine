
#pragma once

#include <ionCore.h>
#include <ionFramework.h>
#include <ionWindow.h>
#include <ionScene.h>


namespace ion
{

	class CCameraController : public IEventListener
	{

	public:

		CCameraController(Scene::ICamera * Camera);

		virtual void OnEvent(IEvent & Event);
		virtual void Update(f64 const TickTime);

		virtual vec3f const & GetPosition() const;
		virtual f32 GetPhi() const;
		virtual f32 GetTheta() const;
		virtual f32 GetVelocity() const;
		virtual Scene::ICamera const * GetCamera() const;
		virtual Scene::ICamera * GetCamera();

		virtual void SetVelocity(f32 const Velocity);
		virtual void SetPhi(f32 const Phi);
		virtual void SetTheta(f32 const Theta);

	protected:

		enum class ECommand
		{
			Forward = 0,
			Back = 1,
			Left = 2,
			Right = 3,
			Count = 4
		};

		bool Commands[(int) ECommand::Count];

		f32 MoveSpeed, LookSpeed, FocalLengthDelta, MaxAngleEpsilon;
		bool Tracking;
		f32 Phi, Theta;

		Scene::ICamera * Camera;

	};

	class CGamePadCameraController : public CCameraController, public CGamePad
	{

	public:

		CGamePadCameraController(Scene::ICamera * Camera);
		virtual void Update(f64 const TickTime);

	protected:

		f32 FocalLengthAccumulator = 0;

	};

}
