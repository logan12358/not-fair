# But Not as we Know it

> Programming game for NZOI January Camp 2018, inspired by Life

## Concept

The game is played on a rectangular grid. Two (or possibly more) players take turns selecting a cell to attempt to convert to their colour. When a cell is selected, it changes colour probabilistically, depending on the colours of neighbouring squares and on which player's turn it is.

Specifically, when a player selects a cell, the colours of the cells in a 3x3 grid centered on the selected cell are counted. The weight used to distribute the probability between outcomes is taken as the count of cells of that colour, plus one for the colour of the player whose turn it is.
