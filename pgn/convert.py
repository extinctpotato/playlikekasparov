#!/usr/bin/env python3

import chess, chess.pgn, sys, os

pgn = open(sys.argv[1])

game = None

for i in range(int(sys.argv[2])):
    game = chess.pgn.read_game(pgn)

board = game.board()

board_states = list(reversed(str(board).replace(" ","").split('\n')))

states_count = 1

for move in game.mainline_moves():
    board.push(move)
    board_states = board_states + list(reversed(str(board).replace(" ","").split('\n')))
    states_count += 1

print(str(states_count))
print("\n".join(board_states))
