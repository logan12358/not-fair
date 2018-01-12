#include "not_fair.h"
#include <cstdio>

class MyPlayer : public NotFairPlayer {
  std::string name() const { return "logan"; }
  std::string colour() const { return "purple"; }

  void begin_game(std::pair<int, int> size, int num_players, int colour) {
    // a game is about to begin
    printf("Beginning game\n(%d, %d), %d, %d\n", size.first, size.second, num_players, colour);
  }
  void move(std::pair<int, int> position, int colour) {
    // a move was just made (you receive this for your own moves as well)
    printf("A move was made by %d at (%d, %d), of colour %d\n", this->turn, position.first, position.second, colour);
  };

  std::pair<int, int> make_move() {
    // try to take cell (0, 0)
    return {0, 0};
  }

public:
  MyPlayer(std::string host) : NotFairPlayer(host) {}
};

int main() {
  MyPlayer player("http://localhost:3000");
  player.run();
}
