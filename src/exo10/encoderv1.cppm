module;
import std;
import exo9;

export module lzw.encoderv1;

import lzw.encoder;

export namespace lzw {

    // Première version en utilisant notre classe dictionnaire basée sur notre classe arbre binaire
    class EncoderV1 : public Encoder {
    public:
        using keycode_t = std::uint16_t;
        const keycode_t maxKeyCode { std::numeric_limits<keycode_t>::max() };
        const keycode_t firstFreeKeyCode { 256 };

        void Decode(std::ifstream& in, std::ofstream& out) override {
            exo9::Map<keycode_t, std::string> dictionary;
            const auto reset_dictionary = [&dictionary, this] {
                dictionary.Clear();
                for(keycode_t i = 0; i < firstFreeKeyCode; i++) {
                    dictionary.Put(i, std::string{static_cast<char>(i)});
                }
            };
            reset_dictionary();

            auto s = std::string{};
            while (!in.eof()) {
                if (dictionary.GetSize() == maxKeyCode) {
                    reset_dictionary();
                }
                keycode_t keycode{};
                if (!in.read(reinterpret_cast<char*>(&keycode), sizeof(keycode_t))) {
                    break;
                }
                if (keycode > dictionary.GetSize()) {
                    std::cerr << "Dictionary Error\n";
                    break;
                }
                if (keycode == dictionary.GetSize()) {
                    dictionary.Put(dictionary.GetSize(), s + s[0]);
                } else if (!s.empty()) {
                    dictionary.Put(dictionary.GetSize(), s + dictionary.Get(keycode)[0]);
                }
                out << dictionary.Get(keycode);
                s = dictionary.Get(keycode);
            }
        }

        void Encode(std::ifstream& in, std::ofstream& out) override {
            exo9::Map<std::string, keycode_t> dictionary;
            const auto reset_dictionary = [&dictionary, this] {
                dictionary.Clear();
                for(keycode_t i = 0; i < firstFreeKeyCode; i++) {
                    dictionary.Put(std::string{static_cast<char>(i)}, i);
                }
            };
            reset_dictionary();

            auto s = std::string{};
            while (!in.eof()) {
                if (dictionary.GetSize() == maxKeyCode) {
                    reset_dictionary();
                }
                char c;
                in.get(c);
                if (in.eof()) break;
                const auto prev_s = s;
                s += c;
                if (!dictionary.Contains(s)) {
                    dictionary.Put(s, dictionary.GetSize());
                    out.write(reinterpret_cast<const char*>(&dictionary.Get(prev_s)), sizeof(keycode_t));
                    s = std::string{c};
                }
            }
            if (!s.empty()) {
                out.write(reinterpret_cast<const char*>(&dictionary.Get(s)), sizeof(keycode_t));
            }
        }

    };

}