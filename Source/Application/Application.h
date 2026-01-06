#pragma once

class Application
{
public:

	// アプリケーション実行
	void Execute();

private:

	Window m_window = {};

	Application () = default;
	~Application() = default;

public:

	static Application& Instance()
	{
		static Application instance;
		return instance;
	}
};