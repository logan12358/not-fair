var http = require('http').Server()
var io = require('socket.io')(http)
var Player = require('./Player.js')
var Game = require('./Game.js')

var players = []
var games = []

io.on('connection', function(socket) {
  let player = new Player(socket)
  players.push(player)
})

startGames = () => {
  let ready_players = players.filter(player => player.name !== undefined && player.game === null)
  while (ready_players.length >= 2) {
    let game = new Game([ready_players.pop(), ready_players.pop()], [10, 10])
    games.push(game)
  }
  setTimeout(startGames, 1000)
}

startGames()

http.listen(3000, function() {
  console.log('listening on *:3000')
})
