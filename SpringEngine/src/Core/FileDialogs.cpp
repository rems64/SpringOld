#include <SpringEngine/Core/FileDialogs.hpp>

#include <Windows.h>
#include <commdlg.h>

namespace SE
{
	std::string openFile(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		//ofn.hwndOwner = glfwGetWin32Window();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
		if (GetOpenFileNameA(&ofn) == TRUE)
		{
			//std::cout << ofn.lpstrFile << std::endl;
			return ofn.lpstrFile;
		};
		return std::string();
	}
};