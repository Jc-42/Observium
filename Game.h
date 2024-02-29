#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Animal.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Texture tileTexture;
    sf::Texture waterTexture;
    sf::Texture animalTexture;
    Animal rabbit;
    Tile map[35][35];
    double deltaTime;
    double cameraOffsetX;
    double cameraOffsetY;
public:
    Game(int sizeX, int sizeY);
    sf::RenderWindow& getWindow();
    void paint();   

static std::vector<int> cube_to_oddr(int q, int r, int s) {
   int col = q + (r - (r & 1)) / 2;
   int row = r;
   return std::vector<int>{col, row};
}

static std::vector<int> oddr_to_cube(int x, int y) {
   int q = x - (y - (y & 1)) / 2;
   int r = y;
   int s = -q - r;
   return std::vector<int>{q, r, s};
}

// Function to add two vectors (arrays)
static std::vector<int> vector_add(const std::vector<int>& v1, const std::vector<int>& v2) {
  if (v1.size() != v2.size()) {
    throw std::invalid_argument("Vectors must have the same size");
  }
  std::vector<int> result(v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    result[i] = v1[i] + v2[i];
  }
  return result;
}

// Function to generate results based on center and N
static std::vector<std::vector<int>> generate_results(const std::vector<int>& center, int N) {
  std::vector<std::vector<int>> results;
  std::vector<std::vector<int>> resultsFin;
  for (int q = -N; q <= N; ++q) {
    for (int r = std::max(-N, -q - N); r <= std::min(N, -q + N); ++r) {
      int s = -q - r;
      std::vector<int> new_point = {q, r, s};
      results.push_back(vector_add(center, new_point));
    }
  }

  for(int i = 0; i < results.size(); i++){
    resultsFin.push_back(Game::cube_to_oddr(results[i][0], results[i][1], results[i][2]));
  }
  return resultsFin;
}

};