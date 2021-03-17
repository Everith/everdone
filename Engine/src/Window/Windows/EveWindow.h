#pragma once
#include "Everith/Window/Window.h"
#include "Everith/Events/Events.h"
#include "Everith\Exception\EveException.h"

namespace Everith {
	class HWND_AccesKey // acces to window handler for graphis class
	{
		// TODO enable when graphics exist
		//friend Graphics;
	public:
		HWND_AccesKey(const HWND_AccesKey&) = delete;
		HWND_AccesKey& operator=(HWND_AccesKey&) = delete;
	protected:
		HWND_AccesKey() = default; //protected constructor ????
		HWND hWnd = nullptr; //windows handler
	};
	/// <window handler acces class for graphics
	/// /////////////////////////////////////////////////////////////////////////////////////////////
	/// main window class>

	class EveWindow : public HWND_AccesKey {
	public:
		//Window exceptions
		class Exception :EveException {
		public:
			using EveException::EveException;
			virtual std::string GetFullMessage() const override { return GetNote() + "\nAt: " + GetLocation(); }
			virtual std::string GetExceptionType() const override { return "Windows Exception"; }
		};

	public:
		EveWindow(HINSTANCE hInst, char* pArgs);
		EveWindow(const EveWindow&) = delete;
		EveWindow& operator=(const EveWindow&) = delete;
		~EveWindow();

		HWND Create(const WindowProps& props);
		void setHInstance(HINSTANCE  hInstance);
		bool IsActive() const;
		bool IsMinimized() const;
		void ShowMessageBox(const std::string& title, const std::string& message, UINT type = MB_OK) const;
		void Kill() { PostQuitMessage(0); }
		// returns false if quitting
		bool ProcessMessage();
		const std::string& GetArgs() const { return args; }

	private: //Event handlers
		//TODO restruct event handler not to be winAPI call for other platforms
		static LRESULT CALLBACK EveEventHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private: //variables
		HINSTANCE  hInstance = nullptr; //windows ID / handler
		std::string args;
		static constexpr char* wndClassName = "Everith - Everdone Windwo"; // TODO implement to recive data from struct

		// TODO implement input handler classes later
	public:
		WPARAM m_QuitMessage = 0;
		static Everith::Events EveEvents;

		//	Keyboard kbd;
		//	Mouse mouse;
	};
}