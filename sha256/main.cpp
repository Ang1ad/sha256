#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <sstream>

typedef std::vector<std::bitset<8>> vec_8bit;

std::bitset<32> rightshift(std::bitset<32> number, const uint32_t shift);
std::bitset<32> rightrotate(std::bitset<32> number, const uint32_t shift);
std::bitset<32> add_bitsets(const std::bitset<32>& a, const std::bitset<32>& b);

int main()
{
	//шифруемое слово
    std::string input_string;
    std::cin >> input_string;

	vec_8bit sequence;
	for (int i = 0; i < input_string.size(); i++)
	{
		sequence.push_back(input_string[i]);
	}
	std::cout << std::endl;

	//Инициализация значений хеша(h)
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

	//Инициализация округлённых констант(k)
	const size_t N = 64;
	uint32_t k[N] = 
	{
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 
	};

	//Добавим одну единицу
	sequence.push_back(0x80);

	//Заполняем нулями до тех пор, пока данные не станут кратны 512 без последних 64 бит
	while ((sequence.size() * 8 + 64) % 512 != 0) {
		sequence.push_back(0x00);
	}

	//Добавим 64 бита в конец, где 64 бита — целое число с порядком байтов big-endian, обозначающее длину входных данных в двоичном виде
	uint64_t bit_length = input_string.size() * 8;
	for (int i = 7; i >= 0; --i) {
		sequence.push_back((bit_length >> (8 * i)) & 0xFF);
	}

    // Разбиваем сообщение на 512-битные блоки
    for (size_t chunk_start = 0; chunk_start < sequence.size(); chunk_start += 64) {
        std::vector<std::bitset<32Ui32>> w(64);

        for (int i = 0; i < 16; ++i) {
            w.at(i) = (sequence[chunk_start + i * 4].to_ulong() << 24) |
                (sequence[chunk_start + i * 4 + 1].to_ulong() << 16) |
                (sequence[chunk_start + i * 4 + 2].to_ulong() << 8) |
                (sequence[chunk_start + i * 4 + 3].to_ulong());
        }

        for (int i = 16; i < 64; ++i) {
            std::bitset<32> s0 = rightrotate(w.at(i - 15), 7) ^ rightrotate(w.at(i - 15), 18) ^ rightshift(w.at(i - 15), 3);
            std::bitset<32> s1 = rightrotate(w.at(i - 2), 17) ^ rightrotate(w.at(i - 2), 19) ^ rightshift(w.at(i - 2), 10);
            w.at(i) = add_bitsets(w.at(i - 16), s0);
            w.at(i) = add_bitsets(w.at(i), w.at(i - 7));
            w.at(i) = add_bitsets(w.at(i), s1);
        }

        // Инициализация рабочих переменных
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;

        // Основной цикл
        for (int i = 0; i < 64; ++i) {
            uint32_t S1 = rightrotate(e, 6).to_ulong() ^ rightrotate(e, 11).to_ulong() ^ rightrotate(e, 25).to_ulong();
            uint32_t ch = (e & f) ^ (~e & g);
            uint32_t temp1 = h + S1 + ch + k[i] + w[i].to_ulong();
            uint32_t S0 = rightrotate(a, 2).to_ulong() ^ rightrotate(a, 13).to_ulong() ^ rightrotate(a, 22).to_ulong();
            uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        // Добавляем результат к ранее вычисленному
        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    // Формируем итоговый хеш
    std::ostringstream result;
    result << std::hex << std::setfill('0')
        << std::setw(8) << h0
        << std::setw(8) << h1
        << std::setw(8) << h2
        << std::setw(8) << h3
        << std::setw(8) << h4
        << std::setw(8) << h5
        << std::setw(8) << h6
        << std::setw(8) << h7;

    std::cout << "SHA-256: " << result.str() << std::endl;

	return 0;
}

std::bitset<32> rightshift(std::bitset<32> number, const uint32_t shift)
{
	return number >> shift;
}

std::bitset<32> rightrotate(std::bitset<32> number, const uint32_t shift)
{
	return (number >> shift) | (number << (32 - shift));
}

std::bitset<32> add_bitsets(const std::bitset<32>& a, const std::bitset<32>& b) {
	uint32_t a_val = a.to_ulong();
	uint32_t b_val = b.to_ulong();
	uint32_t sum = a_val + b_val;
	return std::bitset<32>(sum);
}