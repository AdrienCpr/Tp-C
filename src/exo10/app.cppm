module;
import std;

export module lzw.application;

import lzw.encoder;
import lzw.encoderv1;
import lzw.encoderv2;
import lzw.encoderv3;

export namespace lzw {
    class Application {
    public:
        // `filename_input_text` : fichier à compresseur
        // `filename_output_lz` : fichier destination pour la compression
        // `filename_ouput_text` : fichier destination pour la décompression
        Application(const std::string& filename_input_text,
                    const std::string& filename_output_lz,
                    const std::string& filename_ouput_text) {
            // Routine d'essai pour la compression
            auto compress = [&filename_input_text, &filename_output_lz](Encoder& encoder) {
                std::ifstream input_text{filename_input_text, std::ifstream::in};
                if (!input_text.is_open()) {
                    std::cerr << "Error opening file " << filename_input_text << std::endl;
                    return;
                }
                std::ofstream output_lz{filename_output_lz, std::ifstream::out | std::ifstream::binary};
                if (!input_text.is_open()) {
                    std::cerr << "Error opening file " << filename_output_lz << std::endl;
                    return;
                }

                const auto t_start = std::chrono::high_resolution_clock::now();
                encoder.Encode(input_text, output_lz);
                const auto t_end = std::chrono::high_resolution_clock::now();
                const auto elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
                input_text.close();
                output_lz.close();

                std::ifstream in_txt(filename_input_text, std::ifstream::ate | std::ifstream::binary);
                const auto input_size{in_txt.tellg()};
                std::ifstream in_lz(filename_output_lz, std::ifstream::ate | std::ifstream::binary);
                const auto compressed_size{in_lz.tellg()};
                const auto percentage = static_cast<double>(compressed_size) / static_cast<double>(input_size) * 100.0;
                std::cout << input_size << " bytes uncompressed, "
                    << compressed_size << " bytes uncompressed, "
                    << percentage << "%"
                    << " in " << elapsed_time_ms << "ms"
                    << std::endl;
            };
            // Routine d'essai pour la décompression
            auto decompress = [&filename_output_lz, &filename_ouput_text](Encoder& encoder) {
                std::ifstream input_lz{filename_output_lz, std::ifstream::in | std::ifstream::binary};
                if (!input_lz.is_open()) {
                    std::cerr << "Error opening file " << filename_output_lz << std::endl;
                    return;
                }
                std::ofstream output_text{filename_ouput_text, std::ifstream::out};
                if (!output_text.is_open()) {
                    std::cerr << "Error opening file " << filename_ouput_text << std::endl;
                    return;
                }
                const auto t_start = std::chrono::high_resolution_clock::now();
                encoder.Decode(input_lz, output_text);
                const auto t_end = std::chrono::high_resolution_clock::now();
                const auto elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
                input_lz.close();
                output_text.close();
                std::cout << "uncompress in " << elapsed_time_ms << "ms" << std::endl;
            };

            EncoderV1 encoder_v1{};
            EncoderV2 encoder_v2{};
            EncoderV3 encoder_v3{};

            compress(encoder_v1);
            decompress(encoder_v1);

            compress(encoder_v2);
            decompress(encoder_v2);

            compress(encoder_v3);
            decompress(encoder_v3);
        }
    };
}