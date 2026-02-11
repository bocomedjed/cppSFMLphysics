#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace sf;

const unsigned WIDTH = 300;
const unsigned HEIGHT = 250;
const float DAMPING = 0.95f;
const float SCALE = 4.0f;

int main() {
    RenderWindow window(VideoMode(Vector2u(static_cast<unsigned>(WIDTH * SCALE),
                                            static_cast<unsigned>(HEIGHT * SCALE))),
                        "Wave Simulation SFML 3");
    window.setFramerateLimit(60);

    vector<vector<float>> wave(HEIGHT, vector<float>(WIDTH, 0.0f));
    vector<vector<float>> prev_wave = wave;

    // Create vertex array for pixels
    VertexArray pixels(PrimitiveType::Points, WIDTH * HEIGHT);
    for (unsigned y = 0; y < HEIGHT; ++y) {
        for (unsigned x = 0; x < WIDTH; ++x) {
            pixels[y * WIDTH + x].position = Vector2f(x * SCALE, y * SCALE);
            pixels[y * WIDTH + x].color = Color::Black;
        }
    }

    int frame = 0;

    while (window.isOpen()) {
        while (auto eOpt = window.pollEvent()) {
            const auto &e = *eOpt;
            if (e.is<Event::Closed>()) window.close();
        }

        // Add disturbance
        if (frame % 20 == 0) {
            int cx = WIDTH / 2;
            int cy = HEIGHT / 2;
            for (int dy = -5; dy <= 5; ++dy) {
                for (int dx = -5; dx <= 5; ++dx) {
                    int y = cy + dy;
                    int x = cx + dx;
                    if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
                        wave[y][x] = 512.0f;
                }
            }
        }
        frame++;

        // Wave propagation
        for (unsigned y = 1; y < HEIGHT - 1; ++y) {
            for (unsigned x = 1; x < WIDTH - 1; ++x) {
                float value = (prev_wave[y-1][x] + prev_wave[y+1][x] +
                               prev_wave[y][x-1] + prev_wave[y][x+1]) / 2 - wave[y][x];
                value *= DAMPING;
                wave[y][x] = value;
            }
        }
        prev_wave = wave;

        // Update vertex colors
        for (unsigned y = 0; y < HEIGHT; ++y) {
            for (unsigned x = 0; x < WIDTH; ++x) {
                int colorValue = clamp(int(wave[y][x] / 2 + 128), 0, 255);
                pixels[y * WIDTH + x].color = Color(colorValue, colorValue, colorValue);
            }
        }

        window.clear();
        window.draw(pixels);
        window.display();
    }

    return 0;
}
