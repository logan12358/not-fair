function Player(socket) {
  let player = this
  player.socket = socket
  player.game = null

  player.socket.once('hello', ({ name, colour }) => {
    player.name = name
    player.colour = colour
    console.log('received hello')
  })
  console.log('created a new player')
}

module.exports = Player
