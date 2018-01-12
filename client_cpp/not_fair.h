#include <sio_client.h>
#include <sio_message.h>
#include <string>
#include <cstdio>

class NotFairPlayer {
  virtual std::string name() const = 0;
  virtual std::string colour() const = 0;
  sio::client h;

  virtual void begin_game(std::pair<int, int> size, int num_players, int colour) = 0;
  virtual void move(std::pair<int, int> position, int colour) = 0;
  virtual std::pair<int, int> make_move() = 0;

protected:
  NotFairPlayer(std::string host);
  int turn = 0;

public:
  void run();
};
