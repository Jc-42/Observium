#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Animal.h"
#include <cmath>

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

static std::vector<int> pixel_to_hex(double x, double y, double radius){
  double q = (((std::sqrt(3)/3) * x)  -  ((1.0/3) * y)) / radius;
  double r = ((2.0/3) * y) / radius;
  double s = -q - r;
  std::vector<int> cube = cube_round(q, r, s);
  return cube_to_oddr(cube[0], cube[1], cube[2]);
}

static std::vector<int> cube_round(double frac_q, double frac_r, double frac_s){
  int q = std::round(frac_q);
  int r = std::round(frac_r);
  int s = std::round(frac_s);

  double q_diff = std::abs(q - frac_q);
  double r_diff = std::abs(r - frac_r);
  double s_diff = std::abs(s - frac_s);

  if (q_diff > r_diff && q_diff > s_diff) q = -r-s;
  else if (r_diff > s_diff) r = -q-s;
  else s = -q-r;

  return std::vector<int>{q, r, s};
}

static sf::Vector2f normalize(const sf::Vector2f& vector) {
  double length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
  if (length != 0.0f) {
    return sf::Vector2f(vector.x / length, vector.y / length);
  } else {
    return sf::Vector2f(0.0f, 0.0f);
  }
}

};