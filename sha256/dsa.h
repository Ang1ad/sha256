#include "sha256.h"
#include <string>
#include <iostream>
#include <sstream>

// Функция для вычисления (a^b) % m
unsigned long long mod_exp(unsigned long long a, unsigned long long b, unsigned long long m) {
    unsigned long long result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % m;
        }
        b = b >> 1;
        a = (a * a) % m;
    }
    return result;
}

// Функция для вычисления обратного числа по модулю
unsigned long long mod_inverse(unsigned long long a, unsigned long long m) {
    unsigned long long m0 = m, t, q;
    unsigned long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// Генерация ключей
void generate_keys(unsigned long long& p, unsigned long long& q, unsigned long long& g, unsigned long long& x, unsigned long long& y) {
    p = 23;
    q = 11;
    g = 3;

    // Генерация приватного ключа x
    x = 5;

    // Вычисление публичного ключа y
    y = mod_exp(g, x, p);
}

// Создание подписи
void sign_message(const std::string& message, unsigned long long p, unsigned long long q, unsigned long long g, unsigned long long x, unsigned long long& r, unsigned long long& s) {
    // Вычисление хеша сообщения
    std::ostringstream hash_stream = sha256(message);
    std::cout << "Хеш при создании подписи: " << hash_stream.str() << std::endl;
    std::string hash_str = hash_stream.str();
    unsigned long long H_m = std::stoull(hash_str.substr(0, 16), nullptr, 16); // Берем первые 64 бита хеша

    // Генерация случайного числа k
    unsigned long long k = 3;

    // Вычисление r и s
    r = mod_exp(g, k, p) % q;
    s = (mod_inverse(k, q) * (H_m + x * r)) % q;
}

// Проверка подписи
bool verify_signature(const std::string& message, unsigned long long p, unsigned long long q, unsigned long long g, unsigned long long y, unsigned long long r, unsigned long long s) {
    // Вычисление хеша сообщения
    std::ostringstream hash_stream = sha256(message);
    std::cout << "Хеш при проверке подписи: " << hash_stream.str() << std::endl;
    std::string hash_str = hash_stream.str();
    unsigned long long H_m = std::stoull(hash_str.substr(0, 16), nullptr, 16); // Берем первые 64 бита хеша

    // Вычисление w
    unsigned long long w = mod_inverse(s, q);

    // Вычисление u1 и u2
    unsigned long long u1 = (H_m * w) % q;
    unsigned long long u2 = (r * w) % q;

    // Вычисление v
    unsigned long long v = (mod_exp(g, u1, p) * mod_exp(y, u2, p)) % p % q;

    // Проверка подписи
    return v == r;
}
