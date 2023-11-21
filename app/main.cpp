#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

void write_ofstream(const std::string& str)
{
	std::ofstream file("text_ofstream.txt");

	const auto now = std::chrono::system_clock::now();
	file << str;
	const auto end = std::chrono::system_clock::now();
	const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
	std::cout << "ofstream: " << elapsed.count() << "ms" << std::endl;
	// ofstream: 751ms
}

void write_fwrite(const std::string str)
{
	// fopen_sを使用する
	FILE* fp;
	auto err = fopen_s(&fp, "text_fwrite.txt", "w");
	if (err != 0) {
		std::cout << "ファイルが開けませんでした" << std::endl;
		return;
	}

	const auto now = std::chrono::system_clock::now();
	fwrite(str.data(), sizeof str[0], str.length(), fp);
	const auto end = std::chrono::system_clock::now();
	const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
	fclose(fp);
	std::cout << "fwrite: " << elapsed.count() << "ms" << std::endl;
	// fwrite: 670ms
}

#define _CRT_SECURE_NO_WARNINGS
void write_putc(const std::string str)
{
	// fopen_sを使用する
	FILE* fp;
	auto err = fopen_s(&fp, "text_putc.txt", "w");

	if (err != 0) {
		std::cout << "ファイルが開けませんでした" << std::endl;
		return;
	}

	const auto now = std::chrono::system_clock::now();
	for (const auto& c : str) {
		putc(c, fp);
	}
	const auto end = std::chrono::system_clock::now();
	const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);

	fclose(fp);

	std::cout << "putc: " << elapsed.count() << "ms" << std::endl;
	// putc: 9563ms
}

void omake_string()
{
	{
		std::string str = "";
		const auto now = std::chrono::system_clock::now();
		for (int n = 0; n < 100000; n++) {
			str += std::to_string(111.0) + " " + std::to_string(222.2) + " " + std::to_string(333.3) + " " + std::to_string(44444444) + "\n";
		}
		const auto end = std::chrono::system_clock::now();
		const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
		std::cout << "string_1: " << elapsed.count() << "ms" << std::endl;
		// string_1: 1530ms
	}

	{
		std::string str = "";
		const auto now = std::chrono::system_clock::now();
		for (int n = 0; n < 100000; n++) {
			str += std::to_string(111.0);
			str += " ";
			str += std::to_string(222.2);
			str += " ";
			str += std::to_string(333.3);
			str += " ";
			str += std::to_string(44444444);
			str += "\n";
		}
		const auto end = std::chrono::system_clock::now();
		const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - now);
		std::cout << "string_2: " << elapsed.count() << "ms" << std::endl;
		// string_2: 985ms
	}
}

int main()
{
	std::string str = "";
	for (int n = 0; n < 20000000; n++) {
		str += "0123456789\n";
	}

	write_ofstream(str);
	write_fwrite(str);
	write_putc(str);

	return 0;
}