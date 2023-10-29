#include "Common.h"

namespace Util
{
	static bool DownloadFile(const char* url, const char* file_name)
	{
		auto result = URLDownloadToFileA(nullptr, url, file_name, 0, nullptr);
		switch (result)
		{
		case E_OUTOFMEMORY:
		{
			spdlog::error("There is insufficient memory to complete the operation. E_OUTOFMEMORY");
			break;
		}
		case INET_E_DOWNLOAD_FAILURE:
		{
			spdlog::error("The specified resource or callback interface was invalid. INET_E_DOWNLOAD_FAILURE");
			break;
		}
		case S_OK:
		{
			spdlog::info("URLDownloadToFile(). S_OK");
			return true;
		}
		}

		return false;
	}

	static void ToClipboard(const char* str)
	{
		HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, (strlen(str) + 1));
		memcpy(GlobalLock(hg), str, (strlen(str) + 1));
		GlobalUnlock(hg);
		OpenClipboard(0);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hg);
		CloseClipboard();
		GlobalFree(hg);
	}

	struct HumanReadable {
		std::uintmax_t size{};

		friend std::ostream& operator<<(std::ostream& os, const HumanReadable& hr) {
			int i{};
			double mantissa = hr.size;
			for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}
			mantissa = std::ceil(mantissa * 10.) / 10.;
			os << mantissa << " " << "BKMGTPE"[i];
			return i == 0 ? os : os << "B (" << hr.size << ')';
		}
	};
}