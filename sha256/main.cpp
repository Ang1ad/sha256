#include "sha256.h"
#include "dsa.h"

int main()
{
    setlocale(LC_ALL, "rus");

    unsigned long long p, q, g, x, y, r, s;
    std::string message = "Hello, DSA!";

    // ��������� ������
    generate_keys(p, q, g, x, y);

    // �������� �������
    sign_message(message, p, q, g, x, r, s);

    // �������� �������
    bool is_valid = verify_signature(message, p, q, g, y, r, s);
    is_valid ? (std::cout << "Signature valid" << std::endl) : (std::cout << "Signature invalid" << std::endl);

	return 0;
}