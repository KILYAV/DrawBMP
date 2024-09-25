#include "DrawBMP.h"

bool DrawBMP::OpenBMP(const std::string& fileName) {
	if (name == fileName)
		return true;

	if (false == name.empty()) {
		Clear();
	}

	if (file.open(fileName, std::ios::in); file)
		name = fileName;

	return static_cast<bool>(file);
}
bool DrawBMP::DisplayBMP() {
	if (!file)
		return false;

	BITMAPFILEHEADER head;
	file.read(static_cast<char*>(static_cast<void*>(&head)), sizeof(head));
	if (file.fail())
		return false;

	constexpr WORD BM = ('M' << 8) + 'B';
	if (BM != head.bfType)
		return false;

	BITMAPINFOHEADER info;
	file.read(static_cast<char*>(static_cast<void*>(&info)), sizeof(info));
	if (file.fail())
		return false;

	constexpr UINT countBitInByte = 8;
	constexpr UINT tripSize = sizeof(RGBTRIPLE);
	constexpr UINT quadSize = sizeof(RGBQUAD);
	constexpr WORD biBitCount24 = tripSize * countBitInByte;
	constexpr WORD biBitCount32 = quadSize * countBitInByte;
	const UINT RGBSize{
		biBitCount24 == info.biBitCount ?
			tripSize :
			biBitCount32 == info.biBitCount ?
				quadSize :
				NULL
	};

	if (RGBSize) {
		const UINT width = (info.biWidth * RGBSize + tripSize) / quadSize * quadSize;
		const UINT count = width * info.biHeight;
		std::vector<char> data;
		data.resize(count);

		file.seekg(head.bfOffBits, std::ios::beg);
		file.read(data.data(), count);
		if (file.fail()) {
			return false;
		}

		std::string output;
		output.reserve((info.biWidth + 1) * info.biHeight);
		for (UINT y = info.biHeight - 1; y + 1 > 0; --y) {
			for (UINT x = 0; x < info.biWidth; ++x) {
				const char blace = 0;
				const char white = 255;
				UINT red = y * width + x * RGBSize;
				UINT green = ++red;
				UINT blue = ++green;
				if (blace == (data[red] | data[green] | data[blue])) {
					output += '#';
				}
				else if (white == (data[red] & data[green] & data[blue])) {
					output += ' ';
				}
				else
					return false;
			}
			output += '\n';
		}
		std::cout << output;
		return true;
	}
	return false;
}
void DrawBMP::
CloseBMP() {
	Clear();
}
void DrawBMP::Clear() {
	file.close();
	name.clear();
}