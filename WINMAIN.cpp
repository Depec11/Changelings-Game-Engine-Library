#include "base/game_loop.h"
#include "main_scene.h"

int main() {
	GameLoop::GenerateInstance(1280, 720, true);

	shared_ptr<MainScene> ms = make_shared<MainScene>();
	GameLoop::AddScene(ms);
	ms = nullptr;

	GameLoop::StartAndJoin();

	GameLoop::DeleteInstance();

	return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	main();
}
