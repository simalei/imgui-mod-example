#include "includes.hpp"

static bool g_visible;

void InitUI()
{

}

void RenderUI()
{
    if (g_visible)
    {
        ImGui::Begin("Window title");
        ImGui::Text("Hello World!");
        ImGui::End();
    }
}

DWORD MainThread(LPVOID lpParam)
{
    MH_Initialize();

    ImGuiHook::setInitFunction(InitUI);
    ImGuiHook::setRenderFunction(RenderUI);

    ImGuiHook::setToggleCallback([]() {
        g_visible = !g_visible;
    });

    ImGuiHook::setToggleKey(VK_TAB);


    ImGuiHook::setupHooks([](void* target, void* hook, void** trampoline) {
        MH_CreateHook(target, hook, trampoline);
    });

    MH_EnableHook(MH_ALL_HOOKS);

    return S_OK;
}

DWORD __stdcall DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0x1000, reinterpret_cast<LPTHREAD_START_ROUTINE>(&MainThread), NULL, 0, NULL);
		break;
    case DLL_PROCESS_DETACH:
        break;
	default:
		break;
	}

	return TRUE;
}