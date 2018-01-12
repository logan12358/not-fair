#include "not_fair.h"
#include <sio_client.h>
#include <sio_message.h>
#include <string>
#include <cstdio>

NotFairPlayer::NotFairPlayer(std::string host) { h.connect(host); }

void NotFairPlayer::run() {
  h.socket()->on("start", [this](sio::event& ev) {
    this->h.socket()->off("start");
    auto message = ev.get_message();
    auto size = message->get_map()["size"]->get_vector();
    int num_players = message->get_map()["players"]->get_int();
    int colour = message->get_map()["turn"]->get_int();
    this->begin_game(std::pair<int, int>(size[0]->get_int(), size[1]->get_int()), num_players, colour);

    this->h.socket()->on("move", [this, num_players, colour](sio::event &ev) {
      auto message = ev.get_message();
      auto position = message->get_map()["position"]->get_vector();
      int move_colour = message->get_map()["colour"]->get_int();
      this->move(std::pair<int, int>(position[0]->get_int(), position[1]->get_int()), move_colour);
      this->turn = (this->turn + 1) % num_players;
      printf("turn is now %d\n", this->turn);
      if (this->turn == colour) {
        auto position = this->make_move();
        auto message = sio::object_message::create();
        message->get_map()["position"] = sio::array_message::create();
        message->get_map()["position"]->get_vector().push_back(sio::int_message::create(position.first));
        message->get_map()["position"]->get_vector().push_back(sio::int_message::create(position.second));
        this->h.socket()->emit("move", message);
      }
    });
    if (this->turn == colour) {
      auto position = this->make_move();
      auto message = sio::object_message::create();
      message->get_map()["position"] = sio::array_message::create();
      message->get_map()["position"]->get_vector().push_back(sio::int_message::create(position.first));
      message->get_map()["position"]->get_vector().push_back(sio::int_message::create(position.second));
      this->h.socket()->emit("move", message);
    }
  });

  auto hello_message = sio::object_message::create();
  hello_message->get_map()["name"] = sio::string_message::create(this->name());
  hello_message->get_map()["colour"] = sio::string_message::create(this->colour());
  this->h.socket()->emit("hello", hello_message);
  printf("emitted hello\n");


  while(scanf("%*c") != EOF);
  exit(0);
}
