#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <thread>

// Formula: VCC/4 / A2D_VDD * 2^12 (12-bit resolution)
#define DC_BIAS_IN_A2D ((0.825 / 1.8) * 4096)
#define SCALE_FACTOR 16

void saveWaveFile() {
    // const int sample_period = 1000000000 / SAMPLE_RATE;

    std::ifstream in("/sys/bus/iio/devices/iio:device0/in_voltage4_raw");
    std::ofstream out("sample.wav", std::ofstream::binary);

    // Write header
    const int sample_length = 1;

    const int fmt_length = 16;
    const short fmt_type = 1; // PCM
    const short num_channels = 1;
    const int sample_rate = 8000;
    const int num_samples = sample_length * sample_rate;
    const int h_29 = sample_rate * sizeof(short) * num_channels;
    const short h_33 = sizeof(short) * num_channels;
    const short bits_per_sample = sizeof(short) * 8;
    const int data_size = num_samples * sizeof(short);
    const int file_size = data_size + 36;

    out << "RIFF";
    out.write((char *)&file_size, sizeof(file_size));
    out << "WAVE";
    out << "fmt ";
    out.write((char *)&fmt_length, sizeof(fmt_length));
    out.write((char *)&fmt_type, sizeof(fmt_type));
    out.write((char *)&num_channels, sizeof(num_channels));
    out.write((char *)&sample_rate, sizeof(sample_rate));
    out.write((char *)&h_29, sizeof(h_29));
    out.write((char *)&h_33, sizeof(h_33));
    out.write((char *)&bits_per_sample, sizeof(bits_per_sample));
    out << "data";
    out.write((char *)&data_size, sizeof(data_size));

    // 1 ms / sample rate
    const int sample_period = 1000000 / sample_rate;

    // Write data
    short data;
    int buf;
    const short data_max = std::numeric_limits<short>::max();
    const short data_min = std::numeric_limits<short>::min();

    for (int i = 0; i < num_samples; i++) { // 1 second
        in >> buf;
        buf -= DC_BIAS_IN_A2D;

        if (buf * SCALE_FACTOR > data_max) {
            data = data_max;
        } else if (buf * SCALE_FACTOR < data_min) {
            data = data_min;
        } else {
            data = buf * SCALE_FACTOR;
        }

        out.write((char *)&data, sizeof(data));

        in.seekg(0);
        std::this_thread::sleep_for(std::chrono::microseconds(sample_period));
    }

    out.close();
}
