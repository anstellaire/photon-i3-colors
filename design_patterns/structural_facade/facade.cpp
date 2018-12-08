#include <iostream>
#include <memory>
#include <string>

// -----------------------------------------------------------------------------
//   HELPER ENTITIES
// -----------------------------------------------------------------------------

enum class audio_format {
    MP3, OGG
};

struct encoded_audio_stream {
    audio_format format;
    std::string data;
};

struct decoded_audio_stream {
    std::string data;
};

struct audio_file {
    std::string name;
    encoded_audio_stream stream;
};

// -----------------------------------------------------------------------------
//   CODEC
// -----------------------------------------------------------------------------

struct audio_codec {
    virtual ~audio_codec() {}
    virtual encoded_audio_stream encode(decoded_audio_stream const& stream) = 0;
    virtual decoded_audio_stream decode(encoded_audio_stream const& stream) = 0;
};

struct ogg_audio_codec : audio_codec {
    encoded_audio_stream encode(decoded_audio_stream const& stream) {
        return encoded_audio_stream{
            audio_format::OGG, stream.data + " -> ogg_audio_codec::encode"
        };
    }

    decoded_audio_stream decode(encoded_audio_stream const& stream) {
        return decoded_audio_stream{
            stream.data + " -> ogg_audio_codec::decode"
        };
    }
};

struct mp3_audio_codec : audio_codec {
    encoded_audio_stream encode(decoded_audio_stream const& stream) {
        return encoded_audio_stream{
            audio_format::MP3, stream.data + " -> mp3_audio_codec::encode"
        };
    }

    decoded_audio_stream decode(encoded_audio_stream const& stream) {
        return decoded_audio_stream{
            stream.data + " -> mp3_audio_codec::decode"
        };
    }
};

struct audio_codec_factory {
    static std::unique_ptr<audio_codec> get_codec(audio_format format) {
        switch (format) {
            case audio_format::MP3:
                return std::unique_ptr<audio_codec>{new mp3_audio_codec};
            case audio_format::OGG:
                return std::unique_ptr<audio_codec>{new ogg_audio_codec};
            default:
                throw std::exception{};
        };
    }
};

// -----------------------------------------------------------------------------
//   BIT READER
// -----------------------------------------------------------------------------

struct audio_bit_reader {
    decoded_audio_stream read(encoded_audio_stream const& stream, audio_codec& codec) {
        decoded_audio_stream decoded_stream = codec.decode(stream);
        decoded_audio_stream decoded_read_stream = decoded_audio_stream{
            decoded_stream.data + " -> audio_bit_reader::read"};
        return decoded_read_stream;
    }

    encoded_audio_stream write(decoded_audio_stream const& stream, audio_codec& codec) {
        decoded_audio_stream decoded_read_stream = decoded_audio_stream{
            stream.data + " -> audio_bit_reader::write"};
        encoded_audio_stream encoded_stream = codec.encode(decoded_read_stream);
        return encoded_stream;
    }
};

// -----------------------------------------------------------------------------
//   FACADE
// -----------------------------------------------------------------------------

struct audio_converter_facade {
    static encoded_audio_stream convert(
        encoded_audio_stream const& file, audio_format target_format) {

        audio_bit_reader bit_reader{};

        std::unique_ptr<audio_codec> decoder =
            audio_codec_factory::get_codec(file.format);
        decoded_audio_stream decoded_data = bit_reader.read(file, *decoder);

        std::unique_ptr<audio_codec> encoder =
            audio_codec_factory::get_codec(target_format);
        encoded_audio_stream encoded_data = bit_reader.write(decoded_data, *encoder);

        return encoded_data;
    }
};

// -----------------------------------------------------------------------------
//   USAGE
// -----------------------------------------------------------------------------

int main() {
    audio_file file{"in.ogg",
        encoded_audio_stream{audio_format::OGG, "oggdata"}};
    std::cout << "Data before conversion: " << file.stream.data << std::endl;

    audio_file new_file{"out.ogg",
        audio_converter_facade::convert(file.stream, audio_format::MP3)};
    std::cout << "Data after conversion:  " << new_file.stream.data << std::endl;
}
