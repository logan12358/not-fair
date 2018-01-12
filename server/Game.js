let assert = require('assert')

let sample = array => array[Math.floor(Math.random() * array.length)]

let game_id = 0

function Game(players, size) {
  let game = this
  let [width, height] = game.size = size
  game.id = game_id++
  game.players = players
  game.turn = 0
  game.board =
    new Array(height)
    .fill(null)
    .map(_ => new Array(width)
              .fill(null))

  assert(players.every(player => player.game === null), 'players not all idle')
  for (let player of game.players) {
    player.game = game
    player.index = game.players.indexOf(player)
    player.socket.emit('start', {
      size: game.size,
      players: game.players.length,
      turn: game.players.indexOf(player)
    })
    player.socket.on('move', ({ position }) => { 
      if (game.players[game.turn] !== player) return
      game.move(position)
    })
  }

  console.log('created a new game')
}

Game.prototype.end = function() {
  for (let player of this.players) {
    player.socket.emit('end')
    player.socket.off('move')
  }
}

/** Checks whether a position is valid (on the game board) */
Game.prototype.isValid = function(position) {
  let [column, row] = position
  let [width, height] = this.size
  return column >= 0 && column < width && row >= 0 && row < height
}

Game.prototype.get = function(position) {
  let [column, row] = position
  return this.board[row][column]
}

Game.prototype.set = function(position, player) {
  let [column, row] = position
  return this.board[row][column] = player
}

Game.prototype.neighbours = function*(position) {
  let [column, row] = position
  let deltas = [-1, 0, 1]
  for (let delta_column of deltas) {
    for (let delta_row of deltas) {
      let neighbour = [column + delta_column, row + delta_row]
      if (this.isValid(neighbour)) yield this.get(neighbour)
    }
  }
}

Game.prototype.move = function(position) {
  let [column, row] = position
  let neighbours =
    Array
    .from(this.neighbours(position))
    .filter(neighbour => neighbour)
  neighbours.push(this.players[this.turn])
  console.log(neighbours)
  let new_owner = this.set(position, sample(neighbours))
  for (let player of this.players) {
    player.socket.emit('move', {
      position: position,
      colour: new_owner.index
    })
  }
  this.turn = (this.turn + 1) % this.players.length
  return new_owner
}

module.exports = Game
