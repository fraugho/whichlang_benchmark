#include <iostream>
#include <cassert>
#include "language_detector.hpp"

int main() {
    std::cout << "Testing language detection...\n";
    
    assert(LanguageDetector::detectLanguage("Hello, happy tax payer") == Lang::Eng);
    assert(LanguageDetector::detectLanguage("Bonjour joyeux contribuable") == Lang::Fra);
    assert(LanguageDetector::detectLanguage("Hallo glücklicher Steuerzahler") == Lang::Deu);
    assert(LanguageDetector::detectLanguage("こんにちは幸せな税金納め") == Lang::Jpn);
    assert(LanguageDetector::detectLanguage("你好幸福的纳税人") == Lang::Cmn);
    assert(LanguageDetector::detectLanguage("Merhaba, mutlu vergi mükellefi") == Lang::Tur);
    assert(LanguageDetector::detectLanguage("Hallo, blije belastingbetaler") == Lang::Nld);
    assert(LanguageDetector::detectLanguage("안녕하세요 행복한 납세자입니다") == Lang::Kor);
    assert(LanguageDetector::detectLanguage("Ciao, felice contribuente!") == Lang::Ita);
    assert(LanguageDetector::detectLanguage("Hola feliz contribuyente") == Lang::Spa);
    assert(LanguageDetector::detectLanguage("¡Hola!") == Lang::Spa);
    assert(LanguageDetector::detectLanguage("Olá feliz contribuinte") == Lang::Por);
    assert(LanguageDetector::detectLanguage("") == Lang::Eng);
    
    std::cout << "All tests passed!\n";
    return 0;
}
