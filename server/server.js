var http = require('http').Server()
var io = require('socket.io')(http)

io.on('connection', function(socket) {
  console.log('A user connected')
})

http.listen(3000, function() {
  console.log('listening on *:3000')
})
