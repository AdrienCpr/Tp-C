module;
import std;

export module lzw.encoderv2;

import lzw.encoder;

export namespace lzw {
    // Deuxième version en utilisant std::map
    class EncoderV2 : public Encoder {
    public:
        using keycode_t = std::uint16_t;
        const keycode_t maxKeyCode{std::numeric_limits<keycode_t>::max()};
        const keycode_t firstFreeKeyCode{256};

        void Decode(std::ifstream& in, std::ofstream& out) override {
            std::map<keycode_t, std::string> dictionary;
            const auto reset_dictionary = [&dictionary, this] {
                dictionary.clear();
                for (keycode_t i = 0; i < firstFreeKeyCode; i++) {
                    dictionary[i] = std::string{static_cast<char>(i)};
                }
            };
            reset_dictionary();

            auto s = std::string{};
            while (!in.eof()) {
                if (dictionary.size() == maxKeyCode) {
                    reset_dictionary();
                }
                keycode_t keycode{};
                if (!in.read(reinterpret_cast<char*>(&keycode), sizeof(keycode_t))) {
                    break;
                }
                if (keycode > dictionary.size()) {
                    std::cerr << "Dictionary Error\n";
                    break;
                }
                if (keycode == dictionary.size()) {
                    dictionary[dictionary.size()] = s + s[0];
                }
                else if (!s.empty()) {
                    dictionary[dictionary.size()] = s + dictionary[keycode][0];
                }
                out << dictionary[keycode];
                s = dictionary[keycode];
            }
        }

        void Encode(std::ifstream& in, std::ofstream& out) override {
            std::map<std::string, keycode_t> dictionary;
            const auto reset_dictionary = [&dictionary, this] {
                dictionary.clear();
                for (keycode_t i = 0; i < firstFreeKeyCode; i++) {
                    dictionary[std::string{static_cast<char>(i)}] = i;
                }
            };
            reset_dictionary();

            auto s = std::string{};
            while (!in.eof()) {
                if (dictionary.size() == maxKeyCode) {
                    reset_dictionary();
                }
                char c;
                in.get(c);
                if (in.eof()) break;
                const auto prev_s = s;
                s += c;
                if (!dictionary.contains(s)) {
                    dictionary[s] = dictionary.size();
                    out.write(reinterpret_cast<const char*>(&dictionary[prev_s]), sizeof(keycode_t));
                    s = std::string{c};
                }
            }
            if (!s.empty()) {
                out.write(reinterpret_cast<const char*>(&dictionary[s]), sizeof(keycode_t));
            }
        }
    };
}